#include <string>
#include <map>
#include <vector>
#include "struct/token.hpp"
#include <nlohmann/json.hpp>

namespace theNext {
/**
 * @brief 语法结构输出
 * 
 */
struct gramaticalTree {
private:
    std::vector<gramaticalTree> son;
public:
    token my;
    /**
     * @brief 初始化结构，使用输入参数作为结点类型
     * 
     * @param name 类型
     */
    gramaticalTree(::std::string name) {
        this->my.type = name;
    }
    /**
     * @brief 通过直接添加一个token实现初始化
     * 
     * @param toke token本身
     */
    gramaticalTree(token toke): my(toke) { }
    ~gramaticalTree() { }
    /**
     * @brief 添加一个子树
     * 
     * @param son 子树
     * @return gramaticalTree& this
     */
    gramaticalTree &addSon(const gramaticalTree &son) {
        this->son.push_back(son);
        return *this;
    }
    /**
     * @brief 在队头添加一个子树
     * 
     * @param son 需要添加的子树
     * @return gramaticalTree& this
     */
    gramaticalTree &addSon_back(const gramaticalTree &son) {
        this->son.insert(this->son.begin(), son);
        return *this;
    }
    /**
     * @brief 转换为json格式
     * 
     * @return nlohmann::json 
     */
    nlohmann::json toJson()const {
        auto ans = this->my.toJson();
        for(auto s : son) {
            ans["son"].push_back(s.toJson());
        }
        return ans;
    }
};
} // namespace theNext