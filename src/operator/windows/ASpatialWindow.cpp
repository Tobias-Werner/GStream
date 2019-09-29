//
// Created by tobias on 20.09.19.
//

#include "operator/windows/ASpatialWindow.h"

using namespace STREAM;


ASpatialWindow::ASpatialWindow(std::string &geomColumnName) : geomColumnName(geomColumnName), geomColumnIndex(0) {
    updateSchema();
}

void ASpatialWindow::updateSchema() {

    for (auto &elem : schema)
        if (elem.getName() == geomColumnName) {
            geomColumnIndex = elem.getIndex();
            return;
        }

    // Error handling here
}