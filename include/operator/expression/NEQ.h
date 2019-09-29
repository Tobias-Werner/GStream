//
// Created by tobias on 06.08.18.
//

#ifndef STREAMS_NEQ_H
#define STREAMS_NEQ_H


#include "ACondition.h"

namespace STREAM {


    class NEQ : public ACondition {

    public:

        bool check(Long &first, Long &second) {
            return first.get() != second.get();
        }

        bool check(Double &first, Double &second) {
            return first.get() != second.get();
        }

        bool check(String &first, String &second) {
            return first.get() != second.get();
        }

        bool check(Blob &first, Blob &second) {
            return first.get() != second.get();
        }

        bool check(Null &first, Null &second) {
            return false;
        }

    };

}


#endif //STREAMS_NEQ_H
