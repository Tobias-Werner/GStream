//
// Created by tobias on 20.09.19.
//

#ifndef STREAMS_ASPATIALWINDOW_H
#define STREAMS_ASPATIALWINDOW_H

#include "AWindow.h"

namespace STREAM {

    class ASpatialWindow : public AWindow {

    protected:
        std::string geomColumnName;
        size_t geomColumnIndex;

        ASpatialWindow(std::string &geomColumnName);

        void updateSchema();
    };


}


#endif //STREAMS_ASPATIALWINDOW_H
