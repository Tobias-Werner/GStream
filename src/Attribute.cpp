//
// Created by tobias on 29.01.18.
//

#include <Attribute.h>

#include "Attribute.h"

using namespace std;
using namespace STREAM;

Attribute::Attribute(string name) : index(0), name(name), src("") {

}

Attribute::Attribute(string src, string name) : index(0), name(name), src(src) {

}

Attribute::Attribute(string name, ETypes type) : index(0), name(name), type(type), src("") {

}

string &Attribute::getName() {
    return name;
}

ETypes Attribute::getType() {
    return type;
}

void Attribute::setName(const string &name) {
    Attribute::name = name;
}

string &Attribute::getSrc() {
    return src;
}

void Attribute::setSrc(const string &src) {
    Attribute::src = src;
}

void Attribute::setType(ETypes type) {
    Attribute::type = type;
}

bool Attribute::hasSrc() {
    return src != "";
}

size_t Attribute::getIndex() const {
    return index;
}

void Attribute::setIndex(size_t index) {
    Attribute::index = index;
}

bool Attribute::operator==(const Attribute &other) {
    return (this->name == other.name) && (this->src == other.src);
}

