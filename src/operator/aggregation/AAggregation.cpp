//
// Created by tobias on 31.08.18.
//

#include <data_container/ListContainer.h>
#include "operator/aggregation/AAggregation.h"

using namespace std;
using namespace STREAM;

AAggregation::AAggregation(Attribute attribute) : attribute(attribute), resultSet(make_shared<ListContainer>()) {

}

void AAggregation::triggerPrevOperator() {
    primaryInput.getSrcOperator()->triggerPrevOperator();
}
