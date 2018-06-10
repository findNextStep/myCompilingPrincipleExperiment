#include "grammaticalAnalysier.hpp"
#include <iostream>
#include <algorithm>

using ::std::cout;
using ::std::endl;
namespace theNext {

template<>
void grammaticalAnalysier::makeRule(rule_t &total_rule, rule_t add_rule) {
    for(auto rule : add_rule) {
        total_rule.push_back(rule);
    }
}

template<>
void grammaticalAnalysier::makeRule(rule_t &total_rule, optional add_rule) {
    std::string name = "";
    for(auto n : add_rule) {
        if(name == "") {
            name = n;
        } else {
            name += "_" + n;
        }
    }
    this->addGramaticRule<rule_t>("option_" + name, (rule_t)add_rule);
    this->addGramaticRule<rule_t>("option_" + name, rule_t());
    total_rule.push_back("option_" + name);

}
template<>
void grammaticalAnalysier::makeRule(rule_t &total_rule, repeat add_rule) {
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
    auto repeat_rule = add_rule;
    repeat_rule.push_back(name);
    this->addGramaticRule<rule_t>(name, (rule_t)repeat_rule);
    total_rule.push_back(name);
}

template<>
void grammaticalAnalysier::makeRule(rule_t &total_rule, std::initializer_list<::std::string>add) {
    return makeRule<rule_t>(total_rule, add);
}

template<>
void grammaticalAnalysier::makeRule(rule_t &total_rule, option_and_repeat add_rule) {
    /* 创建一个规则 */
    rule_t rule;
    /* 为这个规则添加一个重复的规则 */
    makeRule<repeat>(rule,add_rule);
    /* 将这个规则作为当前规则的可选项 */
    makeRule<optional>(total_rule,rule);
}

void grammaticalAnalysier::add_rule(const ::std::string name, const rule_t &total_rule) {
    this->all_rule[name].push_back(total_rule);
}

grammaticalAnalysier &grammaticalAnalysier::makeDFA() {
    this->remove_repeat();
    for(auto rule : this->all_rule) {
        cout << rule.first << endl;
        for(auto s : rule.second) {
            cout << "-->";
            for(auto c : s) {
                cout << "\t" << c;
            }
            cout << endl;
        }
        cout << endl;
    }
    this->state_map.resize(1);
    this->set_to(this->end_rule, "", 0);
    int i = 0;
    for(auto path : this->state_map) {
        // cout << i << endl;
        for(auto role : path) {
            cout
            // << "\t"
                    << i << " --\"" << role.first << "\"--> " << role.second << endl;
        }
        // cout << endl;
        ++i;
    }
    return *this;
}

void grammaticalAnalysier::remove_repeat() {
    for(auto it = all_rule.begin(); it != all_rule.end(); ++it) {
        std::sort(it->second.begin(), it->second.end(), [](auto a, auto b) {
            return a > b;
        });
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


void grammaticalAnalysier::set_to(std::string name, std::string end, int start) {
    // if(this->query.find(std::make_pair(name, end)) != this->query.end()) {
    //     return;
    // }
    std::vector<std::pair<std::pair<std::string, std::string>, int> > need_to_link;
    // cout << "------------------\n";
    // cout << name + "\t" + end + "\t" << start << endl;
    for(auto rule : this->all_rule[name]) {
        int now = start;
        for(int i = 0; i < rule.size(); ++i) {

            const auto path  = rule[i];
            if(!this->isToken(path)) {
                std::string path_end = end;
                if(i != rule.size() - 1) {
                    path_end = rule[i + 1];
                }
                auto it = this->query.find(std::make_pair(path, path_end));
                if(it != this->query.end()) {
                    /* 如果存在，提前计算 */
                    for(auto rule : all_rule[path]) {
                        // this->set_to(path, path_end, it->second);
                        if(rule.size()) {
                            if(state_map[now].find(rule[0]) != state_map[now].end()) {
                                now =  state_map[now][rule[0]];
                            } else {
                                this->state_map[now][rule[0]] = this->state_map[it->second][rule[0]];
                                // cout << it->second << endl;
                                cout <<
                                     //  "link : " <<
                                     now << " --\"" << rule[0] << "\"--> " << this->state_map[now][rule[0]] << endl;
                            }

                        }
                    }
                } else {
                    need_to_link.push_back(std::make_pair(std::make_pair(path, path_end) , now));
                }
                if(state_map[now].find(path) != state_map[now].end()) {
                    now = state_map[now][path];
                } else {
                    this->state_map[now][path] = this->state_map.size();
                    cout <<
                         //  "crea : " <<
                         now << " --\"" << path << "\"--> " << this->state_map[now][path] << endl;

                    now = this->state_map.size();
                    this->state_map.resize(this->state_map.size() + 1);
                }
            } else {
                if(state_map[now].find(path) != state_map[now].end()) {
                    now = state_map[now][path];
                } else {
                    this->state_map[now][path] = this->state_map.size();
                    cout <<
                         //  "crea : " <<
                         now << " --\"" << path << "\"--> " << this->state_map[now][path] << endl;

                    now = this->state_map.size();
                    this->state_map.resize(this->state_map.size() + 1);
                }
            }
            if(now == 66) {
                cout << "test" << endl;
            }
        }
        this->add_end(now, rule);
    }
    this->query[std::make_pair(name, end)] = start;
    cout << endl;
    for(auto link : need_to_link) {
        this->set_to(link.first.first, link.first.second, link.second);
    }
    return;
}
void grammaticalAnalysier::add_end(const int n, const rule_t rule) {
    if(n == 47) {
        cout << "threr" << endl;
    }
    if(in_a_end.find(n) == in_a_end.end()) {
        this->in_a_end[n] = rule;
    } else if(in_a_end[n] == rule) {
        return;
    } else {
        cout << "noooooooo" << endl;
        exit(-1);
    }
}
}// namespace theNext