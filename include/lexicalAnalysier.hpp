#pragma once
#include <functional>   // ::std::function
#include <string>       // ::std::string
#include <map>          // ::std::map
#include <vector>       // ::std::vector

namespace theNext {
/**
 * @brief 词法分析器
 */
class lexicalAnalysier {
public:
    // 类型定义
    typedef const ::std::string type_t;
    // 分析内容定义
    typedef ::std::string text_t;
    // 状态转换函数定义
    typedef ::std::function<type_t(text_t::iterator &, text_t::iterator)> state_change_t;
public:
    // 设置用函数
    lexicalAnalysier(/* args */) {};
    ~lexicalAnalysier() {};
private:
};


} // namespace theNext