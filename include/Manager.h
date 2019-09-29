//
// Created by tobias on 02.03.18.
//

#ifndef STREAMS_STREAM_MANAGER_H
#define STREAMS_STREAM_MANAGER_H

#include <map>
#include <iostream>
#include "string"
#include "operator/Stream.h"
#include "operator/View.h"

namespace STREAM {

    class Manager {

    private:

        std::map<std::string, std::shared_ptr<STREAM::Stream> > streams;

        std::map<std::string, std::shared_ptr<STREAM::View> > views;

    public:

        void add(STREAM::Stream* stream);

        void add(STREAM::View* view);

        const std::shared_ptr<STREAM::Stream> getStream(std::string name);

        const std::shared_ptr<STREAM::View> getView(std::string name);
    };


}


#endif //STREAMS_STREAM_MANAGER_H
