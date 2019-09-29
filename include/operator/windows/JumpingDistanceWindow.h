//
// Created by tobias on 29.09.19.
//

#ifndef STREAMS_JUMPINGDISTANCEWINDOW_H
#define STREAMS_JUMPINGDISTANCEWINDOW_H

#include "operator/windows/ASpatialWindow.h"

namespace STREAM {

    class JumpingDistanceWindow : public ASpatialWindow {

    private:
        double distance;
        double sumDistances;

    public:

        JumpingDistanceWindow(double distance, std::string geomColumnName);

        void onDataUpdate() override;

        ~JumpingDistanceWindow();

    };

}


#endif //STREAMS_JUMPINGDISTANCEWINDOW_H
