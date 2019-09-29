#include "data_types/Double.h"
#include "data_types/Long.h"
#include "data_types/String.h"
#include "data_types/Blob.h"
#include <operator/Join.h>
#include <data_container/ListContainer.h>
#include <operator/expression/EQ.h>

#include "operator/Join.h"

using namespace std;
using namespace STREAM;

Join::Join(list<ACondition> conditions) : conditions(conditions),
                                          secondaryInput(Input(this)),
                                          leftData(make_shared<ListContainer>()),
                                          rightData(make_shared<ListContainer>()) {


}

void Join::setSecondarySrc(shared_ptr<AOperator> src) {
    src->addNextInput(secondaryInput);
    secondaryInput.set(src);
}

void Join::onDataUpdate() {

    if (primaryInput.hasChanged())
        leftData = primaryInput.pop();
    else
        rightData = secondaryInput.pop();

    auto condition = conditions.front();

    switch (condition.getLeft().getType()) {
        case ETypes::LONG: {
            join<Long>();
            break;
        }
        case ETypes::DOUBLE: {
            join<Double>();
            break;
        }
        case ETypes::STRING: {
            join<String>();
            break;
        }
        case ETypes::BLOB: {
            join<Blob>();
            break;
        }
    }
}

void Join::triggerPrevOperator() {
    primaryInput.getSrcOperator()->triggerPrevOperator();
    secondaryInput.getSrcOperator()->triggerPrevOperator();
}


void Join::updateSchema() {
    if (primaryInput.getSrcOperator() != nullptr && secondaryInput.getSrcOperator() != nullptr) {
        auto &condition = conditions.front();
        auto schemaLeft = primaryInput.getSrcOperator()->getSchema();
        auto schemaRight = secondaryInput.getSrcOperator()->getSchema();

        for (size_t index = 0; index < schemaLeft.size(); index++)
            if (schemaLeft.at(index) == condition.getLeft()) {
                condition.getLeft().setIndex(index);
                condition.getLeft().setType(schemaLeft[index].getType());
                break;
            }

        for (size_t index = 0; index < schemaRight.size(); index++)
            if (schemaRight.at(index) == condition.getRight()) {
                condition.getRight().setIndex(index);
                condition.getRight().setType(schemaRight[index].getType());
                break;
            }

        schema = schemaLeft;
        schema.insert(schema.end(), schemaRight.begin(), schemaRight.end());

    }
}

template<typename T>
void Join::join() {
    auto condition = conditions.front();
    size_t indexLeft = condition.getLeft().getIndex();
    size_t indexRight = condition.getRight().getIndex();

    auto container = make_shared<ListContainer>();

    auto itLeft = leftData->getIterator();

    while (!itLeft->end()) {
        auto leftTuple = itLeft->get();

        auto valueLeft = dynamic_cast<T *>(leftTuple->getData().at(indexLeft).get());

        auto itRight = rightData->getIterator();
        while (!itRight->end()) {
            auto rightTuple = itRight->get();

            auto valueRight = dynamic_cast<T *>(rightTuple->getData().at(indexRight).get());

            if (condition.check(*valueLeft, *valueRight)) {
                auto tuple = createTuple();

                for (auto &data : leftTuple->getData())
                    tuple->push_back(data->copy());

                for (auto &data : rightTuple->getData())
                    tuple->push_back(data->copy());

                container->pushBack(tuple);
            }

            itRight->next();
        }

        itLeft->next();
    }

    publish(container);
}

Join::~Join() {}
