#include "grammaticalAnalysier.hpp"
#include <algorithm>
#include <list>
#include <stack>

namespace theNext {

gramaticalTree grammaticalAnalysier::analise(std::vector<token> token_list)const {
    using nlohmann::json;
    json js;
    js["type"] = this->end_rule;
    gramaticalTree ans(token::fromJson(js));
    ::std::list<gramaticalTree> buffer;
    int state = 0;

    for(auto toke : token_list) {
        if(this->state_map[state].end() != this->state_map[state].find(toke.type)) {
            /* 如果当前结点存在下一步 */
            state = this->state_map[state].at(toke.type);
            buffer.push_back(toke);
        } else if(this->in_a_end.end() != this->in_a_end.find(state)) {
            token there;
            there.type = this->in_a_end.find(state)->second.first;
            gramaticalTree now(there);
            std::stack<gramaticalTree> st;
            /* 反向迭代检查表格 */
            for(auto it = this->in_a_end.at(state).second.rbegin(); it != this->in_a_end.at(state).second.rend(); ++it) {
                if(*it == buffer.rbegin()->my.type) {
                    now.addSon(*buffer.rbegin());
                    buffer.pop_back();
                } else {
                    exit(233);
                }
            }
            buffer.push_back(now);
        } else {
            exit(234);
        }
    }
    return gramaticalTree(token_list[0]);
}

}// namespace theNext