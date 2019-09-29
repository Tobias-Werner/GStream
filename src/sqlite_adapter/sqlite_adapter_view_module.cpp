//
// Created by tobias on 27.03.18.
//

#include <sqlite_adapter/sqlite_result_handler.h>
#include <parser/CQLParser.h>
#include "sqlite_adapter/sqlite_adapter_view_module.h"
#include "sqlite_adapter/sqlite_adapter_stream_view.h"

using namespace std;
using namespace STREAM;

int stream_view_create(sqlite3 *origin_db, void *pAux, int argc, const char *const *argv, sqlite3_vtab **ppVTab, char **pzErr) {

    auto mgr = static_cast<Manager *>(pAux);

    CQLParser parser(*mgr);

    string sql("CREATE VIEW " + string(argv[2]) + " AS ");
    for (int i = 3; i < argc; i++) sql += (i < argc - 1) ? string(argv[i]) + "," : string(argv[i]) + ";";
    parser.parse(sql);

    // ***********

    auto &view = mgr->getView(argv[2]);

    sql = "CREATE TABLE " + string(argv[2]) + " (";

    auto schema = view->getSchema();
    for (size_t i = 0; i < schema.size(); i++) sql += (i < schema.size() - 1) ? schema.at(i).getName() + "," : schema.at(i).getName() + ");";

    sqlite3_declare_vtab(origin_db, sql.c_str());
    auto view_adapter = new sqlite_adapter_stream_view();

    view_adapter->setView(view.get());
    ppVTab[0] = view_adapter;

    return SQLITE_OK;
};

int stream_view_connect(sqlite3 *origin_db, void *pAux, int argc, const char *const *argv, sqlite3_vtab **ppVTab, char **pzErr) { return SQLITE_OK; }

int stream_view_best_index(sqlite3_vtab *pVTab, sqlite3_index_info *index_info) {

//    for (int i = 0; i < index_info->nConstraint; i++) {
//        fprintf(stdout, "  (%i) aConstraint->iColumn: %i\n", i, (index_info->aConstraint + i)->iColumn);
//
//        string mOperator;
//
//        switch ((index_info->aConstraint + i)->op) {
//            case SQLITE_INDEX_CONSTRAINT_EQ:
//                mOperator = "==";
//                break;
//            case SQLITE_INDEX_CONSTRAINT_GT:
//                mOperator = ">";
//                break;
//            case SQLITE_INDEX_CONSTRAINT_LE:
//                mOperator = "<=";
//                break;
//            case SQLITE_INDEX_CONSTRAINT_LT:
//                mOperator = "<";
//                break;
//            case SQLITE_INDEX_CONSTRAINT_GE:
//                mOperator = ">=";
//                break;
//            case SQLITE_INDEX_CONSTRAINT_MATCH:
//                mOperator = "MATCH";
//                break;
//            case SQLITE_INDEX_CONSTRAINT_LIKE:
//                mOperator = "LIKE";
//                break;
//            case SQLITE_INDEX_CONSTRAINT_GLOB:
//                mOperator = "GLOB";
//                break;
//            case SQLITE_INDEX_CONSTRAINT_REGEXP:
//                mOperator = "REGEXP";
//                break;
//        }
//
//        fprintf(stdout, "  (%i) aConstraint->op: %i (%s)\n", i, (index_info->aConstraint + i)->op, mOperator.c_str());
//        fprintf(stdout, "  (%i) aConstraint->usable: %i\n", i, (index_info->aConstraint + i)->usable);
//        fprintf(stdout, "  (%i) aConstraint->iTermOffset: %i\n", i, (index_info->aConstraint + i)->iTermOffset);
//    }
//
//    fprintf(stdout, " nOrderBy: %i (Number of terms in order by clause)\n", index_info->nOrderBy);
//
//    for (int i = 0; i < index_info->nOrderBy; i++) {
//        fprintf(stdout, "  (%i) aOrderBy->iColumn: %i\n", i, (index_info->aOrderBy + i)->iColumn);
//        fprintf(stdout, "  (%i) aOrderBy->desc: %i\n", i, (index_info->aOrderBy + i)->desc);
//    }
//
//    for (int i = 0; i < index_info->nConstraint; i++) {
//        fprintf(stdout, "  (%i) [must be set] aConstraintUsage->argvIndex: %i\n", i,
//                (index_info->aConstraintUsage + 1)->argvIndex);
//        fprintf(stdout, "  (%i) [must be set] aConstraintUsage->omit: %i\n", i,
//                (index_info->aConstraintUsage + 1)->omit);
//    }
//
//
//    fprintf(stdout, " [must be set] idxNum: %i (will be passed to xFilter)\n", index_info->idxNum);
//    fprintf(stdout, " [must be set] idxStr: %s (will be passed to xFilter)\n", index_info->idxStr);
//    fprintf(stdout, " [must be set] needToFreeIdxStr: %i\n", index_info->needToFreeIdxStr);
//    fprintf(stdout, " [must be set] orderByConsumed: %i\n", index_info->orderByConsumed);
//    fprintf(stdout, " [must be set] estimatedCost: %f\n", index_info->estimatedCost);
//    fprintf(stdout, " [must be set] estimatedRows: %lli\n", index_info->estimatedRows);
//    fprintf(stdout, " [must be set] idxFlags: %i\n", index_info->idxFlags);
//    fprintf(stdout, " [must be set] colUsed: %lli\n", index_info->colUsed);


    return SQLITE_OK;
};

int stream_view_disconnect(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_view_destroy(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_view_open(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor) {

    auto view = static_cast<sqlite_adapter_stream_view *>(pVTab);

    view->getView()->triggerPrevOperator(); // Remove outdated tuples

    auto cursor = new sqlite_adapter_cursor(view->getView());
    ppCursor[0] = cursor;

    return SQLITE_OK;
};

int stream_view_close(sqlite3_vtab_cursor *vtab_cursor) {

    auto stream_cursor = static_cast<sqlite_adapter_cursor *>(vtab_cursor);
    delete stream_cursor;

    return SQLITE_OK;
};

int stream_view_filter(sqlite3_vtab_cursor *vtab_cursor, int idxNum, const char *idxStr, int argc, sqlite3_value **argv) {

//    auto cursor = (sqlite_adapter_cursor *) vtab_cursor;

    return SQLITE_OK;
};

int stream_view_next(sqlite3_vtab_cursor *vtab_cursor) {
    ((sqlite_adapter_cursor *) vtab_cursor)->next();
    return SQLITE_OK;
};

int stream_view_eof(sqlite3_vtab_cursor *vtab_cursor) { return ((sqlite_adapter_cursor *) vtab_cursor)->end(); };

int stream_view_column(sqlite3_vtab_cursor *vtab_cursor, sqlite3_context *context, int num) {

    sqlite_adapter_cursor *cursor = (sqlite_adapter_cursor *) vtab_cursor;

    sqlite_result_handler result_handler(context);

    cursor->get()->getData()[num]->result(result_handler);

    return SQLITE_OK;
};

int stream_view_row_id(sqlite3_vtab_cursor *vtab_cursor, sqlite3_int64 *pRowid) {

    *pRowid = ((sqlite_adapter_cursor *) vtab_cursor)->get()->getRowId();

    return SQLITE_OK;
};

int stream_view_update(sqlite3_vtab *pVTab, int num, sqlite3_value **pValue, sqlite3_int64 *pRowiD) { return SQLITE_ERROR; }

int stream_view_begin(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_view_sync(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_view_commit(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_view_rollback(sqlite3_vtab *pVTab) { return SQLITE_OK; };

int stream_view_find_method(sqlite3_vtab *pVtab, int nArg, const char *zName, void (**pxFunc)(sqlite3_context *, int, sqlite3_value **),
                            void **ppArg) { return SQLITE_OK; };

int stream_view_rename(sqlite3_vtab *pVtab, const char *zNew) { return SQLITE_OK; };