//
// Created by tobias on 02.05.18.
//

#include "sqlite_adapter/sqlite_adapter_stream_table.h"

using namespace std;
using namespace STREAM;

Stream *sqlite_adapter_stream_table::getTable() const {
    return table;
}

void sqlite_adapter_stream_table::setTable(Stream *table) {
    sqlite_adapter_stream_table::table = table;
}
