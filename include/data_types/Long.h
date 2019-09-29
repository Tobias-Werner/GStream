//
// Created by tobias on 05.05.18.
//

#ifndef STREAMS_STREAM_INT_H
#define STREAMS_STREAM_INT_H

#include "ADataType.h"

namespace STREAM {

    class Long : public ADataType {

    private:
        long value;

    public:

        Long(const long &value);

        virtual std::unique_ptr<ADataType> copy() override;

        virtual void result(STREAM::AResultHandler &result_handler) override;

        const long &get();

        virtual ~Long();
    };

}

#endif //STREAMS_STREAM_INT_H
