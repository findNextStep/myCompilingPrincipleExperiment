#pragma once
#include "struct/token.hpp"
#include "lexicalAnalysier.hpp"

namespace theNext {
namespace threadSetting {

const ::std::string identifier("identifier");
const ::std::string start;
const ::std::string addOp("add_op");
const ::std::string subOp("sub_op");
const ::std::string subArrow("subArrow");
const ::std::string decimalA("decimalA");
const ::std::string decimalB("decimalB");
const ::std::string operators("operators");

const ::std::string keyWords("keyWord");
const ::std::string decimal("decimal");

const ::std::string leftBrace("leftBrace");
const ::std::string rightBrace("rightBrace");
const ::std::string colon("colon");
const ::std::string doubleColon("doubleColon");
const ::std::string equal("equal");
const ::std::string equalArrow("equalArrow");
const ::std::string addEqual("addEqual");
const ::std::string addEqualArrow("addEqualArrow");

auto getlex() {
    ::theNext::lexicalAnalysier ans;

    ans.addStateChangeWay(start, ' ', start);
    ans.addStateChangeWay(start, '\t', start);
    ans.addStateChangeWay(start, '\n', start);
    ans.addStateChangeWay(start, '\r', start);

    for(char a = 'a'; a <= 'z'; ++a) {
        ans.addStateChangeWay(start, a, identifier);
        ans.addStateChangeWay(start, a + 'A' - 'a', identifier);
        ans.addStateChangeWay(identifier, a, identifier);
        ans.addStateChangeWay(identifier, a + 'A' - 'a', identifier);
    }
    ans.addStateChangeWay(identifier, '_', identifier);
    ans.addStateChangeWay(start,'_',identifier);

    for(char a = '0'; a <= '9'; ++a) {
        ans.addStateChangeWay(identifier, a, identifier);
        ans.addStateChangeWay(addOp, a, decimalA);
        ans.addStateChangeWay(subOp, a, decimalA);
        ans.addStateChangeWay(decimalA, a, decimalA);
        ans.addStateChangeWay(decimalB, a, decimalB);
        ans.addStateChangeWay(start, a, decimalA);
    }
    ans.addStateChangeWay(decimalA, '.', decimalB);

    ans.addStateChangeWay(start, '+', addOp);
    ans.addStateChangeWay(start, '-', subOp);

    // 定义结束跳转
    ans.defineEndState(decimalB, decimal);
    ans.defineEndState(identifier, identifier);

    // // 定义操作符和关键字
    ans.defineKeyWords("+=>");
    ans.defineKeyWords("->");
    ans.defineKeyWords("{");
    ans.defineKeyWords("}");
    ans.defineKeyWords(":");
    ans.defineKeyWords("::");
    ans.defineKeyWords(";");
    ans.defineKeyWords("=>");

    ans.defineKeyWords("thread");
    ans.defineKeyWords("features");
    ans.defineKeyWords("flows");
    ans.defineKeyWords("properties");
    ans.defineKeyWords("end");
    ans.defineKeyWords("none");
    ans.defineKeyWords("in");
    ans.defineKeyWords("out");
    ans.defineKeyWords("data");
    ans.defineKeyWords("port");
    ans.defineKeyWords("event");
    ans.defineKeyWords("parameter");
    ans.defineKeyWords("flow");
    ans.defineKeyWords("source");
    ans.defineKeyWords("sink");
    ans.defineKeyWords("path");
    ans.defineKeyWords("constant");
    ans.defineKeyWords("access");
    return ans;
}


} // namespace threadSetting
} // namespace theNext