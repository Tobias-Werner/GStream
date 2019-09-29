//
// Created by tobias on 20.09.19.
//

#include <data_container/ListContainer.h>
#include "operator/windows/SessionDistanceWindow.h"

using namespace STREAM;
using namespace std;

SessionDistanceWindow::SessionDistanceWindow(double gap, std::string geomColumnName) : ASpatialWindow(geomColumnName),
                                                                                       gap(gap) {

}

void SessionDistanceWindow::onDataUpdate() {


    if (resultSet->getSize() > 0) {

        auto prevGeom = static_cast<Geometry *>(resultSet->getBack()->getData()[geomColumnIndex].get());

        for (auto it = primaryInput.pop()->getIterator(); !it->end(); it->next()) {
            auto incomingTuple = it->get();

            auto geom = static_cast<Geometry *>(incomingTuple->getData()[geomColumnIndex].get());

            if (Geometry::getDistance(prevGeom, geom) > gap)
                resultSet = make_shared<ListContainer>();

            resultSet->pushBack(incomingTuple);
        }
    } else
        for (auto it = primaryInput.pop()->getIterator(); !it->end(); it->next())
            resultSet->pushBack(it->get());

    publish(resultSet);

}

SessionDistanceWindow::~SessionDistanceWindow() {}