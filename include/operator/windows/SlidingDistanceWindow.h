//
// Created by tobias on 21.08.19.
//

#ifndef STREAMS_SLIDINGDISTANCEWINDOW_H
#define STREAMS_SLIDINGDISTANCEWINDOW_H

#include "ASpatialWindow.h"
#include <string>
#include <data_types/Geometry.h>

namespace STREAM {

    class SlidingDistanceWindow : public ASpatialWindow {

    private:
        double maxDistance;
        double sumDistances;
        std::list<double> distances;

    public:

        SlidingDistanceWindow(double length, std::string geomColumnName);

        void onDataUpdate() override;

        ~SlidingDistanceWindow();

    };

}


#endif //STREAMS_SLIDINGDISTANCEWINDOW_H
