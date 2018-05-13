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
    bool isError()const {
        return this->is_error;
    }

    bool operator==(const token_type &b)const {
        return this->getType() == b.getType();
    }
    token_type(const token_type &other) : this_type(other.this_type) {}

protected:
    void    setIfError(bool ifIsError) {
        this->is_error = ifIsError;
    }
    token_type(const ::std::string type): this_type(type) {}
private:
    bool is_error;
    const ::std::string this_type;
};
/**
 * @brief 词法分析的结果
 * 保存了词法分析得到的类型和token所表示的内容
 */
template<class TYPE>
struct token {
    /**
     * @brief 分析的内容
     *
     */
    ::std::string content;
    /**
     * @brief 词法分析的结果
     */
    TYPE type;
};
} // namespace theNext