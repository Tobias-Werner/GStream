//
// Created by tobias on 08.07.19.
//

#include "sqlite_adapter/sqlite_adapter_functions.h"
#include "data_types/Geometry.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <regex>
#include <string>
#include <exception>
#include <forward_list>
#include <iomanip>

SQLITE_EXTENSION_INIT3

using namespace std;
using namespace STREAM;




void asWKT(sqlite3_context *context, int nArg, sqlite3_value **values) {
    stringstream stream;

    auto data = static_cast<const unsigned char *>(sqlite3_value_blob(values[0]));
    size_t size = sqlite3_value_bytes(values[0]);

    Geometry geom(data, size);

    sqlite3_result_text(context, geom.asWKT().c_str(), -1, SQLITE_TRANSIENT);

}

void geomFromWKT(sqlite3_context *context, int dimensions, sqlite3_value **values) {

    stringstream stream;
    stream << sqlite3_value_text(values[0]);


    switch (dimensions) {
        case 2: {
            Geometry geom(stream.str(), sqlite3_value_double(values[1]));
            const auto &twkb = geom.asTWKB();
            sqlite3_result_blob(context, static_cast<const void *>(twkb.data()), twkb.size(), SQLITE_TRANSIENT);
            break;
        }

        case 3: {
            Geometry geom(stream.str(), sqlite3_value_double(values[1]), sqlite3_value_double(values[2]));
            const auto &twkb = geom.asTWKB();
            sqlite3_result_blob(context, static_cast<const void *>(twkb.data()), twkb.size(), SQLITE_TRANSIENT);
            break;
        }

        case 4: {
            Geometry geom(stream.str(), sqlite3_value_double(values[1]), sqlite3_value_double(values[2]), sqlite3_value_double(values[3]));
            const auto &twkb = geom.asTWKB();
            sqlite3_result_blob(context, static_cast<const void *>(twkb.data()), twkb.size(), SQLITE_TRANSIENT);
            break;
        }
    }


}
