//
// Created by tobias on 24.05.18.
//

#ifndef STREAMS_CONSOLE_RESULT_HANDLER_H
#define STREAMS_CONSOLE_RESULT_HANDLER_H


#include "AResultHandler.h"

namespace STREAM {

    class ConsoleResultHandler : public AResultHandler {
    public:
        virtual void onBegin() override;

        virtual void add(STREAM::Long &value) override;

        virtual void add(STREAM::Double &value) override;

        virtual void add(STREAM::String &value) override;

        virtual void add(STREAM::Blob &value) override;

        virtual void add(STREAM::Geometry &geom) override;

        virtual void add(STREAM::Null &value) override;

        virtual void onEnd() override;

        virtual ~ConsoleResultHandler();
    };

}


#endif //STREAMS_CONSOLE_RESULT_HANDLER_H
