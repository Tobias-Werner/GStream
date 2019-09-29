//
// Created by tobias on 09.08.18.
//

#include <operator/View.h>

#include "operator/View.h"

using namespace std;
using namespace STREAM;

View::View(std::string name) : name(name) {

}

void View::onDataUpdate() {
    data = primaryInput.pop();
}

void View::updateSchema() {
    schema = primaryInput.getSrcOperator()->getSchema();
}

shared_ptr<AStreamContainer> &View::getData() {
    refresh();
    return data;
}

void View::refresh() {
    if (isTimeBased)
        triggerPrevOperator();
}

void View::setToTimeBased() {
    isTimeBased = true;
}

void View::triggerPrevOperator() {
    primaryInput.getSrcOperator()->triggerPrevOperator();
}

std::string View::getName() {
    return name;
}

View::~View() {

}


