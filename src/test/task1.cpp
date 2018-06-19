#include <iostream>
#include <fstream>
#include "threadLanguage/threadSetting.hpp"
using namespace std;

/**
 * @brief 文件读取函数
 *
 * @param name 文件名或者文件路径
 * @return string 文件内容
 */
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


int main(const int argc, char const *argv[]) {
    std::string fileName;
    if(argc >= 2) {
        fileName = std::string(argv[1]);
    } else {
        cin >> fileName;
    }
    auto lex = ::theNext::threadSetting::getlex();

    auto content = readFile(fileName);

    std::vector<theNext::token> ans;
    ::std::string::iterator now = content.begin();
    int li = 0, cl = 0;
    bool catchError = false;
    while(now != content.end() && ans.size() == 0) {
        try {
            ans = lex.analysis(content);
        } catch(const ::theNext::lexicalAnalysierFailExctption &e) {
            catchError = true;
            now = e.end;
            li += e.line;
            if(e.line != 0) {
                cl = e.clow;
            } else {
                cl += e.clow - 1;
            }
            // cout << li + 1 << ":" << cl << "\t" << e.buffer <<  " when " << *e.end << endl;
            cout << "Unrecognizable characters" << *e.end << " in line " << li + 1 << ":" << cl << endl;
            if(e.nowState == "") {
                ++now;
            }
            content = string(now, content.end());
            now = content.begin();
        }
    }
    if(!catchError) {
        ofstream fout("tokenOut.txt");
        for(auto token : ans) {
            fout << token.type << "\t" << token.content << endl;
        }
    }
    return 0;
}
