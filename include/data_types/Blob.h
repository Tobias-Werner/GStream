//
// Created by tobias on 05.05.18.
//

#ifndef STREAMS_STREAM_BLOB_H
#define STREAMS_STREAM_BLOB_H

#include "ADataType.h"
#include <vector>

namespace STREAM {

    class Blob : public STREAM::ADataType {

    protected:
        std::vector<unsigned char> value;

    public:

        Blob() = default;

        Blob(const std::vector<unsigned char> &value);

        virtual std::unique_ptr<ADataType> copy() override;

        virtual void result(STREAM::AResultHandler &result_handler) override;

        std::vector<unsigned char> &get();

        void setValue(const std::vector<unsigned char> &value);

        virtual ~Blob();
    };
}

#endif //STREAMS_STREAM_BLOB_H




