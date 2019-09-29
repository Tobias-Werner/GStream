//
// Created by tobias on 08.05.18.
//

#ifndef STREAMS_MISC_H
#define STREAMS_MISC_H

#include <memory>

namespace std {

    template<typename T, typename ...Args>
    unique_ptr<T> make_unique(Args &&...args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }


}

#endif //STREAMS_MISC_H
