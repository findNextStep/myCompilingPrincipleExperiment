#pragma once
#include <string>       // ::std::string
#include "nlohmann/json.hpp"

namespace theNext {
/**
 * @brief 词法分析的结果
 * 保存了词法分析得到的类型和token所表示的内容
 */
struct token {
    /**
     * @brief 分析的内容
     *
     */
    ::std::string content;
    /**
     * @brief 词法分析的结果
     */
    ::std::string type;
    ::nlohmann::json toJson() const;
    token static fromJson(::nlohmann::json json);
};
} // namespace theNext