//
// Created by tobias on 06.08.18.
//

#ifndef STREAMS_LTE_H
#define STREAMS_LTE_H


#include "ACondition.h"

namespace STREAM {


    class LTE : public ACondition {

    public:

        bool check(Long &first, Long &second) {
            return first.get() <= second.get();
        }

        bool check(Double &first, Double &second) {
            return first.get() <= second.get();
        }

        bool check(String &first, String &second) {
            return first.get() <= second.get();
        }

        bool check(Blob &first, Blob &second) {
            return first.get() <= second.get();
        }

        bool check(Null &first, Null &second) {
            return false;
        }

    };

}


#endif //STREAMS_LTE_H
