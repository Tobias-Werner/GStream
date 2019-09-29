//
// Created by tobias on 23.08.18.
//

#include <operator/windows/AWindow.h>
#include <data_container/ListContainer.h>

#include "operator/windows/AWindow.h"

using namespace STREAM;
using namespace std;

AWindow::AWindow() : resultSet(make_shared<ListContainer>()) {

}

void AWindow::triggerPrevOperator() {
    primaryInput.getSrcOperator()->triggerPrevOperator();
}
