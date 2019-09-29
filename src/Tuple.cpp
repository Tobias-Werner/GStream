//
// Created by tobias on 01.02.18.
//


#include <make_unique.h>
#include <Tuple.h>
#include <iostream>


#include "data_types/Null.h"
#include "Tuple.h"

using namespace std;
using namespace STREAM;
using namespace chrono;

Tuple::Tuple(size_t colSize) : Tuple(colSize, system_clock::now()) {

}

Tuple::Tuple(size_t colSize, std::chrono::system_clock::time_point creationTime) : creationTime(creationTime) {
    columns.reserve(colSize);
    for (int i = 0; i < colSize; i++)
        columns.push_back(std::move(make_unique<Null>()));
}

void Tuple::set(size_t idx, unique_ptr<ADataType> data) {
    columns[idx] = move(data);
}

const vector<unique_ptr<ADataType>> &Tuple::getData() const {
    return columns;
}

void Tuple::setCreationTime(const chrono::system_clock::time_point &creationTime) {
    Tuple::creationTime = creationTime;
}

const chrono::system_clock::time_point &Tuple::getTime() const {
    return creationTime;
}

long long int Tuple::getRowId() const {
    return duration_cast<milliseconds>(creationTime.time_since_epoch()).count();
}

void Tuple::push_back(unique_ptr<ADataType> &&data) {
    columns.push_back(move(data));
}

Tuple::~Tuple() {

}



