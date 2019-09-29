//
// Created by tobias on 06.08.18.
//

#ifndef STREAMS_GTE_H
#define STREAMS_GTE_H


#include "ACondition.h"

namespace STREAM {


    class GTE : public ACondition {

    public:

        bool check(Long &first, Long &second) {
            return first.get() >= second.get();
        }

        bool check(Double &first, Double &second) {
            return first.get() >= second.get();
        }

        bool check(String &first, String &second) {
            return first.get() >= second.get();
        }

        bool check(Blob &first, Blob &second) {
            return first.get() >= second.get();
        }

        bool check(Null &first, Null &second) {
            return true;
        }

    };

}

#endif //STREAMS_GTE_H
