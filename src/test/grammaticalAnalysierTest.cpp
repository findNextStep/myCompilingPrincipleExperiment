#include <grammaticalAnalysier.hpp>
#include <threadLanguage/threadSetting.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tool/treePrinter.hpp>

using namespace theNext;
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


int main() {
    auto lex = theNext::threadSetting::getlex();
    auto ana = theNext::threadSetting::getgra();

    std::string path;
    std::cin >> path;
    auto content = readFile(path);
    cout << ana.analise(lex.analysis(content)).toJson().dump(2) << endl;
    auto ans = ana.analise(lex.analysis(content));
    theNext::treePrinter printer({threadSetting::identifier, threadSetting::decimal});
    printer.setTree(ans.toJson());
    cout << printer.toList() << endl;
    return 0;
}