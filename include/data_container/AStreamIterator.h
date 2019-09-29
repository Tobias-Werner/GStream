//
// Created by tobias on 11.04.18.
//

#ifndef STREAMS_BASIC_STREAM_ITERATOR_H
#define STREAMS_BASIC_STREAM_ITERATOR_H

#include <memory>
#include "Tuple.h"

namespace STREAM {

    class AStreamIterator {

    public:

        AStreamIterator() = default;

        virtual void next() = 0;

        virtual bool end() = 0;

        virtual std::shared_ptr<STREAM::Tuple> get() = 0;

        virtual ~AStreamIterator();

    };
}

#endif //STREAMS_BASIC_STREAM_ITERATOR_H
