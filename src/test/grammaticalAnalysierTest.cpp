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

std::string mermaid(const ::nlohmann::json &js, int &i) {
    int my = i;
    std::stringstream ss;
    ss << i << '[' << js.at("type") << ']' << endl;
    std::string ans = ss.str();
    if(js.find("son") != js.end()) {
        for(auto son : js.at("son")) {
            i++;
            int sonnum = i;
            ans += mermaid(son, i);
            std::stringstream ss;
            ss << my << " --> " << sonnum << endl;
            ans += ss.str();
        }
    } else {
        ss << i << "[\"" << js.at("type").get<std::string>() << "<br>" << js.at("content").get<std::string>() << "\"]" << endl;
        ans = ss.str();
    }
    return ans;
}

int main() {
    auto lex = theNext::threadSetting::getlex();
    auto ana = theNext::threadSetting::getgra();

    std::string path;
    std::cin >> path;
    auto content = readFile(path);
    // cout << ana.analise(lex.analysis(content)).toJson().dump(2) << endl;
    auto ans = ana.analise(lex.analysis(content));
    theNext::treePrinter printer({threadSetting::identifier, threadSetting::decimal});
    printer.setTree(ans.toJson());
    // cout << printer.toList() << endl;
    int i = 0;
    ::nlohmann::json js = ::nlohmann::json::parse(printer.toJson());
    cout << js.dump(2) << endl;
    cout << mermaid(js, i) << endl;
    return 0;
}