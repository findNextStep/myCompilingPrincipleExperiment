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
    /**
     * @brief 判断一个类型是不是一个错误
     *
     * @return true 这个类型是一个错误
     * @return false 这个类型不是一个错误
     */
    bool isError()const {
        return this->is_error;
    }
    /**
     * @brief 复制操作符
     *
     * @param b 被复制对象
     * @return token_type&
     */
    token_type &operator=(const token_type &b) {
        this->this_type = b.this_type;
        this->setIfError(b.isError());
        return *this;
    }
    /**
     * @brief 比较二者是否相等
     *
     * @param b 被比较对象
     * @return true 两者相等
     * @return false 两者不相等
     */
    bool operator==(const token_type &b)const {
        return this->getType() == b.getType();
    }
    /**
     * @brief 复制构造函数
     *
     * @param other 被复制对象
     */
    token_type(const token_type &other) {
        *this = other;
    }

protected:
    /**
     * @brief 设置这个类型是不是一个错误
     *
     * @param ifIsError
     */
    void    setIfError(bool ifIsError) {
        this->is_error = ifIsError;
    }
    /**
     * @brief 提供参数的构造函数
     * 
     * @param type 类型名称
     * @param iserror 是否是一个错误
     */
    token_type(const ::std::string type, bool iserror = false): this_type(type) {
        this->setIfError(iserror);
    }
private:
    bool is_error;
    ::std::string this_type;
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