//
// Created by tobias on 27.01.18.
//

#include <operator/Stream.h>
#include <data_container/ListContainer.h>

#include "operator/Stream.h"

using namespace std;
using namespace STREAM;

Stream::Stream(string name, const std::list<Attribute> attributes) : name(name) {
    for (auto &attribute : attributes)
        schema.push_back(attribute);
}

string Stream::getName() {
    return name;
}

void Stream::insert(shared_ptr<Tuple> &tupel) {
    auto container = make_shared<ListContainer>();
    container->pushBack(tupel);
    publish(container);
}

void Stream::onDataUpdate() {
    // Nothing. Stream is entry and not part of automatic data pulling
}

void Stream::updateSchema() {
    // Nothing. Streams hopefully never change their schema
}

void Stream::triggerPrevOperator() {
    auto container = make_shared<ListContainer>();
    publish(container);
}

Stream::~Stream() {

}

