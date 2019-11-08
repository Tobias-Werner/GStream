//
// Created by tobias on 29.09.19.
//

#ifndef STREAMS_AREAWINDOW_H
#define STREAMS_AREAWINDOW_H

#include "operator/windows/ASpatialWindow.h"
#include <data_types/Geometry.h>
#include <list>

namespace STREAM {

    class AreaWindow : public ASpatialWindow {

    private:

        std::list<double> mins;
        std::list<double> maxs;

    public:

        AreaWindow(const std::string &minPointWKT, const std::string &maxPointWKT, std::string &geomColumnName);

        virtual void onDataUpdate() override;

        ~AreaWindow();
    };

}


#endif //STREAMS_AREAWINDOW_H
