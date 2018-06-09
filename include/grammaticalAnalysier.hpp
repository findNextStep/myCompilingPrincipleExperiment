#include "struct/token.hpp"
#include <map>
#include <string>

namespace theNext {
class optional : public ::std::vector<::std::string> {
public:
    optional(std::vector<std::string> init): std::vector<std::string> (init) {}
};
class repeat : public ::std::vector<::std::string> {
public:
    repeat(std::vector<std::string> init): std::vector<std::string> (init) {}
};
/**
 * @brief
 * reg_base(type)
 * - reg_char{token}
 * - reg_rule{base[]}
 * - reg_repeat{base[]}
 * - reg_optional{base[]}
 * {state--token-->state}
 * {state-->{front,new}}
 */
class grammaticalAnalysier {
public:
    typedef ::std::map<::std::string,::std::string> state_mecian;
    grammaticalAnalysier() {}
    ~grammaticalAnalysier() {}
    template <typename T, Args...Args>
    grammaticalAnalysier &addGramaticRule(const string &rulename, T number1 , Args... numbers) {
        return *this;
    }
protected:
private:
    
};
} // namespace theNext