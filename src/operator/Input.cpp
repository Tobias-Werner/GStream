//
// Created by tobias on 30.07.18.
//
#include "operator/AOperator.h"
#include "operator/Input.h"

using namespace STREAM;
using namespace std;

Input::Input(AOperator *owner) : owner(owner) {}

void Input::set(shared_ptr<AOperator> srcOperator) {
    this->srcOperator = srcOperator;
    owner->updateSchema();
}

void Input::process(shared_ptr<AStreamContainer> data) {
    this->data = data;
    owner->onDataUpdate();
}

shared_ptr<AStreamContainer> Input::pop() {
    return std::move(data);
}

bool Input::hasChanged() {
    return data != nullptr;
}

shared_ptr<AOperator> Input::getSrcOperator() {
    return srcOperator;
}

Input::~Input() {}
