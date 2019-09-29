//
// Created by tobias on 01.02.18.
//

#ifndef SPREAMS_STREAM_TUPEL_H
#define SPREAMS_STREAM_TUPEL_H

#include <chrono>
#include <vector>
#include <memory>
#include <data_types/ADataType.h>

namespace STREAM {

    class Tuple {

    private:
        std::vector<std::unique_ptr<STREAM::ADataType>> columns;
        std::chrono::system_clock::time_point creationTime;

    public:

        Tuple(size_t colSize);

        Tuple(size_t colSize, std::chrono::system_clock::time_point creationTime);

        Tuple(const Tuple &other) = delete;

        void setCreationTime(const std::chrono::system_clock::time_point &creationTime);

        const std::chrono::high_resolution_clock::time_point &getTime() const;

        void push_back(std::unique_ptr<STREAM::ADataType> &&data);

        void set(size_t idx, std::unique_ptr<STREAM::ADataType> data);

        const std::vector<std::unique_ptr<STREAM::ADataType>> &getData() const;

        long long int getRowId() const;

        virtual ~Tuple();

    };
}

#endif //SPREAMS_STREAM_TUPEL_H
