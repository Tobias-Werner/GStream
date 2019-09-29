//
// Created by tobias on 05.05.18.
//


#include <make_unique.h>
#include "data_types/String.h"

using namespace std;
using namespace STREAM;

String::String(const string &value) : value(value) {

}

void String::result(AResultHandler &result_handler) {
    result_handler.add(*this);
}

const string &String::get() {
    return value;
}

unique_ptr<ADataType> String::copy() {
    return make_unique<String>(value);
}

String::~String() {}
