//
// Created by tobias on 22.08.18.
//

#ifndef STREAMS_SLIDINGWINDOW_H
#define STREAMS_SLIDINGWINDOW_H

#include "ATemporalWindow.h"

namespace STREAM {

    class SlidingWindow : public ATemporalWindow {

    private:

        std::chrono::milliseconds duration;

    public:

        SlidingWindow(std::chrono::milliseconds duration);

        virtual void onDataUpdate() override;

        ~SlidingWindow();

    };

}


#endif //STREAMS_SLIDINGWINDOW_H
