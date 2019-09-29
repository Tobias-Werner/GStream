//
// Created by tobias on 12.04.18.
//

#include <data_container/ListContainer.h>

#include "data_container/ListContainer.h"
#include "data_container/ListIterator.h"
#include "make_unique.h"

using namespace std;
using namespace STREAM;

unique_ptr<AStreamIterator> ListContainer::getIterator() {
    return make_unique<ListIterator>(this);
}

void ListContainer::pushBack(shared_ptr<Tuple> tupel) {
    data.push_back(tupel);
}

std::shared_ptr<Tuple> ListContainer::getBack() {
    return data.back();
}

void ListContainer::removeFront() {
    data.pop_front();
}

size_t ListContainer::getSize() {
    return data.size();
}

list<shared_ptr<Tuple>> ListContainer::get_snapshot() {
    return data;
}

ListContainer::~ListContainer() {}
