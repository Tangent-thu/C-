# C-
收录2023年暑期上C++程设课时所写的大作业wordle，仅存档
该代码在Visual Studios 2022上所写，sln后缀为项目，在Visual Studio里打开直接打开此项目所有文档。
如果使用其他编译器，只需下载源1.cpp，ACC.txt和FINAL.txt即可。
第一行输入一个整数T，表示本数据属于第几个任务。（
1
≤
T
≤
4
）

每个任务的具体要求和输入格式为：

【task 1】支持从标准输入指定一个词开始一局游戏（共 6 次猜测）。候选词与可用词内嵌在程序中（分别对应于下发文件中的 FINAL.txt 和 ACC.txt，代码模版中的WordSet类提供了一些成员函数方便你编程），从标准输入读取用户的猜测：

在每次猜测（获得可用词列表中的输入）后打印猜测结果和以及所有字母的状态：

程序运行后，不进行任何输出。每次猜测后，如果输入符合要求，则打印一行，形如 SSSSS AAAAAAAAAAAAAAAAAAAAAAAAAA ，前面五个字母是用户的猜测结果，后面 26 个字母是所有字母的状态（类似 Wordle 游戏中的输入键盘）。S 和 A 允许的取值包括 R（Red，数量过多的字母）、Y（Yellow，位置不正确的字母）、G （Green，正确的字母）、X（Unknown，未知状态的字母），语义与作业简介中描述的一致。如答案为 CRANE，猜测 ABUSE 的结果是 YRRRG，猜测 WANNA 的结果是 RYRGR。如果读入的一行不符合要求，则打印 INVALID。在打印所有字母状态时，如果某个字母在猜测中有多个不同的状态，则选择最「好」的一种，即优先级为 G>Y>R>X。
在游戏结束（用完六次机会或者猜对）后打印猜测次数（包括猜对的最后一次），如果失败，则还需打印正确答案

打印 CORRECT n（其中 n 为猜测次数）/ FAILED ZZZZZ（其中 ZZZZZ 为答案）
游戏结束后正常退出程序
样例输入一

1  
disco  
basis  
disco  
样例输出一

RRGYR RRXXXXXXYXXXXXXXXXGXXXXXXX  
GGGGG RRGGXXXXGXXXXXGXXXGXXXXXXX  
CORRECT 2  
样例输入二

1  
gamma  
exome  
galax  
exams  
dummy  
gammy  
gamme  
样例输出二

RRRGR XXXXRXXXXXXXGXRXXXXXXXXRXX  
GGRYR GXXXRXGXXXXRGXRXXXXXXXXRXX  
RRYGR GXXXRXGXXXXRGXRXXXRXXXXRXX  
RRGGR GXXRRXGXXXXRGXRXXXRXRXXRRX  
GGGGR GXXRRXGXXXXRGXRXXXRXRXXRRX  
GGGGR GXXRRXGXXXXRGXRXXXRXRXXRRX  
FAILED GAMMA  
样例输入三

1  
again  
Why do I have to this kind of things? Damn it!  
kaama  
abcde  
again  

样例输出三 

INVALID  
RYGRR GXXXXXXXXXRXRXXXXXXXXXXXXX  
INVALID  
GGGGG GXXXXXGXGXRXRGXXXXXXXXXXXX  
CORRECT 2  
【task 2】增加对运行多局游戏的支持。每次按照 task 1的格式输入完成一局游戏后，单独输入一行字符串，保证其为Y或者N。如果为Y，则进入下一局游戏；否则正常退出程序。

样例输入四 

2  
disco  
basis  
disco  
Y  
gamma  
exome  
galax  
exams  
dummy  
gammy  
gamme  
N  
样例输出四  

RRGYR RRXXXXXXYXXXXXXXXXGXXXXXXX  
GGGGG RRGGXXXXGXXXXXGXXXGXXXXXXX  
CORRECT 2  
RRRGR XXXXRXXXXXXXGXRXXXXXXXXRXX  
GGRYR GXXXRXGXXXXRGXRXXXXXXXXRXX  
RRYGR GXXXRXGXXXXRGXRXXXRXXXXRXX  
RRGGR GXXRRXGXXXXRGXRXXXRXRXXRRX  
GGGGR GXXRRXGXXXXRGXRXXXRXRXXRRX  
GGGGR GXXRRXGXXXXRGXRXXXRXRXXRRX  
FAILED GAMMA  
【task 3】启动困难模式。在此模式下，新的猜测中所有位置正确（绿色，即 G）的字母不能改变位置，也必须用到所有存在但位置不正确（黄色，即Y ）的字母，但是允许在新的猜测中重复使用数量过多（红色，即R）的字母，也允许存在但位置不正确（黄色，即Y ）的字母再次出现在相同的错误位置。如果读入的猜测不符合困难模式要求，则打印INVALID，并且此次不计入猜测次数。

样例输入五  
3  
gamma  
dummy  
happy  
gamme  
gamma  
Y  
world  
audio  
crane  
board  
roast  
world  
N  
样例输出五  

RRGGR XXXRXXXXXXXXGXXXXXXXRXXXRX  
INVALID  
GGGGR GXXRRXGXXXXXGXXXXXXXRXXXRX  
GGGGG GXXRRXGXXXXXGXXXXXXXRXXXRX  
CORRECT 3  
RRYRY RXXYXXXXRXXXXXYXXXXXRXXXXX  
INVALID  
RGRYG RRXGXXXXRXXXXXGXXYXXRXXXXX  
INVALID  
GGGGG RRXGXXXXRXXGXXGXXGXXRXGXXX  
CORRECT 3  
【task 4】增加统计信息。统计并输出截至目前的游戏成功率（成功局数 / 已玩局数）、平均尝试次数（仅计算成功的游戏，如果没有成功的游戏则为 0）。

每局结束后，额外进行以下操作：

打印一行 X Y Z，分别为成功局数、失败局数（均为整数）和成功游戏的平均尝试次数（浮点数，截断到小数点后两位）
样例输入六

4  
disco  
disco  
Y  
gamma  
dummy  
happy  
gamme  
gamma  
Y  
gamma  
gamme  
gamme  
gamme  
gamme  
gamme  
gamme  
N  
样例输出六

GGGGG XXGGXXXXGXXXXXGXXXGXXXXXXX  
CORRECT 1  
1 0 1.00  
RRGGR XXXRXXXXXXXXGXXXXXXXRXXXRX  
INVALID  
GGGGR GXXRRXGXXXXXGXXXXXXXRXXXRX  
GGGGG GXXRRXGXXXXXGXXXXXXXRXXXRX  
CORRECT 3  
2 0 2.00  
GGGGR GXXXRXGXXXXXGXXXXXXXXXXXXX  
GGGGR GXXXRXGXXXXXGXXXXXXXXXXXXX  
GGGGR GXXXRXGXXXXXGXXXXXXXXXXXXX  
GGGGR GXXXRXGXXXXXGXXXXXXXXXXXXX  
GGGGR GXXXRXGXXXXXGXXXXXXXXXXXXX  
GGGGR GXXXRXGXXXXXGXXXXXXXXXXXXX  
FAILED GAMMA  
2 1 2.00  
