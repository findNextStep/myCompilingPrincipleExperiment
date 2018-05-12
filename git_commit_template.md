# git commit内容约束
为了`git log`的可读性，约定以下模板

> [********]具体描述

具体实现如下

- [cpp ****] 描述对于源代码的操作

    - [cpp base] 描述在include内对基本类型的修改和创建

        - [cpp lexi] 描述对于词法分析部分的修改

    - [cpp test] 描述建立新的测试用例

- [makefile] 描述对`CMakeLists.txt`的修改

- [git ****] 描述对于整体工程的变动

    - [git init] 描述开始一个新的项目
