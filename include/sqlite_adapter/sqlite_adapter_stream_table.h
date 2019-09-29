//
// Created by tobias on 02.05.18.
//

#ifndef STREAMS_SQLITE_ADAPTER_STREAM_TABLE_H
#define STREAMS_SQLITE_ADAPTER_STREAM_TABLE_H

#include <sqlite3ext.h>
#include "operator/Stream.h"

class sqlite_adapter_stream_table : public sqlite3_vtab {
private:
    STREAM::Stream *table;
public:
    STREAM::Stream *getTable() const;

    void setTable(STREAM::Stream *table);


};


#endif //STREAMS_SQLITE_ADAPTER_STREAM_TABLE_H
