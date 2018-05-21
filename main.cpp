#include <iostream>
#include <fstream>
#include "lexicalAnalysier.hpp"
#include "threadLanguage/threadSetting.hpp"

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

int main(const int argc, const char **argv) {
    string fileName = "/media/pxq/data/cuorse/complie/task/1task/testcase/test_txt/test2.txt";
    if(argc == 2) {
        fileName = argv[1];
    }
    auto lex = ::theNext::threadSetting::getlex();

    auto content = readFile(fileName);
    ::theNext::lexicalAnalysier::preprocessing(content);

    std::vector<theNext::token> ans;
    ::std::string::iterator now = content.begin();
    int li = 0, cl = 0;
    while(now != content.end() && ans.size() == 0) {
        try {
            ans = lex.analysis(content);
        } catch(const ::theNext::lexicalAnalysierFailExctption &e) {
            now = e.end;
            li += e.line;
            if(e.line != 0) {
                cl = e.clow;
            } else {
                cl += e.clow - 1;
            }
            cout << li << ":" << cl << "\t" << e.buffer <<  " when " << *e.end << endl;
            if(e.nowState == "") {
                ++now;
            }
            content = std::string(now, content.end());
            now = content.begin();
        }
        cout << ans.size() << endl;
    }
    for(auto token : ans) {
        cout << token.type << "\t" << token.content << endl;
    }
    return 0;
}
