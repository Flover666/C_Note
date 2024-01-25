#ifndef 是"if not defined"的简写，是预处理功能（宏定义、文件包含、条件编译）当中的条件编译，可以根据是否已经定义了一个变量来进行分支选择，其作用是：

　　1、防止头文件的重复包含和编译；

　　2、便于程序的调试和移植；

　　下面分别举例描述。

一、防止头文件的重复包含和编译
下面是错误示范：

headfile_1.h

复制代码
 1 #include <iostream>
 2 class CTest_1 {
 3     CTest_1() {
 4         //do something,eg:init;
 5     }
 6     ~CTest_1() {
 7         //do something ,eg:free;
 8     }
 9     void PrintScreen()
10     {
11         std::cout << "this is Class CTest_1!" << std::endl;
12     }
13 };
复制代码
headfile_2.h

复制代码
 1 #include "headfile_1.h"
 2 class CTest_2 {
 3     CTest_2() {
 4         //do something,eg:init;
 5     }
 6     ~CTest_2() {
 7         //do something,eg:free;
 8     }
 9     void PrintScreen()
10     {
11         std::cout << "this is Class CTest_2!" << std::endl;
12     }
13 };
复制代码
sourcefile.cpp

复制代码
1 #include <iostream>
2 #include "headfile_1.h"
3 #include "headfile_2.h"
4 
5 int main()
6 {
7     return 0;
8 }
复制代码
编译时提示重定义错误：



 

　　以上显示headfile_1.h中的类CTest_1重定义了。

　　一般地，假如有一个C源文件（如sourcefile.cpp），它包含两个头文件（如headfile_1.h和headfile_2.h），而头文件headfile_2.h又包含了headfile_1.h，则最终的效果是该源文件包含了两次headfile_1.h。如果你在头文件里定义了结构体或者类类型，那么问题来了，编译时将会报重复定义的错误。

　　加上条件编译"ifndef"则问题可解决。在headfile_1.h中加上条件编译，如下：

headfile_1.h

复制代码
 1 #ifndef _HEADFILE_1_H
 2 #define _HEADFILE_1_H
 3 #include <iostream>
 4 class CTest_1 {
 5     CTest_1() {
 6         //do something,eg:init;
 7     }
 8     ~CTest_1() {
 9         //do something ,eg:free;
10     }
11     void PrintScreen()
12     {
13         std::cout << "this is Class CTest_1!" << std::endl;
14     }
15 };
16 
17 #endif    //end of _HEADFILE_1_H
复制代码
编译通过！

　　分析：当第一次包含headfile_1.h时，由于没有定义_HEADFILE_1_H，条件为真，这样就会执行#ifndef _HEADFILE_1_H和#endif之间的代码；当第二次包含headfile_1.h时，前面一次已经定义了_HEADFILE_1_H，条件为假，#ifndef _HEADFILE_1_H和#endif之间的代码也就不会再次被包含，这样就避免了重定义。

　　

　　小结：还是把头文件的内容都放在#ifndef和#endif中吧。不管你的头文件会不会被多个文件引用，你最好都加上这个。一般格式是这样的：

复制代码
#ifndef <标识>
#define <标识>

......

......

#endif
复制代码
　　<标识>在理论上来说是可以自由命名的，但每个头文件的这个“标识”都应该是唯一的。标识的明明规则一般是头文件名全大写，前面加下划线，并把文件名中的"."也变成下划线，如：stdio.h

复制代码
#ifndef _STDIO_H
#define _STDIO_H

......

......

#endif
复制代码
 

注意：#ifndef起到的效果是防止一个源文件多次包含同一个头文件，而不是防止两个源文件包含同一个头文件。事实上，防止同一头文件被两个不同的源文件包含这种要求本身就是不合理的，头文件存在的价值就是被不同的源文件包含。

　　

二、便于程序的调试和移植
　　在调试程序时，常常需要对程序中的内容进行选择性地编译，即可以根据一定的条件选择是否编译。

　　主要分以下几种：

1、

复制代码
#ifndef 标识符

程序段 1

#else

程序段 2

#endif
复制代码
它的作用是当“标识符”没有由#define定义过，则编译“程序段1”，否则编译“程序段2”。

2、

复制代码
#ifndef 标识符

#define 标识符

程序段 1

#else

程序段 2

#endif
复制代码
它的作用是当“标识符”没有由#define定义过，则编译“程序段1”，否则编译“程序段2”。

3、

复制代码
#if 表达式

程序段 1

#else

程序段 2

#endif
复制代码
它的作用是当“表达式”值为真时，编译“程序段1”，否则编译“程序段2”。

 

注：以上三种形式中#else不是强制的，可省略；当然，当#else后需要嵌套#if时，可以使用预处理命令#elif，它相当于#else#if。

小结：在程序中使用条件编译主要是为了方便程序的调试和移植。
