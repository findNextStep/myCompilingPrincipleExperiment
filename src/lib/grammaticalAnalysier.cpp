#include "grammaticalAnalysier.hpp"
#include <algorithm>
#include <list>
#include <stack>

namespace theNext {

gramaticalTree grammaticalAnalysier::analise(const std::vector<token> token_list)const {
    using nlohmann::json;
    json js;
    js["type"] = this->end_rule;
    gramaticalTree ans(token::fromJson(js));
    ::std::list<gramaticalTree> buffer;
    int state = 0;
    int i = 0;

    for(auto it = token_list.begin(); it != token_list.end(); ++it) {
        auto toke = *it;
        state = 0;
        for(auto tree : buffer) {
            state = state_map.at(state).at(tree.my.type);
            // cout << tree.my.type << "\t" << state << endl;
        }
        // cout << i << endl << endl;
        ++i;
        if(this->state_map[state].end() != this->state_map[state].find(toke.type)) {
            /* 如果当前结点存在下一步 */
            state = this->state_map[state].at(toke.type);
            buffer.push_back(toke);
        } else if(this->in_a_end.end() != this->in_a_end.find(state)) {
            /* 如果当前节点不存在路径，检查是否有结局 */
            gramaticalTree new_node("");
            bool first = true;
            auto name = this->in_a_end.at(state).analise([&buffer, &new_node, &first](::std::string & next) {
                if(buffer.size()) {
                    if(first) {
                        first = false;
                        next = buffer.rbegin()->my.type;
                    } else {
                        new_node.addSon_back(*buffer.rbegin());
                        buffer.pop_back();
                        if(buffer.size()) {
                            next = buffer.rbegin()->my.type;
                        } else {
                            return false;
                        }
                    }
                    return true;
                }
                return false;
            });
            new_node.my.type = name;
            buffer.push_back(new_node);
            state = 0;
            // for(auto tree : buffer) {
            //     cout << tree.my.type << "\t";
            // }
            // cout << endl;
            for(auto tree : buffer) {
                if(tree.my.type == this->end_rule) {
                    return tree;
                }
                // cout << tree.my.type << "\t" << state << endl;
                state = state_map.at(state).at(tree.my.type);
            }
            // cout << i << endl << endl;
            --it;
            if(name == "") {
                exit(32);
            }
        } else {
            exit(234);
        }
    }
    return gramaticalTree(token_list[0]);
}

}// namespace theNext
