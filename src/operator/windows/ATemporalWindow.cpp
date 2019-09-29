//
// Created by tobias on 20.09.19.
//

#include "operator/windows/ATemporalWindow.h"

using namespace STREAM;

void ATemporalWindow::updateSchema() {
    schema = primaryInput.getSrcOperator()->getSchema();
}

