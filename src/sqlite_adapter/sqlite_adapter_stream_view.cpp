//
// Created by tobias on 02.05.18.
//

#include "sqlite_adapter/sqlite_adapter_stream_view.h"

using namespace std;
using namespace STREAM;

View *sqlite_adapter_stream_view::getView() const {
    return view;
}

void sqlite_adapter_stream_view::setView(View *view) {
    this->view = view;
}

