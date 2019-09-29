//
// Created by tobias on 31.08.18.
//

#ifndef STREAMS_AAGGREGATION_H
#define STREAMS_AAGGREGATION_H

#include <operator/AOperator.h>

namespace STREAM {

    class AAggregation : public AOperator {

    protected:

        Attribute attribute;

        std::shared_ptr<STREAM::AStreamContainer> resultSet;

    public:

        AAggregation(Attribute attribute);

        virtual void triggerPrevOperator() override;

    };

}


#endif //STREAMS_AAGGREGATION_H
