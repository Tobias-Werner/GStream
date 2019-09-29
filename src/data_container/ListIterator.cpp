//
// Created by tobias on 12.04.18.
//

#include "data_container/ListIterator.h"

using namespace std;
using namespace STREAM;

ListIterator::ListIterator(ListContainer *container) {
    snapshot = container->get_snapshot();
    iterator = snapshot.begin();
}

void ListIterator::next() {
    iterator++;
}

bool ListIterator::end() {
    return iterator == snapshot.end();
}

shared_ptr<Tuple> ListIterator::get() {
    return *iterator;
}

ListIterator::~ListIterator() {

}
