#include "grammaticalAnalysier.hpp"
// #include <iostream>
// using namespace std;
namespace theNext {
template<>
void grammaticalAnalysier::makeRule(std::vector<rule_t> &total_rule, rule_t add_rule) {
    for(auto it = total_rule.begin(); it != total_rule.end(); ++it) {
        for(auto rule : add_rule) {
            it->push_back(rule);
        }
    }
}

template<>
void grammaticalAnalysier::makeRule(std::vector<rule_t> &total_rule, optional add_rule) {
    int size = total_rule.size();
    for(int i = 0; i < size; ++i) {
        total_rule.push_back(total_rule[i]);
        for(auto rule : add_rule) {
            total_rule[i].push_back(rule);
        }
    }
}
template<>
void grammaticalAnalysier::makeRule(std::vector<rule_t> &total_rule, repeat add_rule) {
    std::string name = "";
    for(auto n : add_rule) {
        if(name == "") {
            name = n;
        } else {
            name += "_" + n;
        }
    }
    name = "repeat_" + name;
    for(auto it = total_rule.begin(); it != total_rule.end(); ++it) {
        for(auto rule : add_rule) {
            it->push_back(rule);
        }
    }
    for(auto font_rule : total_rule) {
        this->addGramaticRule(name, font_rule);
    }
    rule_t repeat;
    repeat.push_back(name);
    for(auto rule : add_rule) {
        repeat.push_back(rule);
    }
    this->addGramaticRule(name, repeat);
    total_rule.resize(0);
    total_rule.push_back({name});
}

template<>
void grammaticalAnalysier::makeRule(std::vector<rule_t> &total_rule, std::initializer_list<::std::string>add) {
    return makeRule<rule_t>(total_rule, add);
}

template<>
void grammaticalAnalysier::makeRule(std::vector<rule_t> &total_rule, option_and_repeat add_rule) {
    // /* 创建一个规则 */
    // rule_t rule;
    // /* 为这个规则添加一个重复的规则 */
    // makeRule<repeat>(rule, add_rule);
    // /* 将这个规则作为当前规则的可选项 */
    // makeRule<optional>(total_rule, rule);
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
    int size = total_rule.size();
    for(int i = 0; i < size; ++i) {
        total_rule.push_back(total_rule[i]);
        total_rule[i].push_back(name);
    }
}

void grammaticalAnalysier::add_rule(const ::std::string name, const rule_t &total_rule) {
    this->all_rule[name].push_back(total_rule);
}

grammaticalAnalysier &grammaticalAnalysier::makeDFA() {
    this->DFAhas_make = true;
    this->remove_repeat();
    // for(auto rule : this->all_rule) {
    //     cout << rule.first << endl;
    //     for(auto s : rule.second) {
    //         cout << "-->";
    //         for(auto c : s) {
    //             cout << "\t" << c;
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }
    this->state_map.resize(1);
    this->set_to(this->end_rule, "", 0);
    // int i = 0;
    // for(auto path : this->state_map) {
    //     cout << i << endl;
    //     for(auto role : path) {
    //         cout <<
    //              "\t" << i << " --\"" << role.first << "\"--> " << role.second << endl;
    //     }
    //     cout << endl;
    //     ++i;
    // }
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
                                // now =  state_map[now][rule[0]];
                            } else {
                                this->state_map[now][rule[0]] = this->state_map[it->second][rule[0]];
                                // cout << it->second << endl;
                                // cout <<
                                     //       "link : " <<
                                    //  now << " --\"" << rule[0] << "\"--> " << this->state_map[now][rule[0]] << endl;

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
                    // cout <<
                         //       "crea : " <<
                        //  now << " --\"" << path << "\"--> " << this->state_map[now][path] << endl;

                    now = this->state_map.size();
                    this->state_map.resize(this->state_map.size() + 1);
                }
            } else {
                if(state_map[now].find(path) != state_map[now].end()) {
                    now = state_map[now][path];
                } else {
                    this->state_map[now][path] = this->state_map.size();

                    // cout <<
                         //       "crea : " <<
                        //  now << " --\"" << path << "\"--> " << this->state_map[now][path] << endl;

                    now = this->state_map.size();
                    this->state_map.resize(this->state_map.size() + 1);
                }
            }
        }
        this->add_end(now, name, rule);
    }
    this->query[std::make_pair(name, end)] = start;
    // cout << endl;
    for(auto link : need_to_link) {
        this->set_to(link.first.first, link.first.second, link.second);
    }
    return;
}
void grammaticalAnalysier::add_end(const int n, const std::string name, const rule_t rule) {
    this->in_a_end[n].add(rule, name);
}
}