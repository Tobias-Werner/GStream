//
// Created by tobias on 24.05.18.
//

#include "result_handler/ConsoleResultHandler.h"
#include "data_types/Long.h"
#include "data_types/Blob.h"
#include "data_types/String.h"
#include "data_types/Double.h"
#include "data_types/Geometry.h"
#include <iostream>

using namespace std;
using namespace STREAM;

void ConsoleResultHandler::onBegin() {

}

void ConsoleResultHandler::add(Long &value) {
    std::cout << value.get() << " ";
}

void ConsoleResultHandler::add(Double &value) {
    std::cout << value.get() << " ";
}

void ConsoleResultHandler::add(String &value) {
    std::cout << value.get() << " ";
}

void ConsoleResultHandler::add(Blob &value) {
    std::cout << "0x";
    for (auto &aByte : value.get()) {
        std::cout << aByte;
    }
    std::cout << " ";

}

void ConsoleResultHandler::add(Geometry &geom) {
    std::cout << "0x";

    for (const auto &byte : geom.asTWKB())
        std::cout << byte;

    std::cout << " ";

}

void ConsoleResultHandler::add(Null &value) {
    std::cout << " [null] ";
}

void ConsoleResultHandler::onEnd() {

}

ConsoleResultHandler::~ConsoleResultHandler() {}