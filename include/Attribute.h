//
// Created by tobias on 29.01.18.
//

#ifndef SPREAMS_STREAM_COLUMN_DESC_H
#define SPREAMS_STREAM_COLUMN_DESC_H

#include <string>
#include <data_types/ETypes.h>

namespace STREAM {

    class Attribute {

    private:

        size_t index;
        std::string name;
        std::string src;
        STREAM::ETypes type;

    public:

        Attribute() = default;

        Attribute(std::string name);

        Attribute(std::string src, std::string name);

        Attribute(std::string name, STREAM::ETypes type);

        bool operator==(const Attribute &other);

        bool hasSrc();

        void setName(const std::string &name);

        void setSrc(const std::string &src);

        void setType(ETypes type);

        size_t getIndex() const;

        void setIndex(size_t index);

        std::string &getSrc();

        ETypes getType();

        std::string &getName();


    };
}

#endif //SPREAMS_STREAM_COLUMN_DESC_H
