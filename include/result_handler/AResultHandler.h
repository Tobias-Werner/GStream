//
// Created by tobias on 05.05.18.
//

#ifndef STREAMS_ABSTRACT_RESULT_HANDLER_H
#define STREAMS_ABSTRACT_RESULT_HANDLER_H

namespace STREAM {

    class Long;

    class Double;

    class String;

    class Blob;

    class Geometry;

    class Null;

    class AResultHandler {
    public:

        AResultHandler() = default;

        virtual void onBegin();

        virtual void add(STREAM::Long &value) = 0;

        virtual void add(STREAM::Double &value) = 0;

        virtual void add(STREAM::String &value) = 0;

        virtual void add(STREAM::Blob &value) = 0;

        virtual void add(STREAM::Geometry &value) = 0;

        virtual void add(STREAM::Null &value) = 0;

        virtual void onEnd();

        virtual ~AResultHandler();

    };

}
#endif //STREAMS_ABSTRACT_RESULT_HANDLER_H
