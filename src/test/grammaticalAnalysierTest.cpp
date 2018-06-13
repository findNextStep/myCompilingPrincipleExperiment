#include <grammaticalAnalysier.hpp>
#include <threadLanguage/threadSetting.hpp>
#include <fstream>
#include <iostream>

using namespace theNext;
using namespace std;
string readFile(string name) {
    std::ifstream is(name, std::ifstream::binary);
    if(is) {
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);
        char *buffer = new char [length];
        is.read(buffer, length);
        is.close();
        string ans = std::string(buffer, length);
        delete[] buffer;
        return ans;
    }
    return "";
}
int main() {
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
                        // ,rule_t({"identifier"})
                       );


    // ana.addGramaticRule("A", rule_t({"{", "A", "}"}));
    // ana.addGramaticRule("A",option_and_repeat({"a"}));
    // ana.addGramaticRule("A",rule_t());
    // ana.setEndRule("A");
    ana.makeDFA();
    auto lex = theNext::threadSetting::getlex();

    std::string path;
    std::cin >> path;
    auto content = readFile(path);
    cout << ana.analise(lex.analysis(content)).toJson() << endl;
    return 0;
}