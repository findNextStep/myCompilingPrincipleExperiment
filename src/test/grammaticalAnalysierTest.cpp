#include<grammaticalAnalysier.hpp>
using namespace theNext;
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
    ana.addGramaticRule("flowPathSpec", rule_t({"identifier", ":", "flow", "path", "identifier", "->", "identifier", ";"}));
    ana.addGramaticRule("association", optional({"identifier", "::"}),
                        rule_t({"identifier", "splitter"}),
                        optional({"constant"}),
                        rule_t({"access", "decimal"}));
    ana.addGramaticRule("association", rule_t({"none"}));
    ana.addGramaticRule("splitter", rule_t({"+=>"}));
    ana.addGramaticRule("splitter", rule_t({"=>"}));
    ana.addGramaticRule("reference",
                        optional({"packageName", "::"}),
                        rule_t({"identifier"}));

    ana.addGramaticRule("packageName",
                        repeat({"identifier", "::"}),
                        rule_t({"identifier"}));
    ana.setEndRule("ThreadSpec");

    // ana.addGramaticRule("A", rule_t({"{", "A", "}"}));
    // ana.addGramaticRule("A",rule_t({"a"}));
    // ana.addGramaticRule("A",rule_t());
    // ana.setEndRule("A");
    ana.makeDFA();

    return 0;
}