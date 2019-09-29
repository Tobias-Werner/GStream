//
// Created by tobias on 28.02.18.
//

#ifndef STREAMS_STREAM_STREAM_H
#define STREAMS_STREAM_STREAM_H

// System header
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <chrono>

// Lib header
#include <sqlite3ext.h>

// Project header
#include "operator/Stream.h"
#include "sqlite_adapter_cursor.h"
#include "Manager.h"

int stream_create(sqlite3 *origin_db, void *pAux, int argc, const char *const *argv, sqlite3_vtab **ppVTab,
                  char **pzErr);

int stream_connect(sqlite3 *origin_db, void *pAux, int argc, const char *const *argv, sqlite3_vtab **ppVTab,
                   char **pzErr);

int stream_best_index(sqlite3_vtab *pVTab, sqlite3_index_info *index_info);

int stream_disconnect(sqlite3_vtab *pVTab);

int stream_destroy(sqlite3_vtab *pVTab);

int stream_open(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor);

int stream_close(sqlite3_vtab_cursor *vtab_cursor);

int stream_filter(sqlite3_vtab_cursor *vtab_cursor, int idxNum, const char *idxStr, int argc,
                  sqlite3_value **argv);

int stream_next(sqlite3_vtab_cursor *vtab_cursor);

int stream_eof(sqlite3_vtab_cursor *vtab_cursor);

int stream_column(sqlite3_vtab_cursor *vtab_cursor, sqlite3_context *context, int num);

int stream_row_id(sqlite3_vtab_cursor *vtab_cursor, sqlite3_int64 *pRowid);

int stream_update(sqlite3_vtab *pVTab, int num, sqlite3_value **pValue,
                  sqlite3_int64 *pRowiD);

int stream_begin(sqlite3_vtab *pVTab);

int stream_sync(sqlite3_vtab *pVTab);

int stream_commit(sqlite3_vtab *pVTab);

int stream_rollback(sqlite3_vtab *pVTab);

int stream_find_method(sqlite3_vtab *pVtab, int nArg, const char *zName,
                       void (**pxFunc)(sqlite3_context *, int, sqlite3_value **), void **ppArg);

int stream_rename(sqlite3_vtab *pVtab, const char *zNew);




#endif //STREAMS_STREAM_STREAM_H
