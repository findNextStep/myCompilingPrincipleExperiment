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
        string ans = buffer;
        delete[] buffer;
        return ans;
    }
    return "";
}

int main(const int argc, const char **argv) {
    string fileName = "/media/pxq/data/cuorse/complie/task/1task/testcase/test_txt/test1.txt";
    if(argc == 2) {
        fileName = argv[1];
    }
    auto lex = ::theNext::threadSetting::getlex();

    auto content = readFile(fileName);
    cout << content << endl;

    auto ans = lex.analysis(content);
    for(auto token : ans) {
        cout << token.toJson() << endl;
    }
    return 0;
}
