//
// Created by tobias on 05.05.18.
//

#include <data_types/Long.h>
#include <make_unique.h>

#include "data_types/Long.h"

using namespace std;
using namespace STREAM;

Long::Long(const long &value) : value(value) {}

void Long::result(AResultHandler &result_handler) {
    result_handler.add(*this);
}
const long &Long::get() {
    return value;
}

unique_ptr<ADataType> Long::copy() {
    return make_unique<Long>(value);
}

Long::~Long() {}
