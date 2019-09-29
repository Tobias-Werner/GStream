//
// Created by tobias on 30.07.18.
//

#ifndef STREAMS_JOIN_H
#define STREAMS_JOIN_H

#include <functional>
#include <operator/expression/ACondition.h>
#include "AOperator.h"


namespace STREAM {

    class Join : public AOperator {

    private:

        std::list<ACondition> conditions;

        Input secondaryInput;

        std::shared_ptr<STREAM::AStreamContainer> leftData;
        std::shared_ptr<STREAM::AStreamContainer> rightData;

    public:
        Join(std::list<ACondition> conditions);

        void setSecondarySrc(std::shared_ptr<AOperator> src);

        template<typename T>
        void join();

        virtual void triggerPrevOperator() override;

        virtual void onDataUpdate() override;

        virtual void updateSchema() override;

        ~Join();
    };

}


#endif //STREAMS_JOIN_H
