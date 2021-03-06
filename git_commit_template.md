# git commit内容约束
为了`git log`的可读性，约定以下模板

> [********]具体描述

具体实现如下

- [cpp ****] 描述对于源代码的操作

    - [cpp base] 描述在include内对基本类型的修改和创建

        - [cpp lexi] 描述对于词法分析部分的修改

        - [cpp gram] 描述对于语法分析部分的修改

        - [cpp toke] 描述对`token`相关的修改

    - [cpp test] 描述建立新的测试用例

        - [cpp tlex] 针对词法分析程序的测试用例

        - [cpp tgra] 针对语法分析程序的测试用例

    - [cpp tool] 描述各种工具函数/工具类的修改
    
    - [cpp lthr] 描述对于语言thread限制的修改

- [makefile] 描述对`CMakeLists.txt`的修改

- [git ****] 描述对于整体工程的变动

    - [git init] 描述开始一个新的项目

- [ vscode ] 描述vscode配置变化

- [ readme ] 描述说明文件readme的变化

- [mod ****] 描述submod的配置

    - [mod json] 描述json模组的配置