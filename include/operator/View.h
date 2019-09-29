//
// Created by tobias on 09.08.18.
//

#ifndef STREAMS_END_H
#define STREAMS_END_H

#include "AOperator.h"

namespace STREAM {

    class View : public AOperator {

    private:

        std::string name;

        bool isTimeBased = false;

        std::shared_ptr<STREAM::AStreamContainer> data;
    public:

        View(std::string name);

        void refresh();

        std::string getName();

        std::shared_ptr<AStreamContainer> &getData();

        void setToTimeBased();

        virtual void triggerPrevOperator() override;

        virtual void onDataUpdate() override;

        virtual void updateSchema() override;

        ~View();
    };

}


#endif //STREAMS_END_H
