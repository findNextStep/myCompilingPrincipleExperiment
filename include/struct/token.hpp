#pragma once
#include <string>       // ::std::string
#include <memory>

namespace theNext {
/**
 * @brief token类型定义
 *
 */
class token_type {
public:
    /**
     * @brief 获取类型的说明
     *
     * @return const ::std::string 固定值，类型名称
     */
    virtual const ::std::string getType() const {
        return this->this_type;
    }
    bool operator==(token_type b) {
        return this->getType() == b.getType();
    }

protected:
    token_type(const ::std::string type): this_type(type) {}
private:
    const ::std::string this_type;
};
/**
 * @brief 词法分析的结果
 * 保存了词法分析得到的类型和token所表示的内容
 */
struct token {
    typedef token_type *type_t;
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