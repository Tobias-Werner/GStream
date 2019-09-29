//
// Created by tobias on 30.08.19.
//

#ifndef STREAMS_WAYPOINTWINDOW_H
#define STREAMS_WAYPOINTWINDOW_H

#include "ASpatialWindow.h"
#include <vector>
#include <data_types/Geometry.h>

namespace STREAM {

    class WaypointWindow : public ASpatialWindow {

    private:

        STREAM::Geometry waypoints;
        bool prevOverlaped;

    public:

        WaypointWindow(const std::string &wkt, std::string &geomColumnName);

        virtual void onDataUpdate() override;

        ~WaypointWindow();
    };

}


#endif //STREAMS_WAYPOINTWINDOW_H
