//
// Created by tobias on 26.06.18.
//

#ifndef PARSER_CQLPARSER_H
#define PARSER_CQLPARSER_H

#include <cstdlib>
#include <string>
#include "scanner.h"
#include "token.h"
#include "Manager.h"

int my_scan(yyscan_t yyscanner, STREAM::token &token);

void *ParseAlloc(void *(*allocProc)(size_t));

void Parse(void *parser, int token, STREAM::token *tokenInfo, STREAM::Manager *manager);

void ParseFree(void *parser, void(*freeProc)(void *));

namespace STREAM {

    class CQLParser {

    private:
        STREAM::Manager &manager;

    public:

        CQLParser(STREAM::Manager &manager);

        void parse(const std::string &cql);

    };

}


#endif //PARSER_CQLPARSER_H
