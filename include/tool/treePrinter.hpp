#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

namespace theNext {

class treePrinter {
public:
    typedef ::nlohmann::json json;
    typedef ::std::vector<std::string> passList_t;
private:
    /**
     * @brief 需要显示的树的内容
     */
    ::nlohmann::json tree;
    /**
     * @brief 需要输出的结点类型
     *
     */
    passList_t pass_list;
protected:
    /**
     * @brief 判断一个结点是否需要输出
     * 如果一个结点本身的类型需要输出，或者其子树需要输出
     * 则这个结点需要输出
     * @param js 需要输出的结点
     * @param list 需要输出的类型名称列表
     * @return true 这个结点需要输出
     * @return false 这个结点不需要输出
     */
    bool static need_to_print(const json &js, const std::vector<std::string> &list);
    /**
     * @brief 删除子树中所有的不需要的子树
     * 需要通过need_to_print判断
     * @param js 进行处理的结点
     * @param list 可以输出的类型名列表
     * @return json 消除的内容
     */
    json static remove_unneed(const json &js, const std::vector<std::string> &list);
    /**
     * @brief 对当前的js递归的通过缩进格式化
     *
     * @param js 需要输出的js
     * @param level 当前需要的缩进等级
     * @param index 缩进的格子数
     * @return std::string 格式化之后的结果
     */
    std::string static printTree(const json &js, const int level, const int index);
    /**
     * @brief 初始化tree
     *
     * @param js
     */
    void init(const json &js);
public:
    treePrinter(const passList_t &passlist);
    ~treePrinter() {};
    /**
     * @brief 设置自身的js内容
     *
     * @param tree
     */
    void setTree(json tree) {
        return this->init(tree);
    }
    /**
     * @brief 直接返回js格式化输出后的结果
     *
     * @param index 缩进比例
     * @return std::string
     */
    std::string toJson(int index = 4) {
        return this->tree.dump(index);
    }
    /**
     * @brief 通过缩进格式化输出
     *
     * @param index 格式化每一个的缩进量
     * @return std::string
     */
    std::string toList(int index = 4);
};
} // namespace theNext
