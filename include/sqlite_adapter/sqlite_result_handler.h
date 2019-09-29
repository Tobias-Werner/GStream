//
// Created by tobias on 07.05.18.
//

#ifndef STREAMS_SQLITE_RESULT_HANDLER_H
#define STREAMS_SQLITE_RESULT_HANDLER_H

#include <sqlite3.h>
#include "result_handler/AResultHandler.h"

namespace STREAM {

    class sqlite_result_handler : public STREAM::AResultHandler {
    private:
        sqlite3_context *context;
    public:

        sqlite_result_handler(sqlite3_context *context);

        virtual void add(STREAM::Long &value) override;

        virtual void add(STREAM::Double &value) override;

        virtual void add(STREAM::String &value) override;

        virtual void add(STREAM::Blob &value) override;

        virtual void add(STREAM::Geometry &geom) override;

        virtual void add(STREAM::Null &value) override;

    };
}
#endif //STREAMS_SQLITE_RESULT_HANDLER_H
