//
// Created by tobias on 09.08.18.
//

#include <data_container/ListContainer.h>
#include "operator/aggregation/Max.h"

using namespace std;
using namespace STREAM;

Max::Max(Attribute attribute) : AAggregation(attribute) {
//    attribute.setName("max");
    schema.push_back(attribute);
}

template<typename T>
void STREAM::Max::isGreaterThan() {
    auto data = primaryInput.pop();

    auto currentValue = dynamic_cast<T *>(resultSet->getIterator()->get()->getData().at(attribute.getIndex()).get());

    auto it = data->getIterator();

    while (!it->end()) {
        auto tuple = it->get();

        auto incomingValue = dynamic_cast<T *>(tuple->getData().at(attribute.getIndex()).get());

        if (gt.check(*incomingValue, *currentValue)) {
            auto container = make_shared<ListContainer>();
            auto maxTuple = make_shared<Tuple>(1);
            maxTuple->push_back(tuple->getData().at(attribute.getIndex())->copy());
            container->pushBack(maxTuple);
            resultSet = container;
        }

        it->next();
    }


    publish(resultSet);
}

void Max::onDataUpdate() {

    switch (attribute.getType()) {
        case ETypes::LONG: {
            isGreaterThan<Long>();
            break;
        }
        case ETypes::DOUBLE: {
            isGreaterThan<Double>();
            break;
        }
        case ETypes::STRING: {
            isGreaterThan<String>();
            break;
        }
        case ETypes::BLOB: {
            isGreaterThan<Blob>();
            break;
        }
    }

}

void Max::updateSchema() {

    auto incomingSchema = primaryInput.getSrcOperator()->getSchema();

    for (auto &attribute : schema)
        for (size_t i = 0; i < incomingSchema.size(); i++)
            if (attribute == incomingSchema.at(i)) {
                attribute.setIndex(i);
                attribute.setType(incomingSchema.at(i).getType());
            }

}

Max::~Max() {

}
