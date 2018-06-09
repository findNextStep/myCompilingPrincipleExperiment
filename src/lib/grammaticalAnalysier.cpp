#include "grammaticalAnalysier.hpp"
#include <iostream>
#include <algorithm>

using ::std::cout;
using ::std::endl;
namespace theNext {

template<>
void grammaticalAnalysier::makeRule(::std::vector<rule_t> &total_rule, rule_t add_rule) {
    for(auto s : add_rule) {
        for(auto it = total_rule.begin(); it != total_rule.end(); ++it) {
            it->push_back(s);
        }
    }
}

template<>
void grammaticalAnalysier::makeRule(::std::vector<rule_t> &total_rule, optional add_rule) {
    int size = total_rule.size();
    // 复制并重构
    for(int i = 0; i < size; ++i) {
        total_rule.push_back(total_rule.at(i));
        for(auto s : add_rule) {
            total_rule.at(i).push_back(s);
        }
    }
}
template<>
void grammaticalAnalysier::makeRule(::std::vector<rule_t> &total_rule, repeat add_rule) {
    std::string name = "";
    for(auto n : add_rule) {
        if(name == "") {
            name = n;
        } else {
            name += "_" + n;
        }
    }
    this->addGramaticRule<rule_t>("repeat_" + name, (rule_t)add_rule);
    for(auto it = total_rule.begin(); it != total_rule.end(); ++it) {
        it->push_back(name);
    }
}

template<>
void grammaticalAnalysier::makeRule(::std::vector<rule_t> &total_rule, std::initializer_list<::std::string>add) {
    return makeRule<rule_t>(total_rule, add);
}

template<>
void grammaticalAnalysier::makeRule(::std::vector<rule_t> &total_rule, option_and_repeat add_rule) {
    std::string name = "";
    for(auto n : add_rule) {
        if(name == "") {
            name = n;
        } else {
            name += "_" + n;
        }
    }
    name = "repeat_" + name;
    this->addGramaticRule<rule_t>(name, (rule_t)add_rule);
    return makeRule(total_rule,  optional({name}));
}

void grammaticalAnalysier::add_rule(const ::std::string name, const ::std::vector<rule_t> &total_rule) {
    for(auto rule : total_rule) {
        this->all_rule[name].push_back(rule);
    }
}

grammaticalAnalysier &grammaticalAnalysier::makeDFA() {
    this->remove_repeat();
    for(auto rule : this->all_rule) {
        cout << rule.first << endl;
        for(auto s : rule.second) {
            for(auto c : s) {
                cout << "\t" << c;
            }
            cout << endl;
        }
        cout << endl;
    }
    return *this;
}

void grammaticalAnalysier::remove_repeat() {
    for(auto it = all_rule.begin(); it != all_rule.end(); ++it) {
        std::sort(it->second.begin(), it->second.end());
        for(int i = 1; i < it->second.size(); ++i) {
            if(it->second[i - 1] == it->second[i]) {
                it->second.erase(it->second.begin() + i - 1);
                i--;
            }
        }
    }
}

bool grammaticalAnalysier::isToken(std::string name) const {
    return this->all_rule.find(name) == this->all_rule.end();
}
}// namespace theNext