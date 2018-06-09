#pragma once
#include "struct/token.hpp"
#include <map>
#include <string>

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
    typedef ::std::map<::std::string, ::std::string> state_mecian;

    grammaticalAnalysier() {}
    ~grammaticalAnalysier() {}
    template <typename T, typename...Args>
    grammaticalAnalysier &addGramaticRule(const ::std::string &rulename, T number1 , Args... numbers) {
        ::std::vector<rule_t> total_rule(1);
        addGramaticRule(total_rule, number1, numbers...);
        add_rule(rulename, total_rule);
        return *this;
    }
    template <typename T>
    grammaticalAnalysier &addGramaticRule(const ::std::string &rulename, T number1) {
        ::std::vector<rule_t> total_rule(1);
        addGramaticRule(total_rule, number1);
        add_rule(rulename, total_rule);
        return *this;
    }

protected:
    template <typename T, typename...Args>
    grammaticalAnalysier &addGramaticRule(::std::vector<rule_t> &total_rule,
                                          T number1 , Args... numbers) {
        makeRule<T>(total_rule, number1);
        return addGramaticRule(total_rule, numbers...);
    }
    template <typename T>
    grammaticalAnalysier &addGramaticRule(::std::vector<rule_t> &total_rule,
                                          T number1) {
        makeRule<T>(total_rule, number1);
        return *this;
    }
    void add_rule(const ::std::string name, const ::std::vector<rule_t> &total_rule);
    template<typename T>
    void makeRule(::std::vector<rule_t> &total_rule, T add_rule);
private:
    std::map<std::string, std::vector<rule_t> >all_rule;

};
} // namespace theNext