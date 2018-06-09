#include<grammaticalAnalysier.hpp>

int main() {
    ::theNext::grammaticalAnalysier ana;
    ana.addGramaticRule("ThreadSpaec", theNext::rule_t({"thread", "identifier"}), theNext::optional({"features", "featureSpace"}));
}