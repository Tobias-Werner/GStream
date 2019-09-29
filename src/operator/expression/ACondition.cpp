//
// Created by tobias on 07.08.18.
//

#include "operator/expression/ACondition.h"

using namespace std;
using namespace STREAM;

bool ACondition::check(Blob &first, Blob &second) {
    return false;
}

bool ACondition::check(Long &first, Long &second) {
    return false;
}

bool ACondition::check(Double &first, Double &second) {
    return false;
}

bool ACondition::check(String &first, String &second) {
    return false;
}

bool ACondition::check(Null &first, Null &second) {
    return false;
}

Attribute &ACondition::getLeft() {
    return first;
}

void ACondition::setFirst(const Attribute &first) {
    ACondition::first= first;
}

Attribute &ACondition::getRight() {
    return second;
}

void ACondition::setSecond(const Attribute &secondName) {
    ACondition::second = secondName;
}

ACondition::~ACondition() {

}

