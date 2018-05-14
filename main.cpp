#include <iostream>
#include "lexicalAnalysier.hpp"
#include "threadLanguage/threadSetting.hpp"

using ::theNext::threadSetting::threadState;

int main(int, char **) {
    ::theNext::lexicalAnalysier<threadState> a;
    a.addStateChangeWay(threadState(), '+', threadState::addOp);
    ::nlohmann::json json;
    json["type"] = "test";
    json["content"] = "dafda";
    auto dafdafd = ::theNext::token::fromJson(json);
    std::cout << dafdafd.toJson() << std::endl;
    return 0;
}
