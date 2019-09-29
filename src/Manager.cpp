#include "Manager.h"

using namespace std;
using namespace STREAM;

void Manager::add(Stream *stream) {
    streams[stream->getName()] = std::shared_ptr<STREAM::Stream>(stream);
}

void Manager::add(View *view) {
    views[view->getName()] = std::shared_ptr<STREAM::View>(view);
}

const shared_ptr<Stream> Manager::getStream(string name) {
    return streams[name];
}

const shared_ptr<View> Manager::getView(string name) {
    return views[name];
}