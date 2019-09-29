//
// Created by tobias on 07.05.18.
//

#include "sqlite_adapter/sqlite_result_handler.h"
#include <sqlite3ext.h>
#include "data_types/Long.h"
#include "data_types/Blob.h"
#include "data_types/String.h"
#include "data_types/Double.h"
#include "data_types/Geometry.h"
#include <vector>
#include <iostream>

SQLITE_EXTENSION_INIT3

using namespace std;
using namespace STREAM;

sqlite_result_handler::sqlite_result_handler(sqlite3_context *context) : context(context) {}

void sqlite_result_handler::add(Long &value) {
    sqlite3_result_int(context, value.get());
}

void sqlite_result_handler::add(Double &value) {
    sqlite3_result_double(context, value.get());
}

void sqlite_result_handler::add(Blob &value) {
    cout << "hia" << endl;
    sqlite3_result_blob(context, reinterpret_cast<void * >(&value.get()[0]), value.get().size(), SQLITE_TRANSIENT);
}

void sqlite_result_handler::add(Geometry &geom) {

    const auto &twkb = geom.asTWKB();

    sqlite3_result_blob(context, reinterpret_cast<const void * >(twkb.data()), twkb.size(), SQLITE_TRANSIENT);
}

void sqlite_result_handler::add(String &value) {
    sqlite3_result_text(context, value.get().c_str(), -1, nullptr);
}

void sqlite_result_handler::add(Null &value) {
    sqlite3_result_null(context);
}