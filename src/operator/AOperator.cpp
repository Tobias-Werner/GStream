//
// Created by tobias on 30.07.18.
//

#include <operator/AOperator.h>

#include "operator/AOperator.h"

using namespace std;
using namespace STREAM;

AOperator::AOperator() : primaryInput(Input(this)) {

}

void AOperator::setSrc(std::shared_ptr<AOperator> src) {
    src->addNextInput(primaryInput);
    primaryInput.set(src);
}

shared_ptr<Tuple> AOperator::createTuple() {
    return make_shared<Tuple>(schema.size());
}

vector<Attribute> AOperator::getSchema() {
    return schema;
}

void AOperator::publish(shared_ptr<AStreamContainer> container) {
    for (auto &o : nextOperator)
        o->process(container);
}


void AOperator::addNextInput(Input &node) {
    nextOperator.push_back(&node);
}


bool AOperator::hasAttribute(string name) {
    for (auto &attribute : schema)
        if (attribute.getName() == name)
            return true;

    return false;
}

AOperator::~AOperator() {}


