//
// Created by tobias on 12.04.18.
//

#ifndef STREAMS_LIST_STREAM_ITERATOR_H
#define STREAMS_LIST_STREAM_ITERATOR_H


#include "AStreamIterator.h"
#include "ListContainer.h"

namespace STREAM {

    class ListIterator : public STREAM::AStreamIterator {

    private:
        std::list<std::shared_ptr<STREAM::Tuple>> snapshot;
        std::list<std::shared_ptr<STREAM::Tuple>>::iterator iterator;
    public:

        ListIterator(STREAM::ListContainer *container);

        virtual void next() override;

        virtual bool end() override;

        virtual std::shared_ptr<STREAM::Tuple> get() override;

        ~ListIterator();

    };

}

#endif //STREAMS_LIST_STREAM_ITERATOR_H
