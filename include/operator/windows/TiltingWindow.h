//
// Created by tobias on 29.08.18.
//

#ifndef STREAMS_TILTINGWINDOW_H
#define STREAMS_TILTINGWINDOW_H

#include "ATemporalWindow.h"

namespace STREAM {

    class TiltingWindow : public ATemporalWindow {

    private:

        std::shared_ptr<AStreamContainer> buffer;

        std::chrono::milliseconds duration;

        std::chrono::high_resolution_clock::time_point begin;

    public:

        TiltingWindow(std::chrono::milliseconds duration);

        virtual void onDataUpdate() override;

        ~TiltingWindow();
    };

}


#endif //STREAMS_TILTINGWINDOW_H
