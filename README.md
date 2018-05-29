# myCompilingPrincipleExperiment

编译原理课程实验内容

## 编译环境

> g++ --version
> g++.exe (x86_64-posix-seh-rev2, Built by MinGW-W64 project) 7.1.0
> Copyright (C) 2017 Free Software Foundation, Inc.
>
> cmake --version
> cmake version 3.8.2
>
> clang++ --version
> clang version 6.0.0 (https://github.com/llvm-mirror/clang.git 4e8386f480e758e0e5e9c26c7439ac7bf9a71d23) (https://github.com/llvm-mirror/llvm.git 6727c50d80dcdfe8631f5806fd8148b2334fdcb7)

## 文件结构

- include 

  放置词法分析程序的实现和语言声明

  - struct

    放置通用数据结构用于编译器各个组件之间的交互

    - token.hpp

      词法分析程序的输出

  - threadLanguage

    测试语言的规则

    - threadSetting.hpp

      测试语言的表述

  - lexicalAnalysier.hpp

    词法分析程序实现

- src

  编译程序

  - test

    测试程序

    - functionalTestForLexicalAnalysier.cpp

      测试词法分析程序正确性的程序

- third

  使用的第三方非标准库

  - [json](https://github.com/nlohmann/json)

    std风格的c++json库