#pragma once
#include <functional>   // ::std::function
#include <string>       // ::std::string
#include <map>          // ::std::map
#include <vector>       // ::std::vector
#include <memory>       // ::std::shared_ptr
#include "struct/token.hpp"


namespace theNext {
/**
 * @brief 词法分析器
 *
 * @tparam T 类型定义器
 *      类型定义器中间应当全是static const ::std::string
 */
template<class TYPE>
class lexicalAnalysier {
public:
    // 类型定义
    typedef ::theNext::token_type type_t;
    // 分析内容定义
    typedef ::std::string text_t;
    // 状态转换函数定义
    typedef ::std::function<TYPE(text_t::iterator &, text_t::iterator)> state_change_t;
    // 判断终止（错误或者判断结束）回调函数
    typedef ::std::function < token(text_t, TYPE)> end_callback_t;
    // 本体类型
    typedef theNext::lexicalAnalysier<TYPE> this_t;
public:
    // 设置用函数

    lexicalAnalysier() {};
    ~lexicalAnalysier() {};

    this_t &addStateChangeFunc(TYPE type, const state_change_t &func) {
        this->state_change_list[type].push_back(func);
        return *this;
    }
private:
    // 状态转换函数列表
    ::std::map<type_t, ::std::vector<state_change_t> > state_change_list;
    // 当前状态
    TYPE now_state;
};

} // namespace theNext
