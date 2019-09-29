//
// Created by tobias on 17.08.18.
//

#ifndef STREAMS_SELECT_H
#define STREAMS_SELECT_H

#include "AOperator.h"

namespace STREAM {

    class Select : public AOperator {

    public:

        Select(std::list<Attribute> selectedAttributes);

        void setSrc(std::shared_ptr<AOperator> src);

        virtual void triggerPrevOperator() override;

        virtual void onDataUpdate() override;

        virtual void updateSchema() override;

        ~Select();

    };

}

#endif //STREAMS_SELECT_H
