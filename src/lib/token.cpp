#include "struct/token.hpp"


namespace theNext {

::nlohmann::json token::toJson() {
    ::nlohmann::json ans;
    ans["type"] = this->type;
    ans["content"] = this->content;
    return ans;
}

token token::fromJson(::nlohmann::json json) {
    token ans;
    ans.content = json["content"];
    ans.type = json["type"];
    return ans;
}

} // namespace theNext
