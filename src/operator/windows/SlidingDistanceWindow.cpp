//
// Created by tobias on 21.08.19.
//

#include "operator/windows/SlidingDistanceWindow.h"
#include "data_types/Geometry.h"
#include "data_types/ETypes.h"

using namespace STREAM;

SlidingDistanceWindow::SlidingDistanceWindow(double length, std::string geomColumnName) : ASpatialWindow(
        geomColumnName), maxDistance(length), sumDistances(0.0) {}

void SlidingDistanceWindow::onDataUpdate() {

    for (auto it = primaryInput.pop()->getIterator(); !it->end(); it->next()) {
        auto incomingTuple = it->get();

        auto geom = static_cast<Geometry *>(incomingTuple->getData()[geomColumnIndex].get());

        if (this->resultSet->getSize() > 0) {
            auto lastInsertedTuple = resultSet->getBack();
            auto prevGeometry = static_cast<Geometry *>(lastInsertedTuple->getData()[geomColumnIndex].get());
            auto distance = Geometry::getDistance(prevGeometry, geom);

            sumDistances += distance;
            distances.push_back(distance);

            while (sumDistances >= maxDistance) {
                sumDistances -= distances.front();
                distances.pop_front();
                resultSet->removeFront();
            }
        }
        resultSet->pushBack(incomingTuple);
    }
    publish(resultSet);
}


SlidingDistanceWindow::~SlidingDistanceWindow() {}