//
// Created by tobias on 09.08.18.
//

#ifndef STREAMS_MAX_H
#define STREAMS_MAX_H


#include "operator/expression/GT.h"
#include "AAggregation.h"


namespace STREAM {

    class Max : public AAggregation {

    private:
        GT gt;

        template<typename T>
        void isGreaterThan();

    public:

        Max(Attribute attribute);

        virtual void onDataUpdate() override;

        virtual void updateSchema() override;

        ~Max();

    };

}


#endif //STREAMS_MAX_H
