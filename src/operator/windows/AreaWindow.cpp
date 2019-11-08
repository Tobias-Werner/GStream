//
// Created by tobias on 29.09.19.
//
#include <operator/windows/AreaWindow.h>
#include <iostream>

using namespace STREAM;
using namespace std;

AreaWindow::AreaWindow(const std::string &point1WKT, const std::string &point2WKT,
                       std::string &geomColumnName) : ASpatialWindow(geomColumnName) {

    auto point1 = Geometry(point1WKT, 6);
    auto point2 = Geometry(point2WKT, 6);

    int type1, type2;
    int dimension1, dimension2;
    list<double> coordinates1, coordinates2;

    point1.readMetadataAndCoordinates(type1, dimension1, coordinates1);
    point2.readMetadataAndCoordinates(type2, dimension2, coordinates2);

    auto it1 = coordinates1.begin();
    auto it2 = coordinates2.begin();


    while (it1 != coordinates1.end()) {

        mins.push_back((*it1 < *it2) ? *it1 : *it2);
        maxs.push_back((*it1 > *it2) ? *it1 : *it2);

        it1++;
        it2++;
    }

}

void AreaWindow::onDataUpdate() {
    for (auto it = primaryInput.pop()->getIterator(); !it->end(); it->next()) {
        auto incomingTuple = it->get();

        auto geom = static_cast<Geometry *>(incomingTuple->getData()[geomColumnIndex].get());

        bool isInRectangle = Geometry::pointInRectangle(mins, maxs, geom);

        if (isInRectangle)
            resultSet->pushBack(incomingTuple);
    }
    publish(resultSet);
}

AreaWindow::~AreaWindow() {}