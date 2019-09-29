//
// Created by tobias on 30.07.18.
//

#ifndef STREAMS_AOPERATOR_H
#define STREAMS_AOPERATOR_H


#include <list>
#include <memory>
#include "Input.h"

namespace STREAM {

    class AOperator {

    private:

        std::list<Input *> nextOperator;

    protected:

        Input primaryInput;

        std::vector<STREAM::Attribute> schema;

        void publish(std::shared_ptr<STREAM::AStreamContainer>);

    public:

        AOperator();

        void setSrc(std::shared_ptr<AOperator> src);

        virtual void triggerPrevOperator() = 0;

        bool hasAttribute(std::string name);

        std::vector<STREAM::Attribute> getSchema();

        std::shared_ptr<STREAM::Tuple> createTuple();

        void addNextInput(Input &node);

        virtual void onDataUpdate() = 0;

        virtual void updateSchema() = 0;

        virtual ~AOperator();
    };

}


#endif //STREAMS_AOPERATOR_H
