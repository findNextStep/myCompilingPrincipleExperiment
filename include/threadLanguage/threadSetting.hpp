#pragma once
#include "struct/token.hpp"
#include "lexicalAnalysier.hpp"
#include "grammaticalAnalysier.hpp"

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
    ans.addStateChangeWay(start, '_', identifier);

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

auto getgra() {
    grammaticalAnalysier ana;
    ana.addGramaticRule("ThreadSpec",
                        rule_t({"thread", "identifier"}),
                        optional({"features", "featureSpec"}),
                        optional({"flows", "flowSpec"}),
                        optional({"properties", "association", ";"}),
                        rule_t({"end", "identifier", ";"}));
    ana.addGramaticRule("featureSpec", rule_t({"portSpec"}));
    ana.addGramaticRule("featureSpec", rule_t({"ParameterSpec"}));
    ana.addGramaticRule("featureSpec", rule_t({"none"}));
    ana.addGramaticRule("portSpec",
                        rule_t({"identifier", ":", "IOtype", "portType"}),
                        option_and_repeat({"{", "association", "}"}),
                        rule_t({";"}));
    ana.addGramaticRule("portType",
                        rule_t({"data", "port"}),
                        optional({"reference"}));
    ana.addGramaticRule("portType",
                        rule_t({"event", "data", "port"}),
                        optional({"reference"}));

    ana.addGramaticRule("portType",
                        rule_t({"event", "port"}));
    ana.addGramaticRule("ParameterSpec",
                        rule_t({"identifier", ":", "IOtype", "parameter" }),
                        optional({"reference"}),
                        option_and_repeat({"{", "association", "}"}),
                        rule_t({";"}));
    ana.addGramaticRule("IOtype", rule_t({"in"}));
    ana.addGramaticRule("IOtype", rule_t({"out"}));
    ana.addGramaticRule("IOtype", rule_t({"in", "out"}));
    ana.addGramaticRule("flowSpec", rule_t({"flowSourceSpec"}));
    ana.addGramaticRule("flowSpec", rule_t({"flowSinkSpec"}));
    ana.addGramaticRule("flowSpec", rule_t({"flowPathSpec"}));
    ana.addGramaticRule("flowSpec", rule_t({"none", ";"}));
    ana.addGramaticRule("flowSourceSpec", rule_t({"identifier", ":", "flow", "source", "identifier"}),
                        option_and_repeat({"{", "association", "}"}),
                        rule_t({";"}));
    ana.addGramaticRule("flowSinkSpec",
                        rule_t({"identifier", ":", "flow", "source", "identifier"}),
                        option_and_repeat({"association"}));
    ana.addGramaticRule("flowPathSpec", rule_t({"identifier", ":", "flow", "path", "identifier", "->", "identifier", ";"}));
    ana.addGramaticRule("association", optional({"identifier", "::"}),
                        rule_t({"identifier", "splitter"}),
                        optional({"constant"}),
                        rule_t({"access", "decimal"}));
    ana.addGramaticRule("association", rule_t({"none"}));
    ana.addGramaticRule("splitter", rule_t({"+=>"}));
    ana.addGramaticRule("splitter", rule_t({"=>"}));
    ana.addGramaticRule("reference",
                        optional({"packageName"}),
                        rule_t({"identifier"}));

    ana.addGramaticRule("packageName",
                        rule_t({"identifier", "::"})
                       );

    return ana;
}



} // namespace threadSetting
} // namespace theNext