#pragma once
#include <functional>   // ::std::function
#include <string>       // ::std::string
#include <map>          // ::std::map
#include <vector>       // ::std::vector
#include <memory>       // ::std::shared_ptr
#include <sstream>
#include "struct/token.hpp"


namespace theNext {

class lexicalAnalysierFailExctption: public ::std::exception {
public:
    int line;
    int clow;
    // 当前分析的结尾
    ::std::string::iterator end;
    // 错误信息
    ::std::string errorMessage;
    // 当前缓冲中的内容
    ::std::string buffer;
    // 当前状态
    ::std::string nowState;
    ::std::string what() {
        std::stringstream ss;
        ss << line << ":" << clow << "\t" << errorMessage;
        return ss.str();
    }
};

/**
 * @brief 建立简单的词法分析器
 */
class lexicalAnalysier {
public:
    // 类型定义
    typedef ::std::string type_t;
    typedef ::theNext::token token;
    // 分析内容定义
    typedef ::std::string text_t;
    // 状态转换函数定义
    typedef ::std::pair<std::pair<::std::string, char>, ::std::string> state_change_t;
    // 结束方式
    typedef ::std::pair<::std::string, type_t> end_state_t;
    // 本体类型
    typedef theNext::lexicalAnalysier this_t;
public:
    // 设置用函数
    lexicalAnalysier() {}
    ~lexicalAnalysier() {};
    /**
     * @brief 设置状态转换
     *
     * @param nowState 当前状态
     * @param nowChar 状态下出现的字符
     * @param nextState
     * @return this_t&
     */
    this_t &addStateChangeWay(::std::string nowState, char nowChar, const ::std::string &nextState) {
        this->state_change_map[::std::make_pair(nowState, nowChar)] = nextState;
        return *this;
    }
    /**
     * @brief 定义一个状态的结束状态
     * 在一个自动机结束（没有相应的匹配）的时候调用
     * 判断当前缓冲中的字符串的类型
     * @param nowState 当前状态
     * @param outState 结束后当前字符的类型
     * @return this_t&
     */
    this_t &defineEndState(const ::std::string &nowState, const ::std::string &outState) {
        this->end_state[nowState] = outState;
        return *this;
    }
    /**
     * @brief 添加一个关键字
     *
     * @param word 关键字内容
     * @param type 关键字类型
     * @return this_t&
     */
    this_t &defineKeyWords(const std::string &word, const ::std::string &type);
    /**
     * @brief 添加一个关键字
     * 关键字类型就是关键字本身
     * @param word 关键字
     * @return this_t&
     */
    this_t &defineKeyWords(const std::string &word) {
        return defineKeyWords(word, word);
    }
public:
    /**
     * @brief 分析函数
     *
     * @param context 分析的文章
     */
    ::std::vector<token> analysis(::std::string &context) const;

protected:
    /**
     * @brief 返回一个DFA节点的全部出度
     *
     * @param type 查询的节点
     * @return vector<pair<char,::std::string> > 出度表
     */
    ::std::vector<std::pair<char, ::std::string> > whereIgo(::std::string type)const;
    /**
     * @brief 查找下一个状态
     *
     * @param type 当前状态
     * @param a 下一个字符
     * @return std::map<std::pair<::std::string, char>, ::std::string>::const_iterator 下一个状态或者end()
     */
    std::map<std::pair<::std::string, char>, ::std::string>::const_iterator query_state(::std::string type, char a)const {
        return this->state_change_map.find(::std::make_pair(type, a));
    }
    /**
     * @brief 查找终止状态
     *
     * @param type 状态
     * @return ::std::map<::std::string, ::std::string>::const_iterator 状态对应的结束类型或者end()
     */
    ::std::map<::std::string, ::std::string>::const_iterator query_type(::std::string type)const {
        return this->end_state.find(type);
    }
private:
    // 状态转换函数列表
    ::std::map<std::pair<::std::string, char>, ::std::string> state_change_map;
    // 结束处理列表
    ::std::map<::std::string, ::std::string> end_state;
};

} // namespace theNext
