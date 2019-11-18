%include
{
 #include <cassert>
 #include <iostream>
 #include "parser/token.h"
 #include "data_types/ETypes.h"
 #include "Manager.h"
 #include "operator/Operators.h"
}

%syntax_error
{
 std::cout << "Parser Error." << std::endl;
}

%parse_accept {

}

%token_type {STREAM::token*}

%type dataType {STREAM::ETypes}

%type identifierList {std::list<std::string*>*}

%type attribute {STREAM::Attribute*}

%type attributeList {std::list<STREAM::Attribute>*}

%type operator {STREAM::ACondition*}

%type condition {STREAM::ACondition*}

%type conditionList {std::list<STREAM::ACondition>*}

%type window {STREAM::AWindow*}

%type aggregation {STREAM::AAggregation*}

%type viewCreationClause {STREAM::View*}

%type selectionClause {STREAM::AOperator*}

%extra_argument {STREAM::Manager* manager}


// +================================+
// |              START             |
// +================================+

start ::= statement K_SEMICOLON .

statement ::= creation .

statement ::= insertion .

// +================================+
// |          CREATE STREAM         |
// +================================+

creation ::= K_CREATE K_STREAM IDENTIFIER(A) K_OPEN_BRACKET attributeList(B) K_CLOSE_BRACKET .
{
    for(auto& a : *B)
        a.setSrc(*(A->stringValue));

    manager->add(new STREAM::Stream(*(A->stringValue), *B));
    delete B;
}


// +================================+
// |           CREATE VIEW          |
// +================================+

creation ::= viewCreationClause(B) selectionClause(C) fromClause(D) window(E) .
{
    std::shared_ptr<STREAM::AOperator> selection(C);
    std::shared_ptr<STREAM::AOperator> stream = manager->getStream(*(D->stringValue));
    std::shared_ptr<STREAM::AOperator> window(E);

    window->setSrc(stream);
    selection->setSrc(window);
    B->setSrc(selection);

    manager->add(B);
}

creation ::= viewCreationClause(B) selectionClause(C) fromClause(D) K_JOIN identifierList(E) K_ON conditionList(F) window(G).
{
    auto join = std::make_shared<STREAM::Join>(*F);
    std::shared_ptr<STREAM::AOperator> windowLeft(G);

    //std::shared_ptr<STREAM::AOperator> windowRight = std::make_shared<STREAM::AWindow>(*G);

    std::shared_ptr<STREAM::AOperator> windowRight(G);
    std::shared_ptr<STREAM::AOperator> selection(C);

    std::shared_ptr<STREAM::AOperator> streamLeft = manager->getStream(*(D->stringValue));
    std::shared_ptr<STREAM::AOperator> streamRight = manager->getStream(*(E->front()));

    windowLeft->setSrc(streamLeft);
    windowRight->setSrc(streamRight);

    join->setSrc(windowLeft);
    join->setSecondarySrc(windowRight);

    selection->setSrc(join);
    B->setSrc(selection);

    manager->add(B);
}

viewCreationClause(A) ::= K_CREATE K_VIEW IDENTIFIER(B) K_AS .
{
    A = new STREAM::View(*(B->stringValue));
}

selectionClause(A) ::= K_SELECT attributeList(B)  .
{
    A = new STREAM::Select(*B);
    delete B;
}

selectionClause(A) ::= K_SELECT aggregation(B) .
{
    A = B;
}

fromClause(A) ::= K_FROM IDENTIFIER(B) .
{
    A = B;
}

// +================================+
// |              WINDOW            |
// +================================+


window(A) ::= K_OPEN_SQUARE_BRACKET K_SLIDE V_LONG(B) K_MS K_CLOSE_SQUARE_BRACKET. {
    std::chrono::milliseconds ms(*(B->longValue));
    A = new STREAM::SlidingWindow(ms);
}

window(A) ::= K_OPEN_SQUARE_BRACKET K_TILT V_LONG(B) K_MS K_CLOSE_SQUARE_BRACKET. {
    std::chrono::milliseconds ms(*(B->longValue));
    A = new STREAM::TiltingWindow(ms);
}

window(A) ::= K_OPEN_SQUARE_BRACKET K_SLIDE V_DOUBLE(B) K_M K_ON IDENTIFIER(C) K_CLOSE_SQUARE_BRACKET. {
    A = new STREAM::SlidingDistanceWindow(*(B->doubleValue), *(C->stringValue));
}

window(A) ::= K_OPEN_SQUARE_BRACKET K_TILT V_DOUBLE(B) K_M K_ON IDENTIFIER(C) K_CLOSE_SQUARE_BRACKET. {
    A = new STREAM::TiltingDistanceWindow(*(B->doubleValue), *(C->stringValue));
}

window(A) ::= K_OPEN_SQUARE_BRACKET K_WAY V_STRING(B) K_ON IDENTIFIER(C) K_CLOSE_SQUARE_BRACKET. {
    std::string wkt = *(B->stringValue);
    wkt = wkt.substr(1, wkt.size() - 2);
    A = new STREAM::WaypointWindow(wkt, *(C->stringValue));
}

window(A) ::= K_OPEN_SQUARE_BRACKET K_SESSION V_DOUBLE(B) K_M K_ON IDENTIFIER(C) K_CLOSE_SQUARE_BRACKET. {
    A = new STREAM::SessionDistanceWindow(*(B->doubleValue), *(C->stringValue));
}

window(A) ::= K_OPEN_SQUARE_BRACKET K_JUMPING V_DOUBLE(B) K_M K_ON IDENTIFIER(C) K_CLOSE_SQUARE_BRACKET. {
    A = new STREAM::JumpingDistanceWindow(*(B->doubleValue), *(C->stringValue));
}

window(A) ::= K_OPEN_SQUARE_BRACKET K_AREA V_STRING(B) V_STRING(C) K_ON IDENTIFIER(D) K_CLOSE_SQUARE_BRACKET. {

    std::string wkt1 = *(B->stringValue);
    wkt1 = wkt1.substr(1, wkt1.size() - 2);

    std::string wkt2 = *(C->stringValue);
    wkt2 = wkt2.substr(1, wkt2.size() - 2);

    A = new STREAM::AreaWindow(wkt1,wkt2, *(D->stringValue));
}


// +================================+
// |            INSERTION           |
// +================================+

insertion ::= K_INSERT K_INTO IDENTIFIER K_OPEN_BRACKET attributeList(A) K_CLOSE_BRACKET K_VALUES K_OPEN_BRACKET valueList K_CLOSE_BRACKET .
{
    delete A;
}



// +================================+
// |         ATTRIBUTE NAMES        |
// +================================+

attributeList(A) ::= attributeList(B) K_COMA attribute(C) .
{
    B->push_back(*C);
    delete C;
    A = B;
}

attributeList(A) ::= attribute(B) .
{
    A = new std::list<STREAM::Attribute>({*B});
    delete B;
}

attribute(A) ::= IDENTIFIER(B) .
{
    A = new STREAM::Attribute(*(B->stringValue));
}

attribute(A) ::= IDENTIFIER(B) dataType(C) .
{
    A = new STREAM::Attribute(*(B->stringValue), C);
}

attribute(A) ::= IDENTIFIER(B) K_POINT IDENTIFIER(C) .
{
    A = new STREAM::Attribute(*(B->stringValue), *(C->stringValue));
}


// +================================+
// |           IDENTIFIER           |
// +================================+

identifierList(A) ::= IDENTIFIER(B) .
{
    A = new std::list<std::string*>({B->stringValue});
}

identifierList(A) ::= identifierList(B) K_COMA IDENTIFIER(C) .
{
    B->push_back(C->stringValue);
    A = B;
}


// +================================+
// |             VALUES             |
// +================================+

valueList ::= valueList K_COMA value .

valueList ::= value .

value ::= V_DOUBLE .

value ::= V_LONG .

value ::= V_STRING .



// +================================+
// |           CONDITION            |
// +================================+

conditionList ::= condition K_AND condition .

conditionList ::= condition K_OR condition .

conditionList(A) ::= condition(B) .
{
    A = new std::list<STREAM::ACondition>({*B});
    delete B;
}

condition(A) ::= attribute(B) operator(C) attribute(D) .
{
    C->setFirst(*B);
    C->setSecond(*D);
    A = C;

    delete B;
    delete D;
}

operator(A) ::= K_EQUAL .
{
    A = new STREAM::EQ();
}

operator(A) ::= K_GREATER_THAN .
{
    A = new STREAM::GT();
}

operator(A) ::= K_GRATER_THAN_EQUAL .
{
    A = new STREAM::GTE();
}

operator(A) ::= K_LESSER_THAN .
{
    A = new STREAM::LT();
}

operator(A) ::= K_LESSER_THAN_EQUAL .
{
    A = new STREAM::LTE();
}

operator(A) ::= K_NOT_EQUAL .
{
    A = new STREAM::NEQ();
}



// +================================+
// |          ATTRIBUTE DESC       |
// +================================+









// +================================+
// |           AGGREGATIONS         |
// +================================+

aggregation(A) ::= K_MAX K_OPEN_SQUARE_BRACKET attribute(B) K_CLOSE_SQUARE_BRACKET.
{
    A = new STREAM::Max(*B);
}

aggregation ::= K_MIN K_OPEN_SQUARE_BRACKET attribute(B) K_CLOSE_SQUARE_BRACKET.
{

}



// +================================+
// |            DATATYPES          |
// +================================+

dataType(A) ::= K_DOUBLE .
{
    A = STREAM::ETypes::DOUBLE;
}

dataType(A) ::= K_INTEGER .
{
    A = STREAM::ETypes::LONG;
}

dataType(A) ::= K_STRING .
{
    A = STREAM::ETypes::STRING;
}

dataType(A) ::= K_BLOB .
{
    A = STREAM::ETypes::BLOB;
}

dataType(A) ::= K_GEOMETRY .
{
    A = STREAM::ETypes::GEOMETRY;
}

