#include <iostream>
#include "lexicalAnalysier.hpp"
#include "threadLanguage/threadSetting.hpp"

using ::theNext::threadSetting::threadState;

int main(int, char **) {
    ::theNext::lexicalAnalysier<threadState> a;
    a.addStateChangeWay(threadState(), '+', threadState::addOp);
    return 0;
}
