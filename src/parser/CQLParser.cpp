//
// Created by tobias on 26.06.18.
//
#include <iostream>
#include <list>
#include <Manager.h>

#include "parser/CQLParser.h"
#include "parser/parser.h"

using namespace std;
using namespace STREAM;

CQLParser::CQLParser(Manager &manager) : manager(manager) {}

void CQLParser::parse(const string &cql) {

    void *parser = ParseAlloc(malloc);

    yyscan_t scanner;
    yylex_init(&scanner);
    YY_BUFFER_STATE bufferState;

    bufferState = yy_scan_string(cql.c_str(), scanner);

    list<STREAM::token> tokens;

    while (true) {

        tokens.push_back(token());
        auto &token = tokens.back();

        token.lexcode = my_scan(scanner, token);
        Parse(parser, token.lexcode, &token, &manager);


        if (token.lexcode == 0) break;

    }

    for (auto &t : tokens)
        switch (t.lexcode) {
            case IDENTIFIER :
                delete t.stringValue;
                break;
            case V_LONG :
                delete t.longValue;
                break;
            case V_DOUBLE :
                delete t.doubleValue;
                break;
            case V_STRING:
                delete t.stringValue;
                break;
        }

    yy_delete_buffer(bufferState, scanner);
    yylex_destroy(scanner);

    ParseFree(parser, free);
}
