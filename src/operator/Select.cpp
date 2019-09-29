//
// Created by tobias on 17.08.18.
//

#include <operator/Select.h>
#include <data_container/ListContainer.h>

#include "operator/Select.h"

using namespace std;
using namespace STREAM;

Select::Select(std::list<Attribute> selectedAttributes) {

    for (auto &selectedAttribute : selectedAttributes)
        schema.push_back(selectedAttribute);
}

void Select::setSrc(std::shared_ptr<AOperator> src) {
    src->addNextInput(primaryInput);
    primaryInput.set(src);
}

void Select::onDataUpdate() {

    auto container = make_shared<ListContainer>();

    for (auto it = primaryInput.pop()->getIterator(); !it->end(); it->next()) {
        auto tuple = it->get();
        auto newTuple = make_shared<Tuple>(schema.size(), tuple->getTime());

        for (size_t i = 0; i < schema.size(); i++) {
            auto &selectedAttribute = schema.at(i);
            auto index = selectedAttribute.getIndex();
            newTuple->set(i, tuple->getData().at(index)->copy());
        }

        container->pushBack(newTuple);
    }

    publish(container);
}


void Select::updateSchema() {
    auto incomingSchema = primaryInput.getSrcOperator()->getSchema();

    for (auto &attribute : schema)
        for (size_t i = 0; i < incomingSchema.size(); i++)
            if (attribute.getName() == incomingSchema.at(i).getName())
                attribute.setIndex(i);


}

void Select::triggerPrevOperator() {
    primaryInput.getSrcOperator()->triggerPrevOperator();
}

Select::~Select() {

}


