//
// Created by tobias on 10.04.18.
//

#ifndef STREAMS_STREAM_DATA_CONTAINER_H
#define STREAMS_STREAM_DATA_CONTAINER_H

#include "Tuple.h"
#include "AStreamIterator.h"
#include "Attribute.h"
#include <list>

namespace STREAM {

    class AStreamContainer {


    public:

        AStreamContainer() = default;

        virtual std::unique_ptr<STREAM::AStreamIterator> getIterator() = 0;

        virtual size_t getSize() = 0;

        virtual void pushBack(std::shared_ptr<Tuple> tuple) = 0;

        virtual std::shared_ptr<Tuple> getBack() = 0;

        virtual void removeFront() = 0;

        virtual ~AStreamContainer();
    };


}
#endif //STREAMS_STREAM_DATA_CONTAINER_H
