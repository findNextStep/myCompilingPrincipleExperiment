#pragma once
#include "struct/token.hpp"
#include <map>
#include <string>
#include "struct/gramaticalTree.hpp"
#include "tool/matchingDFA.hpp"

namespace theNext {
typedef ::std::vector<std::string> rule_t;
class optional : public rule_t {
public:
    optional(rule_t init): rule_t (init) {}
};
class repeat : public rule_t {
public:
    repeat(rule_t init): rule_t (init) {}
};
class option_and_repeat : public rule_t {
public:
    option_and_repeat(rule_t init): rule_t (init) {}
};
/**
 * @brief
 * reg_base(type)
 * - reg_char{token}
 * - reg_rule{base[]}
 * - reg_repeat{base[]}
 * - reg_optional{base[]}
 * {state--token-->state}
 * {state-->{front,new}}
 */
class grammaticalAnalysier {
public:
    grammaticalAnalysier() {}
    ~grammaticalAnalysier() {}
    template <typename T, typename...Args>
    grammaticalAnalysier &addGramaticRule(const ::std::string &rulename, T number1, Args... numbers) {
        if(this->end_rule == "") {
            setEndRule(rulename);
        }
        std::vector<rule_t> total_rule(1);
        addGramaticRule(total_rule, number1, numbers...);
        add_rule(rulename, total_rule);
        return *this;
    }
    template <typename T>
    grammaticalAnalysier &addGramaticRule(const ::std::string &rulename, T number1) {
        if(this->end_rule == "") {
            setEndRule(rulename);
        }
        std::vector<rule_t> total_rule(1);
        addGramaticRule(total_rule, number1);
        add_rule(rulename, total_rule);
        return *this;
    }
    grammaticalAnalysier &setEndRule(const ::std::string &name) {
        this->end_rule = name;
        return *this;
    }

    grammaticalAnalysier &makeDFA();

    gramaticalTree analise(const std::vector<token> tokens) const;

protected:
    template <typename T, typename...Args>
    grammaticalAnalysier &addGramaticRule(std::vector<rule_t> &total_rule,
                                          T number1, Args... numbers) {

        makeRule<T>(total_rule, number1);
        return addGramaticRule(total_rule, numbers...);
    }
    template <typename T>
    grammaticalAnalysier &addGramaticRule(std::vector<rule_t> &total_rule,
                                          T number1) {
        makeRule<T>(total_rule, number1);
        return *this;
    }
    bool isToken(std::string) const;
    void remove_repeat();
    void add_rule(const ::std::string name, const std::vector<rule_t> &total_rule) {
        for(auto rule : total_rule) {
            add_rule(name, rule);
        }
    }
    virtual void add_rule(const ::std::string name, const rule_t &total_rule);
    virtual void add_end(const int n, const std::string name, rule_t rule);
    template<typename T>
    void makeRule(std::vector<rule_t> &total_rule, T add_rule);
    void set_to(std::string name, std::string end, int start);
private:
    /**
     * @brief
     * [自动机标号<<转换token,期待结尾> ,跳转为结尾]
     */
    typedef ::std::vector<std::map<::std::string, int> > state_machine;
    ::std::map<::std::pair<::std::string, ::std::string>, int> query;
    std::map<std::string, std::vector<rule_t> >all_rule;
    // std::map<int, std::pair<std::string, rule_t> > in_a_end;
    ::std::map<int, matchingDFA> in_a_end;
    std::string end_rule;
    state_machine state_map;
};
} // namespace theNext