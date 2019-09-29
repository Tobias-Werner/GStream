//
// Created by tobias on 30.07.18.
//

#ifndef STREAMS_AINPUT_H
#define STREAMS_AINPUT_H

#include <data_container/AStreamContainer.h>

namespace STREAM {

    class AOperator;

    class Input {

    private:

        AOperator *owner;

        std::shared_ptr<AOperator> srcOperator;

        std::shared_ptr<AStreamContainer> data;

    public:

        Input(AOperator *owner);

        void set(std::shared_ptr<AOperator> srcOperator);

        std::shared_ptr<AOperator> getSrcOperator();

        bool hasChanged();

        void process(std::shared_ptr<AStreamContainer> data);

        std::shared_ptr<AStreamContainer> pop();

        ~Input();
    };

}

#endif //STREAMS_AOPERATOR_H
