//
// Created by tobias on 07.08.18.
//

#ifndef STREAMS_CONDITION_H
#define STREAMS_CONDITION_H

#include <data_types/Long.h>
#include <data_types/Double.h>
#include <data_types/Blob.h>
#include <data_types/String.h>
#include <data_types/Null.h>
#include <Attribute.h>

namespace STREAM {

    class ACondition {

    private:

        Attribute first;

        Attribute second;

    public:

        virtual bool check(Long &first, Long &second);

        virtual bool check(Double &first, Double &second);

        virtual bool check(String &first, String &second);

        virtual bool check(Blob &first, Blob &second);

        virtual bool check(Null &first, Null &second);

        Attribute &getLeft();

        void setFirst(const Attribute &first);

        Attribute &getRight();

        void setSecond(const Attribute &second);

        virtual ~ACondition();
    };
}


#endif //STREAMS_CONDITION_H
