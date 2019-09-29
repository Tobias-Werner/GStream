//
// Created by tobias on 05.05.18.
//

#ifndef STREAMS_ABSTRACT_DATA_TYPE_H
#define STREAMS_ABSTRACT_DATA_TYPE_H

#include <memory>
#include "result_handler/AResultHandler.h"

namespace STREAM {

    class ADataType {

    public:

        ADataType() = default;

        virtual std::unique_ptr<ADataType> copy() = 0;

        virtual void result(STREAM::AResultHandler &result_handler) = 0;

        virtual ~ADataType();
    };
}

#endif //STREAMS_ABSTRACT_DATA_TYPE_H
