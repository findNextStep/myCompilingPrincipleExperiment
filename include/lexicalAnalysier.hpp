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
        this->end_state[nowState] = nowState;
        return *this;
    }
    /**
     * @brief 添加一个关键字
     *
     * @param word 关键字内容
     * @param type 关键字类型
     * @return this_t&
     */
    this_t &defineKeyWords(const std::string &word, const ::std::string &type) {
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
    ::std::vector<token> analysis(::std::string &context) const {
        ::std::vector<token> ans;
        // 记录当前状态，空状态为初始状态
        ::std::string now_state;
        // 分析内容缓存
        text_t buffer = "";
        // 记录行列数
        int line = 0, colw = 0;
        // 记录上一个字符，用于换行统计
        char last_char = ' ';
        for(::std::string::iterator it = context.begin(); it != context.end(); ++it) {
            // 列数++
            ++colw;
            if(*it == '\n' && last_char != '\r' || *it == '\r') {
                // 遇到回车行数++，列数归零
                ++line;
                colw = 0;
            }
            last_char = *it;
            // 如果状态重置，清空缓存
            if(now_state == ::std::string()) {
                buffer = "";
            }
            if(this->query_state(now_state, *it) != this->state_change_map.end()) {
                // 发现符合状态转换的自动机转化
                now_state = query_state(now_state, *it)->second;
                buffer += *it;
            } else if(this->query_type(now_state) != this->end_state.end()) {
                // 没有符合的转化，判断是不是一个结束状态
                token n;
                n.content = buffer;
                n.type = this->query_type(now_state)->second;
                ans.push_back(n);
                now_state = ::std::string();
                buffer = "";
                it--;
            } else {
                // 没有自动机匹配，也不是终止状态，报错
                lexicalAnalysierFailExctption error;
                error.line = line;
                error.clow = colw;
                error.end = it;
                error.buffer = buffer;
                error.nowState = now_state;
                error.errorMessage = "unKnow statement when meet : \"" + buffer + "\"\"" + *it + "\"";
                throw error;
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
