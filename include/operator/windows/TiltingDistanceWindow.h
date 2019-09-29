//
// Created by tobias on 28.08.19.
//

#ifndef STREAMS_TILTINGDISTANCEWINDOW_H
#define STREAMS_TILTINGDISTANCEWINDOW_H

#include "ASpatialWindow.h"
#include <string>
#include <data_types/Geometry.h>

namespace STREAM {

    class TiltingDistanceWindow : public ASpatialWindow {

    private:
        double maxDistance;
        double sumDistances;

        std::shared_ptr<STREAM::AStreamContainer> buffer;

    public:

        TiltingDistanceWindow(double length, std::string geomColumnName);

        void onDataUpdate() override;

        ~TiltingDistanceWindow();

    };

}

#endif //STREAMS_TILTINGDISTANCEWINDOW_H
