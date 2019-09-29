//
// Created by tobias on 22.08.18.
//

#include <operator/windows/SlidingWindow.h>
#include <data_container/ListContainer.h>
#include "operator/windows/SlidingWindow.h"
#include <iostream>

using namespace std;
using namespace STREAM;
using namespace chrono;

STREAM::SlidingWindow::SlidingWindow(milliseconds duration) : duration(duration) {

}

void STREAM::SlidingWindow::onDataUpdate() {

    auto now = high_resolution_clock().now();
    auto newResultSet = make_shared<ListContainer>();

    for (auto it = resultSet->getIterator(); !it->end(); it->next()) {
        auto existingTuple = it->get();
        if (now - existingTuple->getTime() < duration)
            newResultSet->pushBack(existingTuple);
    }

    for (auto it = primaryInput.pop()->getIterator(); !it->end(); it->next()) {
        auto incomingTuple = it->get();
        if (now - incomingTuple->getTime() < duration)
            newResultSet->pushBack(incomingTuple);
    }

    resultSet = newResultSet;

    publish(resultSet);
}

STREAM::SlidingWindow::~SlidingWindow() {

}
