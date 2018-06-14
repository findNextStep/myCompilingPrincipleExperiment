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
 * @brief 语法分析器
 * 通过特定变长参数函数
 *
 */
class grammaticalAnalysier {
public:
    grammaticalAnalysier() : DFAhas_make(false) {}
    ~grammaticalAnalysier() {}
    /**
     * @brief 添加一个语法规则
     * 添加的语法规则会用于自动生成语法分析的DFA
     * @tparam T 语法分析用的类型
     *      包括
     *      ::std::vector<std::string> = ::theNext::rule_t 普通规则
     *      ::theNext::optional 可选规则
     *      ::theNext::repeat   可重复规则（至少一次）
     *      ::theNext::option_and_repeat 重复可选规则
     * @tparam Args 其他规则参数，每一个规则的类型与上述相同
     * @param rulename 规则名称
     * @return grammaticalAnalysier& this
     */
    template <typename T, typename...Args>
    grammaticalAnalysier &addGramaticRule(const ::std::string &rulename, T number1, Args... numbers) {
        DFAhas_make = false;
        if(this->end_rule == "") {
            setEndRule(rulename);
        }
        std::vector<rule_t> total_rule(1);
        addGramaticRule(total_rule, number1, numbers...);
        add_rule(rulename, total_rule);
        return *this;
    }
    /**
     * @brief 添加语法规则的单参数版本
     * 详细信息见多参数版本
     */
    template <typename T>
    grammaticalAnalysier &addGramaticRule(const ::std::string &rulename, T number1) {
        DFAhas_make = false;
        if(this->end_rule == "") {
            setEndRule(rulename);
        }
        std::vector<rule_t> total_rule(1);
        addGramaticRule(total_rule, number1);
        add_rule(rulename, total_rule);
        return *this;
    }
    /**
     * @brief 设置终止规则名称
     * 如果没有指定，终止规则名称为第一个添加的语法规则的名称
     * @param name 终止规则的名称
     * @return grammaticalAnalysier& this
     */
    grammaticalAnalysier &setEndRule(const ::std::string &name) {
        DFAhas_make = false;
        this->end_rule = name;
        return *this;
    }
    /**
     * @brief 制作语法分析的DFA
     * 会在分析的时候自动判断是否需要调用
     * @return grammaticalAnalysier& this
     */
    grammaticalAnalysier &makeDFA();
    /**
     * @brief 进行语法分析
     *
     * @param tokens 词法分析器的分析结果
     * @return gramaticalTree 语法分析树
     */
    gramaticalTree analise(const std::vector<token> tokens);

protected:
    /**
     * @brief 为规则添加一个项目
     * 批量添加项目通过递归的方式实现
     * @tparam T 被添加的项目
     * @tparam Args 其他待添加的项目
     * @param total_rule 当前已经生成的规则
     * @param number1 当前添加的规则
     * @param numbers 其他规则
     * @return grammaticalAnalysier& this
     */
    template <typename T, typename...Args>
    grammaticalAnalysier &addGramaticRule(std::vector<rule_t> &total_rule,
                                          T number1, Args... numbers) {

        makeRule<T>(total_rule, number1);
        return addGramaticRule(total_rule, numbers...);
    }
    /**
     * @brief 为规则添加最后一个项目
     *
     * @tparam T 添加的最后一个项目的类型
     * @param total_rule 总计的所有项目
     * @param number1 最后一个项目
     * @return grammaticalAnalysier& this
     */
    template <typename T>
    grammaticalAnalysier &addGramaticRule(std::vector<rule_t> &total_rule,
                                          T number1) {
        makeRule<T>(total_rule, number1);
        return *this;
    }
    /**
     * @brief 判断一个名称是否为一个token
     * 如果当前没有同名的语法规则，会被认为是一个token
     */
    bool isToken(std::string) const;
    /**
     * @brief 消除当前所有规则中重复的规则并且排序
     */
    void remove_repeat();
    /**
     * @brief 添加一个新的规则
     *
     * @param name 规则名称
     * @param total_rule 所有规则
     */
    void add_rule(const ::std::string name, const std::vector<rule_t> &total_rule) {
        for(auto rule : total_rule) {
            add_rule(name, rule);
        }
    }
    /**
     * @brief 为一个规则名称添加一个规则
     *
     * @param name 规则名称
     * @param total_rule 新添加的规则
     */
    virtual void add_rule(const ::std::string name, const rule_t &total_rule);
    /**
     * @brief 为第n个状态添加规则为rule的规则name
     *
     * @param n 终结状态的标号
     * @param name 规则名称
     * @param rule 规则内容
     */
    virtual void add_end(const int n, const std::string name, rule_t rule);
    /**
     * @brief 为规则群total_rule添加一个规则
     *
     * @tparam T 规则类型
     * @param total_rule 当前所有规则
     * @param add_rule 添加的规则
     */
    template<typename T>
    void makeRule(std::vector<rule_t> &total_rule, T add_rule);
    /**
     * @brief  将一个规则链接到特定的位置
     *
     * @param name 规则名称
     * @param end 规则的后缀
     * @param start 规则的起始点
     */
    void set_to(std::string name, std::string end, int start);
private:
    bool DFAhas_make;
    /**
     * @brief
     * [自动机标号<<转换token,期待结尾> ,跳转为结尾]
     */
    typedef ::std::vector<std::map<::std::string, int> > state_machine;
    ::std::map<::std::pair<::std::string, ::std::string>, int> query;
    std::map<std::string, std::vector<rule_t> >all_rule;
    ::std::map<int, matchingDFA> in_a_end;
    std::string end_rule;
    state_machine state_map;
};
} // namespace theNext