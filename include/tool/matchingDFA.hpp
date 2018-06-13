#include <string>
#include <map>
#include <vector>
#include <functional>

namespace theNext {

class matchingDFA {
private:
    ::std::vector<std::map<::std::string, int> > state_map;
    std::map<int, std::string>ans;
protected:
    std::string query(int i)const {
        if(ans.find(i) != ans.end()) {
            return ans.at(i);
        }
        return "";
    }
public:
    matchingDFA(): state_map(1) { }
    ~matchingDFA() { }

    void add(::std::vector<::std::string> rule, ::std::string name) {
        int now = 0;
        // for(auto s : rule) {
        for(auto it = rule.rbegin(); it != rule.rend(); ++it) {
            auto s = *it;
            if(state_map[now].find(s) != state_map[now].end()) {
                now = state_map[now][s];
            } else {
                now = state_map[now][s] = state_map.size();
                state_map.resize(state_map.size() + 1);
            }
        }
        // }
        if(ans.find(now) != ans.end() && ans[now] != name) {
            exit(23);
        }
        ans[now] = name;
    }

    std::string analise(const std::function<bool(std::string &)> &next)const {
        int now = 0;
        std::string path;
        while(next(path)) {
            if(state_map[now].find(path) != state_map[now].end()) {
                now = state_map.at(now).at(path);
            } else {
                break;
            }
        }
        return query(now);
    }

    std::string analise(const std::vector<std::string> &path) const {
        auto it = path.begin();
        return analise([&it, path](std::string & next) {
            if(it != path.end()) {
                next = *it;
                return true;
            }
            return false;
        });
    }
};

} // namespace TheNext
