#pragma once
#include "struct/token.hpp"
#include "lexicalAnalysier.hpp"

namespace theNext {
namespace threadSetting {

class threadState: public token_type {
    threadState(::std::string content): token_type(content) {}
public:
// 定义状态
    threadState(): token_type() {}
    // 标识符
    const static threadState identifier;
    // 一个+符号
    const static threadState addOp;
    // 一个-符号
    const static threadState subOp;
    // ->
    const static threadState subArrow;

    // 一个没有小数点的数字
    const static threadState decimalA;
    // 一个有小数点的数字
    const static threadState decimalB;
    // 一个{
    const static threadState leftBrace;
    // 一个}
    const static threadState rightBrace;
    // 一个:
    const static threadState colon;
    // 两个:
    const static threadState doubleColon;
    // 一个=
    const static threadState equal;
    // 一个=>
    const static threadState equalArrow;
    // +=
    const static threadState addEqual;
    // +=>
    const static threadState addEqualArrow;

// 定义类型
    // 一个操作符
    const static threadState operators;
    // 一个数字
    const static threadState decimal;
    // 一个关键字
    const static threadState keyWords;
};

const threadState threadState::identifier("identifier");
const threadState threadState::addOp("add_op");
const threadState threadState::subOp("sub_op");
const threadState threadState::subArrow("subArrow");
const threadState threadState::decimalA("decimalA");
const threadState threadState::decimalB("decimalB");
const threadState threadState::operators("operators");

const threadState threadState::keyWords("keyWord");
const threadState threadState::decimal("decimal");

const threadState threadState::leftBrace("leftBrace");
const threadState threadState::rightBrace("rightBrace");
const threadState threadState::colon("colon");
const threadState threadState::doubleColon("doubleColon");
const threadState threadState::equal("equal");
const threadState threadState::equalArrow("equalArrow");
const threadState threadState::addEqual("addEqual");
const threadState threadState::addEqualArrow("addEqualArrow");

auto getlex() {
    ::theNext::lexicalAnalysier<threadState>ans;

    ans.addStateChangeWay(threadState(), ' ', threadState());
    ans.addStateChangeWay(threadState(), '\t', threadState());
    ans.addStateChangeWay(threadState(), '\n', threadState());

    for(char a = 'a'; a <= 'z'; ++a) {
        ans.addStateChangeWay(threadState(), a, threadState::identifier);
        ans.addStateChangeWay(threadState(), a + 'A' - 'a', threadState::identifier);
        ans.addStateChangeWay(threadState::identifier, a, threadState::identifier);
        ans.addStateChangeWay(threadState::identifier, a + 'A' - 'a', threadState::identifier);
    }
    ans.addStateChangeWay(threadState::identifier, '_', threadState::identifier);

    for(char a = '0'; a <= '9'; ++a) {
        ans.addStateChangeWay(threadState::identifier, a, threadState::identifier);
        ans.addStateChangeWay(threadState::addOp, a, threadState::decimalA);
        ans.addStateChangeWay(threadState::subOp, a, threadState::decimalA);
        ans.addStateChangeWay(threadState::decimalA, a, threadState::decimalA);
        ans.addStateChangeWay(threadState::decimalB, a, threadState::decimalB);
        ans.addStateChangeWay(threadState(), a, threadState::decimalA);
    }
    ans.addStateChangeWay(threadState::decimalA, '.', threadState::decimalB);

    ans.addStateChangeWay(threadState(), '+', threadState::addOp);
    ans.addStateChangeWay(threadState(), '-', threadState::subOp);

    // 定义结束跳转
    ans.defineEndState(threadState::decimalA, threadState::decimal);
    ans.defineEndState(threadState::decimalB, threadState::decimal);
    ans.defineEndState(threadState::identifier, threadState::identifier);

    // 定义操作符和关键字
    ans.defineKeyWords("+=>", threadState::operators);
    ans.defineKeyWords("->", threadState::operators);
    ans.defineKeyWords("{", threadState::operators);
    ans.defineKeyWords("}", threadState::operators);
    ans.defineKeyWords(":", threadState::operators);
    ans.defineKeyWords("::", threadState::operators);
    ans.defineKeyWords(";", threadState::operators);
    ans.defineKeyWords("=>", threadState::operators);

    ans.defineKeyWords("thread", threadState::keyWords);
    ans.defineKeyWords("features", threadState::keyWords);
    ans.defineKeyWords("flows", threadState::keyWords);
    ans.defineKeyWords("properties", threadState::keyWords);
    ans.defineKeyWords("end", threadState::keyWords);
    ans.defineKeyWords("none", threadState::keyWords);
    ans.defineKeyWords("in", threadState::keyWords);
    ans.defineKeyWords("out", threadState::keyWords);
    ans.defineKeyWords("data", threadState::keyWords);
    ans.defineKeyWords("port", threadState::keyWords);
    ans.defineKeyWords("event", threadState::keyWords);
    ans.defineKeyWords("parameter", threadState::keyWords);
    ans.defineKeyWords("flow", threadState::keyWords);
    ans.defineKeyWords("source", threadState::keyWords);
    ans.defineKeyWords("sink", threadState::keyWords);
    ans.defineKeyWords("path", threadState::keyWords);
    ans.defineKeyWords("constant", threadState::keyWords);
    ans.defineKeyWords("access", threadState::keyWords);
    return ans;
}


} // namespace threadSetting
} // namespace theNext