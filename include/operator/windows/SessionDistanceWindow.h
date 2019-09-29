//
// Created by tobias on 21.08.19.
//

#ifndef STREAMS_SESSIONDISTANCEWINDOW_H
#define STREAMS_SESSIONDISTANCEWINDOW_H

#include "ASpatialWindow.h"
#include <string>
#include <data_types/Geometry.h>

namespace STREAM {

    class SessionDistanceWindow : public ASpatialWindow {

    private:
        double gap;

    public:

        SessionDistanceWindow(double gap, std::string geomColumnName);

        void onDataUpdate() override;

        ~SessionDistanceWindow();

    };

}


#endif //STREAMS_SESSIONDISTANCEWINDOW_H
