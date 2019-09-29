//
// Created by tobias on 24.01.18.
//
#include <sqlite_adapter/sqlite_result_handler.h>
#include "Manager.h"
#include "sqlite_adapter/sqlite_adapter_stream_module.h"
#include "sqlite_adapter/sqlite_adapter_view_module.h"
#include "sqlite_adapter/sqlite_adapter_functions.h"
#include "make_unique.h"


SQLITE_EXTENSION_INIT1

#ifdef _WIN32
__declspec(dllexport)
#endif

STREAM::Manager mgr;

extern "C" {

sqlite3_module stream_module = {
        0,           /* iVersion */
        stream_create,     /* streamCreate */
        stream_connect,    /* xConnect */
        stream_best_index,  /* xBestIndex */
        stream_disconnect, /* xDisconnect */
        stream_destroy,    /* xDestroy */
        stream_open,       /* xOpen - open a cursor */
        stream_close,      /* xClose - close a cursor */
        stream_filter,     /* xFilter - configure scan constraints */
        stream_next,       /* xNext - advance a cursor */
        stream_eof,        /* xEof - check for end of scan */
        stream_column,     /* xColumn - read data */
        stream_row_id,      /* xRowid - read data */
        stream_update,     /* xUpdate */
        stream_begin,      /* xBegin */
        stream_sync,       /* xSync */
        stream_commit,     /* xCommit */
        stream_rollback,   /* xRollback */
        stream_find_method, /* xFindMethod */
        stream_rename      /* xRename */
};

sqlite3_module stream_view_module = {
        0,           /* iVersion */
        stream_view_create,     /* streamCreate */
        stream_view_connect,    /* xConnect */
        stream_view_best_index,  /* xBestIndex */
        stream_view_disconnect, /* xDisconnect */
        stream_view_destroy,    /* xDestroy */
        stream_view_open,       /* xOpen - open a cursor */
        stream_view_close,      /* xClose - close a cursor */
        stream_view_filter,     /* xFilter - configure scan constraints */
        stream_view_next,       /* xNext - advance a cursor */
        stream_view_eof,        /* xEof - check for end of scan */
        stream_view_column,     /* xColumn - read data */
        stream_view_row_id,      /* xRowid - read data */
        stream_view_update,     /* xUpdate */
        stream_view_begin,      /* xBegin */
        stream_view_sync,       /* xSync */
        stream_view_commit,     /* xCommit */
        stream_view_rollback,   /* xRollback */
        stream_view_find_method, /* xFindMethod */
        stream_view_rename      /* xRename */
};

int sqlite3_extension_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi) {

    SQLITE_EXTENSION_INIT2(pApi);

    sqlite3_create_module(db, "stream", &stream_module, &mgr);

    sqlite3_create_module(db, "streamview", &stream_view_module, &mgr);

    // Encode 2D geometry (WKT string + XY precision)
    sqlite3_create_function_v2(db, "geomFromWKT", 2, SQLITE_ANY, NULL, geomFromWKT, NULL, NULL, NULL);

    // Encode 3D geometry (WKT string + XY precision + Z precision)
    sqlite3_create_function_v2(db, "geomFromWKT", 3, SQLITE_ANY, NULL, geomFromWKT, NULL, NULL, NULL);

    // Encode 4D geometry (WKT string + XY precision + Z precision + T precision)
    sqlite3_create_function_v2(db, "geomFromWKT", 4, SQLITE_ANY, NULL, geomFromWKT, NULL, NULL, NULL);

    // Decode geometry
    sqlite3_create_function_v2(db, "AsWKT", 1, SQLITE_ANY, NULL, asWKT, NULL, NULL, NULL);

    std::cout << "STREAMS loaded." << std::endl;

    return SQLITE_OK;
}
};
