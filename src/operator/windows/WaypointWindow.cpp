//
// Created by tobias on 02.09.19.
//

#include <operator/windows/WaypointWindow.h>
#include <data_container/ListContainer.h>

using namespace STREAM;
using namespace std;

WaypointWindow::WaypointWindow(const std::string &wkt, std::string &geomColumnName) : ASpatialWindow(geomColumnName) {
    this->waypoints = Geometry(wkt, 6);
    this->prevOverlaped = false;
}

void WaypointWindow::onDataUpdate() {
    for (auto it = primaryInput.pop()->getIterator(); !it->end(); it->next()) {
        auto incomingTuple = it->get();

        auto geom = static_cast<Geometry *>(incomingTuple->getData()[geomColumnIndex].get());

        bool overlaps = Geometry::pointOverlapsMultipoint(&waypoints, geom, 80.0);

        if (overlaps && !prevOverlaped) {
            prevOverlaped = true;
            resultSet = make_shared<ListContainer>();

        } else if (!overlaps && prevOverlaped) {
            prevOverlaped = false;
        }

        resultSet->pushBack(incomingTuple);

    }
    publish(resultSet);
}

WaypointWindow::~WaypointWindow() {}