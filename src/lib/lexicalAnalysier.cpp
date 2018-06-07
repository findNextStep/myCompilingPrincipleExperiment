#include "lexicalAnalysier.hpp"

namespace theNext {

lexicalAnalysier &lexicalAnalysier::defineKeyWords(const std::string &word, const ::std::string &type) {
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

::std::vector<token>lexicalAnalysier::analysis(::std::string &context) const {
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

::std::vector<std::pair<char, ::std::string> > lexicalAnalysier::whereIgo(::std::string type)const {
    ::std::vector<std::pair<char, ::std::string> >ans;
    for(auto item : state_change_map) {
        if(item.first.first == type) {
            ans.push_back(std::make_pair(item.first.second, item.second));
        }
    }
    return ans;
}
} // namespace theNext
