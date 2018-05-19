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
    auto toJson() {
        ::nlohmann::json ans;
        ans["type"] = this->type;
        ans["content"] = this->content;
        return ans;
    }
    auto static fromJson(::nlohmann::json json) {
        token ans;
        ans.content = json["content"];
        ans.type = json["type"];
        return ans;
    }
};
} // namespace theNext