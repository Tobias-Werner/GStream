//
// Created by tobias on 29.05.18.
//

#ifndef STREAMS_STREAM_NULL_H
#define STREAMS_STREAM_NULL_H


#include "ADataType.h"

namespace STREAM {

    class Null : public ADataType {

    public:

        virtual std::unique_ptr<ADataType> copy() override;

        virtual void result(AResultHandler &result_handler) override;

    };

}


#endif //STREAMS_STREAM_NULL_H
