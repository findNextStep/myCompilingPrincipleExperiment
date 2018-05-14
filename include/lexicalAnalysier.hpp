#pragma once
#include <functional>   // ::std::function
#include <string>       // ::std::string
#include <map>          // ::std::map
#include <vector>       // ::std::vector
#include <memory>       // ::std::shared_ptr
#include "struct/token.hpp"


namespace theNext {

class lexicalAnalysierFailExctption: public ::std::exception {
public:
    int line;
    int clow;
    ::std::string errorMessage;
};

/**
 * @brief 建立简单的词法分析器
 *
 * @tparam TYPE 继承于::theNext::token_type，默认构造函数为初始状态,设置友元类
 */
template<typename TYPE>
class lexicalAnalysier {
public:
    // 类型定义
    typedef ::theNext::token_type type_t;
    typedef ::theNext::token token;
    // 分析内容定义
    typedef ::std::string text_t;
    // 状态转换函数定义
    typedef ::std::pair<std::pair<TYPE, char>, TYPE> state_change_t;
    // 结束方式
    typedef ::std::pair<TYPE, type_t> end_state_t;
    // 本体类型
    typedef theNext::lexicalAnalysier<TYPE> this_t;
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
    this_t &addStateChangeWay(TYPE nowState, char nowChar, TYPE nextState) {
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
    this_t &defineEndState(TYPE nowState, TYPE outState) {
        this->end_state[nowState] = nowState;
        return *this;
    }
public:
    /**
     * @brief 分析函数
     *
     * @param context 分析的文章
     */
    ::std::vector<token> analysis(::std::string context) {
        ::std::vector<token> ans;
        TYPE now_state;
        text_t buffer = "";
        int line = 0 , colw = 0;
        for(auto it = context.begin(); it != context.end(); ++it) {
            ++colw;
            if(*it == '\n') {
                ++line;
                colw = 0;
            }
            if(this->query_state(now_state, *it) != this->state_change_map.end()) {
                now_state = *query_state(now_state, *it);
                buffer += *it;
            } else if(this->query_type(now_state) != this->end_state.end()) {
                token n;
                n.content = buffer;
                n.type = this->query_type(now_state);
                ans.push_back(n);
                buffer = *it;
            } else {
                lexicalAnalysierFailExctption error;
                error.line = line;
                error.clow = colw;
                error.errorMessage = "unKnow statement when meet : " + buffer + *it;
            }
        }
        return ans;
    }
protected:
    auto query_state(TYPE type, char a) {
        return this->state_change_map.find(::std::make_pair(type, a));
    }
    auto query_type(TYPE type) {
        return this->end_state.find(type);
    }
private:
    // 状态转换函数列表
    ::std::map<std::pair<TYPE, char>, TYPE> state_change_map;
    // 结束处理列表
    ::std::map<TYPE, TYPE> end_state;
};

} // namespace theNext
