//
// Created by tobias on 28.08.19.
//

#include <operator/windows/TiltingDistanceWindow.h>
#include <data_container/ListContainer.h>


using namespace STREAM;
using namespace std;

TiltingDistanceWindow::TiltingDistanceWindow(double length, std::string geomColumnName) : ASpatialWindow(geomColumnName),
                                                                                          buffer(make_shared<ListContainer>()),
                                                                                          maxDistance(length),
                                                                                          sumDistances(0.0) {

}

void TiltingDistanceWindow::onDataUpdate() {

    for (auto it = primaryInput.pop()->getIterator(); !it->end(); it->next()) {
        auto incomingTuple = it->get();

        auto geom = static_cast<Geometry *>(incomingTuple->getData()[geomColumnIndex].get());

        if (this->buffer->getSize() > 0) {

            auto lastInsertedTuple = buffer->getBack();
            auto prevGeometry = static_cast<Geometry *>(lastInsertedTuple->getData()[geomColumnIndex].get());
            auto distance = Geometry::getDistance(prevGeometry, geom);
            sumDistances += distance;

            if (sumDistances >= maxDistance) {
                resultSet = buffer;
                buffer = make_shared<ListContainer>();
                sumDistances = 0;
            }
        }
        buffer->pushBack(incomingTuple);
    }
    publish(resultSet);
}


TiltingDistanceWindow::~TiltingDistanceWindow() {}
