//
// Created by tobias on 02.05.18.
//

#ifndef STREAMS_SQLITE_ADAPTER_STREAM_VIEW_H
#define STREAMS_SQLITE_ADAPTER_STREAM_VIEW_H

#include <operator/View.h>
#include <sqlite3ext.h>


class sqlite_adapter_stream_view : public sqlite3_vtab {

private:
    STREAM::View *view;

public:
    STREAM::View *getView() const;

    void setView(STREAM::View *view);
};


#endif //STREAMS_SQLITE_ADAPTER_STREAM_VIEW_H
