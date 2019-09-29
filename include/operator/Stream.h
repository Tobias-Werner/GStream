//
// Created by tobias on 27.01.18.
//

#ifndef SPREAMS_STREAM_TABLE_H
#define SPREAMS_STREAM_TABLE_H

#include <vector>
#include <unordered_set>
#include <string>
#include <memory>
#include "Attribute.h"
#include "Tuple.h"
#include "data_container/AStreamContainer.h"
#include "AOperator.h"
#include "View.h"

namespace STREAM {

    class Stream : public AOperator {

    private:

        std::string name;

    public:

        Stream(std::string name, const std::list<Attribute> attributes);

        std::string getName();

        void insert(std::shared_ptr<Tuple> &tupel);

        void triggerPrevOperator() override;

        virtual void onDataUpdate() override;

        virtual void updateSchema() override;

        ~Stream();

    };
}

#endif //SPREAMS_STREAM_TABLE_H
