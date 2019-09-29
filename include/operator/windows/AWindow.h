//
// Created by tobias on 23.08.18.
//

#ifndef STREAMS_AWINDOW_H
#define STREAMS_AWINDOW_H

#include <operator/AOperator.h>

namespace STREAM {

    class AWindow : public AOperator {

    protected:

        std::shared_ptr<STREAM::AStreamContainer> resultSet;

    public:

        AWindow();

        virtual void triggerPrevOperator() override;

    };

}


#endif //STREAMS_AWINDOW_H
