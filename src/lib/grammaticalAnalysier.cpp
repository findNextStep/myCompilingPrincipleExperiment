#include "grammaticalAnalysier.hpp"
#include <iostream>

using ::std::cout;
using ::std::endl;
namespace theNext {
std::string make_name(rule_t rule) {
    std::string ans = "";
    for(auto name : rule) {
        if(ans == "") {
            ans = name;
        } else {
            ans += '_' + name;
        }
    }
    return ans;
}

template<>
void grammaticalAnalysier::makeRule(rule_t &name_list, ::std::vector<rule_t> &total_rule, rule_t add_rule) {
    for(auto s : add_rule) {
        for(auto it = total_rule.begin(); it != total_rule.end(); ++it) {
            it->push_back(s);
        }
    }
}

template<>
void grammaticalAnalysier::makeRule(rule_t &name_list, ::std::vector<rule_t> &total_rule, optional add_rule) {
    int size = total_rule.size();
    auto add_name = make_name(add_rule);
    // 复制并重构
    for(int i = 0; i < size; ++i) {
        total_rule.push_back(total_rule.at(i));
        name_list.push_back(name_list.at(i) + "_without_" + add_name);
        name_list.at(i) += "_with_" + add_name;
        for(auto s : add_rule) {
            total_rule.at(i).push_back(s);
        }
    }
}
template<>
void grammaticalAnalysier::makeRule(rule_t &name_list, ::std::vector<rule_t> &total_rule, repeat add_rule) {
    std::string name = "repeat_" + make_name(add_rule);
    this->addGramaticRule(name, (rule_t)add_rule);
    for(auto it = total_rule.begin(); it != total_rule.end(); ++it) {
        it->push_back(name);
    }
}
template<>
void grammaticalAnalysier::makeRule(rule_t &name_list, ::std::vector<rule_t> &total_rule, std::initializer_list<::std::string>add) {
    return makeRule<rule_t>(name_list, total_rule, add);
}

void grammaticalAnalysier::add_rule(const rule_t &name_list, const ::std::vector<rule_t> &total_rule) {
    for(int i = 0; i < name_list.size(); ++i) {
        cout << name_list.at(i) << " : ";
        for(auto rule : total_rule.at(i)) {
            cout << rule << " ";
        }
        cout << endl;
    }
}
}// namespace theNext