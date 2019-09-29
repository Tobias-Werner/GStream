//
// Created by tobias on 05.05.18.
//

#include <make_unique.h>
#include "data_types/Double.h"

using namespace std;
using namespace STREAM;

Double::Double(const double &value) : value(value) {

}

void Double::result(AResultHandler &result_handler) {
    result_handler.add(*this);
}

const double &Double::get() {
    return value;
}

unique_ptr<ADataType> Double::copy() {
    return make_unique<Double>(value);
}

Double::~Double() {}
