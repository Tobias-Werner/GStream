//
// Created by tobias on 29.08.18.
//

#include <operator/windows/TiltingWindow.h>
#include <data_container/ListContainer.h>
#include <iostream>

#include "operator/windows/TiltingWindow.h"

using namespace std;
using namespace STREAM;
using namespace chrono;

STREAM::TiltingWindow::TiltingWindow(std::chrono::milliseconds duration) : buffer(make_shared<ListContainer>()),
                                                                           duration(duration),
                                                                           begin(high_resolution_clock::now()) {

}

void STREAM::TiltingWindow::onDataUpdate() {
    auto now = high_resolution_clock().now();

    if ((now - begin) > duration) {
        resultSet = buffer;
        buffer = make_shared<ListContainer>();
        begin = now;
    }

    for (auto newTupleIterator = primaryInput.pop()->getIterator(); !newTupleIterator->end(); newTupleIterator->next())
        buffer->pushBack(newTupleIterator->get());

    publish(resultSet);

}

STREAM::TiltingWindow::~TiltingWindow() {

}
