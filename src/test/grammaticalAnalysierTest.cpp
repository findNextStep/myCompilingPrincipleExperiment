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
    ana.addGramaticRule("portSpec",
                        rule_t({"identifier", ":", "IOtype", "portType"}),
                        optional(repeat({"{", "association", "}"})));
    return 0;
}