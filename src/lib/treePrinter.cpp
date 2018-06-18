#include "tool/treePrinter.hpp"
#include <iostream>
using ::std::cout;
using ::std::endl;

namespace theNext {
treePrinter::treePrinter(const passList_t &passlist) {
    this->pass_list = passlist;
}

void treePrinter::init(const json &js) {
    this->tree = remove_unneed(js, this->pass_list);
    cout << tree.dump(2) << endl;
    return;
}

::nlohmann::json treePrinter::remove_unneed(const json &js, const std::vector<std::string> &typelist) {
    json ans;
    if(js.find("son") != js.end()) {
        ans["son"] = {};
        for(auto son : js.at("son")) {
            if(need_to_print(son, typelist)) {
                ans["type"] = js.at("type");
                ans.at("son").push_back(remove_unneed(son, typelist));
            }
        }
    } else {
        if(need_to_print(js, typelist)) {
            ans["type"] = js.at("type");
            return js;
        } else {
            return ans;
        }
    }
    return ans;
}


bool treePrinter::need_to_print(const json &js, const std::vector<std::string> &typelist) {
    if(js.find("son") != js.end()) {
        /* 如果js有子树 */
        for(auto son : js.at("son")) {
            if(need_to_print(son, typelist)) {
                return true;
            }
        }
        return false;
    } else {
        /* 没有子树判读自身是否有必要显示 */
        for(auto rule : typelist) {
            if(rule == js.at("type")) {
                return true;
            }
        }
        return false;
    }
}
}