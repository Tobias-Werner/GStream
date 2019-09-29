//
// Created by tobias on 31.01.18.
//

#ifndef SPREAMS_STREAM_CURSOR_H
#define SPREAMS_STREAM_CURSOR_H

#include <sqlite3ext.h>
#include "operator/Stream.h"
#include "operator/View.h"
#include <vector>

SQLITE_EXTENSION_INIT3

namespace STREAM {

    class sqlite_adapter_cursor : public sqlite3_vtab_cursor {

    private:
        const STREAM::View *owner;
        std::unique_ptr<STREAM::AStreamIterator> iterator;

    public:
        sqlite_adapter_cursor(STREAM::View *owner);

        void next();

        bool end();

        std::shared_ptr<STREAM::Tuple> get();

        const View *get_owner() const;

    };


}
#endif //SPREAMS_STREAM_CURSOR_H
