//
// Created by tobias on 29.05.18.
//

#include <data_types/Null.h>
#include <make_unique.h>

#include "data_types/Null.h"

using namespace std;
using namespace STREAM;

void Null::result(AResultHandler &result_handler) {

}

unique_ptr<ADataType> Null::copy() {
    return make_unique<Null>();
}
