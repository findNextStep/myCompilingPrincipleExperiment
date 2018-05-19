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
 * @tparam TYPE 继承于::theNext::::std::string，默认构造函数为初始状态,设置友元类
 */
class lexicalAnalysier {
public:
    // 类型定义
    typedef ::std::string type_t;
    typedef ::theNext::token token;
    typedef ::std::string TYPE;
    // 分析内容定义
    typedef ::std::string text_t;
    // 状态转换函数定义
    typedef ::std::pair<std::pair<TYPE, char>, TYPE> state_change_t;
    // 结束方式
    typedef ::std::pair<TYPE, type_t> end_state_t;
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
    this_t &defineKeyWords(std::string word, TYPE type) {
        ::std::string now_state;
        std::string name;
        for(auto c : word) {
            name += c;
            if(this->query_state(now_state, c) != this->state_change_map.end()) {
                // 判断原本到达的位置
                auto replace = this->query_state(now_state, c)->second;
                // 获取原本位置所用的出度
                auto out = this->whereIgo(replace);
                for(auto pair : out) {
                    this->state_change_map[::std::make_pair(name, pair.first)] =  pair.second;
                }
            }
            this->state_change_map[std::make_pair(now_state, c)] = ::std::string(name);
            now_state = ::std::string(name);
        }
        this->end_state[::std::string(word)] = type;
        return *this;
    }
public:
    /**
     * @brief 分析函数
     *
     * @param context 分析的文章
     */
    ::std::vector<token> analysis(::std::string context) const {
        ::std::vector<token> ans;
        ::std::string now_state;
        text_t buffer = "";
        int line = 0 , colw = 0;
        for(auto it = context.begin(); it != context.end(); ++it) {
            ++colw;
            if(*it == '\n') {
                ++line;
                colw = 0;
            }
            if(this->query_state(now_state, *it) != this->state_change_map.end()) {
                now_state = query_state(now_state, *it)->second;
                buffer += *it;
            } else if(this->query_type(now_state) != this->end_state.end()) {
                token n;
                n.content = buffer;
                n.type = this->query_type(now_state)->second;
                ans.push_back(n);
                now_state = ::std::string();
                buffer = "";
                it--;
            } else {
                lexicalAnalysierFailExctption error;
                error.line = line;
                error.clow = colw;
                error.errorMessage = "unKnow statement when meet : " + buffer + *it;
            }
        }
        if(this->query_type(now_state) != this->end_state.end()) {
            token n;
            n.content = buffer;
            n.type = this->query_type(now_state)->second;
            ans.push_back(n);
        }
        return ans;
    }
protected:
    /**
     * @brief 返回一个DFA节点的全部出度
     *
     * @param type 查询的节点
     * @return vector<pair<char,::std::string> > 出度表
     */
    ::std::vector<std::pair<char, ::std::string> > whereIgo(::std::string type)const {
        ::std::vector<std::pair<char, ::std::string> >ans;
        for(auto item : state_change_map) {
            if(item.first.first == type) {
                ans.push_back(std::make_pair(item.first.second, item.second));
            }
        }
        return ans;
    }
    std::map<std::pair<::std::string, char>, ::std::string>::const_iterator query_state(::std::string type, char a)const {
        return this->state_change_map.find(::std::make_pair(type, a));
    }
    ::std::map<::std::string, TYPE>::const_iterator query_type(::std::string type)const {
        return this->end_state.find(type);
    }
public:
    // 状态转换函数列表
    ::std::map<std::pair<::std::string, char>, ::std::string> state_change_map;
    // 结束处理列表
    ::std::map<::std::string, TYPE> end_state;
};

} // namespace theNext
