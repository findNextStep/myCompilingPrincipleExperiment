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
    return;
}

::nlohmann::json treePrinter::remove_unneed(const json &js, const std::vector<std::string> &typelist) {
    json ans;
    if(js.find("son") != js.end()) {
        /* 添加所有子项中需要添加的项目 */
        ans["son"] = {};
        for(auto son : js.at("son")) {
            if(need_to_print(son, typelist)) {
                ans["type"] = js.at("type");
                ans.at("son").push_back(remove_unneed(son, typelist));
            }
        }
    } else {
        /* 对于没有子项的项目而言添加自身 */
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
        /* 如果js有子树,判断子树中是否有需要添加的项目 */
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

::std::string treePrinter::toList(int index) {
    return printTree(this->tree, 0, index);
}

std::string treePrinter::printTree(const json &js, const int level, const int index) {
    std::string ans =  js.at("type").get<std::string>() + '\n';
    if(js.find("son") == js.end()) {
        /* 如果没有子树，为叶子节点，添加自身的文本内容 */
        ans = js.at("content").get<std::string>() + '\t' + ans;
    }
    for(int i = 0; i < level * index; ++i) {
        /* 添加缩进 */
        ans = ' ' + ans;
    }
    if(js.find("son") != js.end()) {
        /* 添加子树内容 */
        for(auto son : js.at("son")) {
            ans += printTree(son, level + 1, index);
        }
    }
    return ans;
}

}