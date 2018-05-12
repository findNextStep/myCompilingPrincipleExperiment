#pragma once
#include <string>       // ::std::string

namespace theNext {
/**
 * @brief 词法分析的结果
 *
 */
struct token {
    typedef ::std::string type_t;
    /**
     * @brief 分析的内容
     *
     */
    ::std::string content;
    /**
     * @brief 词法分析的结果
     */
    type_t type;
};
} // namespace theNext