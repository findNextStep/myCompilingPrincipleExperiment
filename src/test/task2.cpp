#include <iostream>
#include <fstream>
#include "threadLanguage/threadSetting.hpp"
#include "tool/treePrinter.hpp"

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


int main(int argc, char const *argv[]) {
    std::string filename = "tokenOut.txt";
    if(argc != 1) {
        filename = std::string(argv[1]);
    }
    ifstream fin(filename);
    std::string type, content;
    // 词法分析程序输出结果
    std::vector<theNext::token> ana_lex;
    // 输入词法分析程序task1的输出结果
    while(fin >> type >> content) {
        theNext::token token;
        token.type = type;
        token.content = content;
        ana_lex.push_back(token);
    }
    auto gra = theNext::threadSetting::getgra();
    auto ans = gra.analise(ana_lex);

    std::ofstream fout("SyntaxOut.txt");
    theNext::treePrinter tp({::theNext::threadSetting::identifier, ::theNext::threadSetting::decimal});
    tp.setTree(ans.toJson());
    cout << tp.toList() << endl;
    return 0;
}

