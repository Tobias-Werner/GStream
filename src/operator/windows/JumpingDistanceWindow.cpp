//
// Created by tobias on 29.09.19.
//

#include "operator/windows/JumpingDistanceWindow.h"
#include "data_types/Geometry.h"
#include "data_types/ETypes.h"

using namespace std;
using namespace STREAM;

JumpingDistanceWindow::JumpingDistanceWindow(double distance, std::string geomColumnName) : ASpatialWindow(
        geomColumnName), distance(distance), sumDistances(0) {}

void JumpingDistanceWindow::onDataUpdate() {
    for (auto it = primaryInput.pop()->getIterator(); !it->end(); it->next()) {
        auto incomingTuple = it->get();

        if (resultSet->getSize() > 0) {

            auto geom = static_cast<Geometry *>(incomingTuple->getData()[geomColumnIndex].get());

            auto lastInsertedTuple = resultSet->getBack();
            auto prevGeometry = static_cast<Geometry *>(lastInsertedTuple->getData()[geomColumnIndex].get());

            sumDistances += Geometry::getDistance(prevGeometry, geom);

            if (sumDistances > distance) {
                resultSet->pushBack(incomingTuple);
                sumDistances = 0;
            }
        } else {
            resultSet->pushBack(incomingTuple);
        }


    }
    publish(resultSet);
}

JumpingDistanceWindow::~JumpingDistanceWindow() {}