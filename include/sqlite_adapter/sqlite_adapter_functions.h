//
// Created by tobias on 08.07.19.
//

#ifndef STREAMS_SQLITE_ADAPTER_FUNCTIONS_H
#define STREAMS_SQLITE_ADAPTER_FUNCTIONS_H

#include <sqlite3ext.h>
#include <string>

void asWKT(sqlite3_context *context, int nArg, sqlite3_value **values);

void geomFromWKT(sqlite3_context *context, int dimensions, sqlite3_value **values);

#endif //STREAMS_SQLITE_ADAPTER_FUNCTIONS_H
