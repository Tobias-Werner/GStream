//
// Created by tobias on 05.05.18.
//

#ifndef STREAMS_STREAM_DOUBLE_H
#define STREAMS_STREAM_DOUBLE_H

#include "ADataType.h"

namespace STREAM {

    class Double : public ADataType {

    private:
        double value;

    public:

        Double(const double &value);

        virtual std::unique_ptr<ADataType> copy() override;

        virtual void result(STREAM::AResultHandler &result_handler) override;

        const double &get();

        virtual ~Double();
    };
}

#endif //STREAMS_STREAM_DOUBLE_H
