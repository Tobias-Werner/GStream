#include "sqlite_adapter/sqlite_adapter_cursor.h"

using namespace std;
using namespace STREAM;

sqlite_adapter_cursor::sqlite_adapter_cursor(View *owner) : owner(owner) {
    iterator = owner->getData()->getIterator();
}

const View *sqlite_adapter_cursor::get_owner() const {
    return owner;
}

void sqlite_adapter_cursor::next() {
    iterator->next();
}

std::shared_ptr<Tuple> sqlite_adapter_cursor::get() {
    return iterator->get();
}

bool sqlite_adapter_cursor::end() {
    return iterator->end();
}
