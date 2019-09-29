//
// Created by tobias on 27.03.18.
//
#include <parser/CQLParser.h>
#include "data_types/Long.h"
#include "data_types/Double.h"
#include "data_types/String.h"
#include "data_types/Null.h"
#include "data_types/Blob.h"
#include "data_types/Geometry.h"

#include "sqlite_adapter/sqlite_adapter_stream_module.h"
#include "sqlite_adapter/sqlite_adapter_stream_table.h"
#include "make_unique.h"

using namespace std;
using namespace STREAM;

int stream_create(sqlite3 *origin_db, void *pAux, int argc, const char *const *argv, sqlite3_vtab **ppVTab,
                  char **pzErr) {

    auto mgr = static_cast<Manager *>(pAux);

    CQLParser parser(*mgr);

    string sql("CREATE STREAM " + string(argv[2]) + "(");
    for (int i = 3; i < argc; i++) sql += (i < argc - 1) ? string(argv[i]) + "," : string(argv[i]) + ");";
    parser.parse(sql);

    // *************

    auto &table = mgr->getStream(string(argv[2]));

    sql = "CREATE TABLE " + string(argv[2]) + " (";
    auto desc = table->getSchema();
    for (size_t i = 0; i < desc.size(); i++) sql += (i < desc.size() - 1) ? desc.at(i).getName() + "," : desc.at(i).getName() + ");";

    sqlite3_declare_vtab(origin_db, sql.c_str());
    auto table_adapter = new sqlite_adapter_stream_table();

    table_adapter->setTable(table.get());
    ppVTab[0] = table_adapter;

    return SQLITE_OK;
};

int stream_connect(sqlite3 *origin_db, void *pAux, int argc, const char *const *argv, sqlite3_vtab **ppVTab, char **pzErr) { return SQLITE_OK; }

int stream_best_index(sqlite3_vtab *pVTab, sqlite3_index_info *index_info) { return SQLITE_OK; };

int stream_disconnect(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_destroy(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_open(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor) {

    ppCursor[0] = new sqlite3_vtab_cursor;

    return SQLITE_OK;
};

int stream_close(sqlite3_vtab_cursor *vtab_cursor) {

    auto stream_cursor = static_cast<sqlite_adapter_cursor *>(vtab_cursor);

    delete stream_cursor;

    return SQLITE_OK;
};

int stream_filter(sqlite3_vtab_cursor *vtab_cursor, int idxNum, const char *idxStr, int argc, sqlite3_value **argv) { return SQLITE_OK; };

int stream_next(sqlite3_vtab_cursor *vtab_cursor) { return 0; };

int stream_eof(sqlite3_vtab_cursor *vtab_cursor) { return SQLITE_ERROR; };

int stream_column(sqlite3_vtab_cursor *vtab_cursor, sqlite3_context *context, int num) { return SQLITE_OK; };

int stream_row_id(sqlite3_vtab_cursor *vtab_cursor, sqlite3_int64 *pRowid) {
    auto epoch = ((sqlite_adapter_cursor *) vtab_cursor)->get()->getTime().time_since_epoch();
    *pRowid = 1;

    cout << "set to" << pRowid << endl;

    return SQLITE_OK;
};

int stream_update(sqlite3_vtab *pVTab, int num, sqlite3_value **pValue,
                  sqlite3_int64 *pRowiD) {

    auto *table = ((sqlite_adapter_stream_table *) pVTab)->getTable();

    // Check, if operation is an insert. Returning an error, if it's not
    // Only insertions are allowed for streams

    if (!(num > 1 && sqlite3_value_type(pValue[0]) == SQLITE_NULL)) {
        return SQLITE_ERROR;
    }

    // Check, if the inserted row got no previously set row id
    // An notify on stream isn't allowed. Thus, every row needs a new id
    if (!(sqlite3_value_type(pValue[1]) == SQLITE_NULL)) {
        return SQLITE_ERROR;
    }


    auto tuple = table->createTuple();

    for (int i = 2; i < num; i++) {

        size_t idx = i - 2;

        switch (sqlite3_value_type(pValue[i])) {
            case SQLITE_TEXT: {
                tuple->set(idx, make_unique<String>(string(reinterpret_cast<const char *>(sqlite3_value_text(pValue[i])))));
                break;
            }

            case SQLITE_FLOAT: {
                tuple->set(idx, make_unique<Double>(sqlite3_value_double(pValue[i])));
                break;
            }

            case SQLITE_INTEGER: {
                tuple->set(idx, make_unique<Long>(sqlite3_value_int(pValue[i])));
                break;
            }

            case SQLITE_NULL: {
                // Fields were initialized with null-objects
                break;
            }

            case SQLITE_BLOB: {

                tuple->set(idx, make_unique<Geometry>(sqlite3_value_blob(pValue[i]), sqlite3_value_bytes(pValue[i])));
                break;
            }
            default: {
                return SQLITE_ERROR;
            }
        }
    }

    *pRowiD = tuple->getRowId();
    table->insert(tuple);

    return SQLITE_OK;
}

int stream_begin(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_sync(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_commit(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_rollback(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_find_method(sqlite3_vtab *pVtab, int nArg, const char *zName,
                       void (**pxFunc)(sqlite3_context *, int, sqlite3_value **), void **ppArg) { return SQLITE_OK; };

int stream_rename(sqlite3_vtab *pVtab, const char *zNew) { return SQLITE_OK; };

