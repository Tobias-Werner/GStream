//
// Created by tobias on 12.04.18.
//

#ifndef STREAMS_LIST_STREAM_CONTAINER_H
#define STREAMS_LIST_STREAM_CONTAINER_H

#include "AStreamContainer.h"

namespace STREAM {

    class ListContainer : public STREAM::AStreamContainer {

    private:
        std::list<std::shared_ptr<STREAM::Tuple>> data;

    public:

        ListContainer() = default;

        virtual std::unique_ptr<STREAM::AStreamIterator> getIterator() override;

        virtual void pushBack(std::shared_ptr<Tuple> tupel) override;

        virtual std::shared_ptr<Tuple> getBack() override;

        virtual void removeFront() override;

        virtual size_t getSize() override;

        std::list<std::shared_ptr<STREAM::Tuple>> get_snapshot();

        virtual ~ListContainer();
    };

}
#endif //STREAMS_LIST_STREAM_CONTAINER_H
