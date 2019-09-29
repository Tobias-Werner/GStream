//
// Created by tobias on 05.05.18.
//

#ifndef STREAMS_STREAM_STRING_H
#define STREAMS_STREAM_STRING_H

#include <string>
#include "ADataType.h"

namespace STREAM {

    class String : public ADataType {

    private:
        std::string value;

    public:
        String(const std::string &value);

        virtual std::unique_ptr<ADataType> copy() override;

        virtual void result(STREAM::AResultHandler &result_handler) override;

        const std::string &get();

        virtual ~String();
    };
}

#endif //STREAMS_STREAM_STRING_H
