//
// Created by tobias on 26.06.18.
//

#ifndef PARSER_TOKENTYPE_H
#define PARSER_TOKENTYPE_H

#include <string>

namespace STREAM {

    struct token {
        int lexcode;
        std::string *stringValue;
        long *longValue;
        double *doubleValue;
    };

}


#endif //PARSER_TOKENTYPE_H
