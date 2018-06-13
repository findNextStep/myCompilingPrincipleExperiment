#include <string>
#include <map>
#include <vector>
#include "struct/token.hpp"
#include <nlohmann/json.hpp>

namespace theNext {

struct gramaticalTree {
private:
    std::vector<gramaticalTree> son;
public:
    token my;
    gramaticalTree(::std::string name) {
        this->my.type = name;
    }
    gramaticalTree(token toke): my(toke) { }
    ~gramaticalTree() { }

    gramaticalTree &addSon(const gramaticalTree &son) {
        this->son.push_back(son);
        return *this;
    }

    gramaticalTree &addSon_back(const gramaticalTree &son) {
        this->son.insert(this->son.begin(), son);
        return *this;
    }

    nlohmann::json toJson()const {
        auto ans = this->my.toJson();
        for(auto s : son) {
            ans["son"].push_back(s.toJson());
        }
        return ans;
    }
};
} // namespace theNext