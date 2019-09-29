//
// Created by tobias on 05.05.18.
//

#include <data_types/Blob.h>
#include <make_unique.h>
#include "data_types/Blob.h"

using namespace std;
using namespace STREAM;

Blob::Blob(const vector<unsigned char> &value) : value(value) {}

void Blob::result(AResultHandler &result_handler) {
    result_handler.add(*this);
}

vector<unsigned char> &Blob::get() {
    return value;
}

unique_ptr<ADataType> Blob::copy() {
    return make_unique<Blob>(value);
}

void Blob::setValue(const vector<unsigned char> &value) {
    Blob::value = value;
}

Blob::~Blob() {}
