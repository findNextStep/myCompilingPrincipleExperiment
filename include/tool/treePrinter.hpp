#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

namespace theNext {

class treePrinter {
public:
    typedef ::nlohmann::json json;
    typedef ::std::vector<std::string> passList_t;
private:
    ::nlohmann::json tree;
    passList_t pass_list;
protected:
    bool static need_to_print(const json &, const std::vector<std::string> &);
    json static remove_unneed(const json &, const std::vector<std::string> &);
    void init(const json &);
public:
    treePrinter(const passList_t &passlist);
    ~treePrinter() {};
    void setTree(json tree) {
        return this->init(tree);
    }
};
} // namespace theNext
