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


int last = 0;
bool first = false;

/**
 * @brief 判断一个结点是否需要被显示
 *
 * @param js 结点
 * @param need_list 需要显示的类型表
 */
bool needoutput(const ::nlohmann::json &js, vector<std::string> need_list) {
    if(js.find("son") != js.end()) {
        bool need = false;
        for(auto son : js["son"]) {
            if(needoutput(son, need_list)) {
                return true;
            }
        }
        return false;
    } else {
        for(auto item : need_list) {
            if(item == js["type"].get<string>()) {
                return true;
            }
        }
        return false;
    }
}

/**
 * @brief 按照mermaid的流程图格式绘制语法分析树
 *
 * @param js 语法分析树结点
 * @param need_list 需要显示的类型
 * @param my 当前结点编号
 */
void printTree(const ::nlohmann::json &js, vector<string> need_list, int my = 0) {
    if(js.find("son") != js.end()) {
        for(auto son : js["son"]) {
            if(needoutput(son, need_list)) {
                if(son["son"].size() == 0) {
                    if(son["type"] != theNext::threadSetting::identifier && son["type"] != theNext::threadSetting::decimal) {
                        continue;
                    }
                }
                cout << my;
                if(!my && !first) {
                    last++;
                    first = true;
                    cout << "[\"" << js["type"].get<string>() << "\"]";
                }
                cout << " --> " << last << "[\"" << son["type"].get<string>();
                if(son["content"].get<string>().size()) {
                    cout << "<br>" << son["content"].get<string>() << "\"]" << endl;
                    last++;
                } else {
                    cout << "\"]" << endl;
                    printTree(son, need_list, last++);
                }
            }
        }
    }
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