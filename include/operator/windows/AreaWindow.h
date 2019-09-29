//
// Created by tobias on 29.09.19.
//

#ifndef STREAMS_AREAWINDOW_H
#define STREAMS_AREAWINDOW_H

#include "operator/windows/ASpatialWindow.h"

namespace STREAM {

    class AreaWindow : public ASpatialWindow {

    private:

        STREAM::Geometry waypoints;
        bool prevOverlaped;

    public:

        AreaWindow(const std::string &wkt, std::string &geomColumnName);

        virtual void onDataUpdate() override;

        ~AreaWindow();
    };

}


#endif //STREAMS_AREAWINDOW_H
