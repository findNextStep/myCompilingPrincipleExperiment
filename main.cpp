#include <iostream>
#include "lexicalAnalysier.hpp"
#include "threadLanguage/threadSetting.hpp"

using ::theNext::threadSetting::threadState;
using namespace theNext;
using namespace std;

int main(int, char **) {
    ::theNext::lexicalAnalysier<threadState> analise = theNext::threadSetting::getlex();
    for(auto item : analise.state_change_map) {
        cout << item.first.first.getType() << " --\"" << item.first.second << "\"-->" << item.second.getType() << endl;
    }
    string input;
    while(cin >> input) {
        auto ans = analise.analysis(input);
        cout << "end";
        for(auto a : ans) {
            cout << a.toJson() << endl;
        }

    }
    return 0;
}
