#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include<random>
using namespace std;

class WordSet {
public:
    WordSet() {
        std::ifstream FINAL_FILE("./FINAL.txt");
        if (!FINAL_FILE.good()) {
            printf("[ERROR] FINAL.txt not found!\n");
            return;
        }
        while (!FINAL_FILE.eof()) {
            std::string str;
            FINAL_FILE >> str;
            final_set.insert(str);
        }

        std::ifstream ACCEPTABLE_FILE("./ACC.txt");
        if (!ACCEPTABLE_FILE.good()) {
            printf("[ERROR] ACC.txt not found!\n");
            return;
        }
        while (!ACCEPTABLE_FILE.eof()) {
            std::string str;
            ACCEPTABLE_FILE >> str;
            acceptable_set.insert(str);
        }

    }

    bool in_final_set(std::string word) {
        return final_set.find(word) != final_set.end();
    }

    bool in_acceptable_set(std::string word) {
        return acceptable_set.find(word) != acceptable_set.end();
    }
private:
    std::set<std::string> final_set;
    std::set<std::string> acceptable_set;
};

/* 该类的目的是完成困难模式要求，将上一次玩家所输入词和结果储存在该类的对象中
同时该类中还设立了一个成员函数numberY以计算词中每个字母所具有的Y结果数，并储存在长度为26的numY数组中*/
class start {
public:
    string ad, icenter;
    int numY[26];
    start(string guess, string result) {
        ad = guess;
        icenter = result;
        for (int i = 0; i < 26; i++) numY[i] = 0;
    }

    //调用下面成员函数，可以让该类的对象的numY数组成员变量在26个字母所相对应的位置储存字母所具有的Y结果数.
    void numberY() {
        for (int i = 0; i < 5; i++) {
            if (icenter[i] == 'Y') numY[ad[i] - 'a']++; //ad[i] -'a'的做法是将小写字母a-z与数字0-25对应上
        }
    }
};

//该函数主要判断玩家所输入的新词是否符合困难模式的要求，container负责接受start对象，newword则接受用户所输的新词，最后经过分析返回true或者false.
bool HardMode(start container, string newword) {
    bool hard = true;
    container.numberY();
    for (int i = 0; i < 5; i++) {
        if (container.icenter[i] == 'G' && newword[i] != container.ad[i]) hard = false;
        if (container.icenter[i] == 'Y') {
            int n = 0;
            for (int j = 0; j < 5; j++) {
                if (container.icenter[j] == 'G') continue;
                if (newword[j] == container.ad[i]) n++;
            }
            if (n < container.numY[container.ad[i] - 'a']) hard = false;
        }
    }
    return hard;
}

void WordleStart(string& theguess, string& thefinal, string& theresult, string& theresult2) {
    int repeat1[26], repeat[26];  //repeat和repeat1数组用于存储最终词和猜测词中字母重复的个数.
    char a = 'a';  //该变量的建立是为了规范代码风格.
    for (int i = 0; i < 26; i++) {
        repeat[i] = 1;
    }
    for (int i = 0; i < 5; i++) {
        if (repeat[thefinal[i] - a] != 1) continue; //该语句为了避免相同字母多次重复比较，例如again，error等词，当a、r等字母比较完后，后续再遇到时则直接跳过避免有重复比较.
        for (int j = 0; j < 5; j++) {
            if (i == j) continue;
            if (thefinal[i] == thefinal[j]) repeat[thefinal[i] - a]++;
        }
    }
    for (int i = 0; i < 26; i++) {
        repeat1[i] = 0;
    }

    //该循环是确定猜词中是否存在结果为G的字母，因为G优先级最高，故单写一一个循环以先找出所有的G.
    for (int i = 0; i < 5; i++) {
        if (theguess[i] == thefinal[i]) {
            theresult[i] = 'G';
            theresult2[theguess[i] - a] = 'G';
            repeat1[theguess[i] - a]++;
        }
    }

    //该循环用以寻找猜词中是否存在结果为Y的字母.
    for (int i = 0; i < 5; i++) {
        int notrepeat = 0;
        for (int j = 0; j < 5; j++) {
            if (j == i) continue;
            if (theguess[i] == thefinal[j] && theresult[i] != 'G' && repeat1[theguess[i] - a] < repeat[theguess[i] - a] && notrepeat == 0) {
                theresult[i] = 'Y';
                repeat1[theguess[i] - a]++;
                notrepeat++;  //该变量用于防止repeat1数组里的数字被错误地重复增加，保证repeat1相对应的位置数字能正确地与repeat比较
                if (theresult2[theguess[i] - a] != 'G') theresult2[theguess[i] - a] = 'Y';
            }


        }
        if (theresult[i] == 'R' && theresult2[theguess[i] - a] == 'X') {
            theresult2[theguess[i] - a] = 'R';
        }

    }
}
int main() {
    int task;
    while (cin >> task) {
        if (task >= 1 && task <= 4) break;
    }
    WordSet wordle;
    string theguess, thefinal, theresult, theresult2, niu, option;
    int num, repeat[26], repeat1[26];  //定义num以用来计算一局游戏的尝试次数
    int thewin, thefail, round, thetry;  //定义变量，用于记录成功局数，失败局数和总尝试次数
    float theaveragetry; //同理，定义变量记录平均尝试次数
    thewin = thefail = thetry = 0;
    round = 1;
    option = "Y";
    while (option == "Y") {
        num = 0;
        theresult2 = "XXXXXXXXXXXXXXXXXXXXXXXXXX";  //每次重新开始一轮游戏时对theresult2变量重新初始化
        theresult = "RRRRR";
        theguess = "RRRRR";  //先对theguess赋值，以防止空字符串进入到函数中出现报错

        //该循环用于输入最终结果词，若输入词在候选词库内则跳出循环.
        while (cin >> thefinal) {
            if (wordle.in_final_set(thefinal)) break;
        }
        getline(cin, niu);  //前面用cin输入时没有读入\n，所以在用户输词前再用一个getline函数让\n移开.


        while (num < 6) {
            string thehardguess = theguess;  //定义一个thehardguess新变量储存上一次theguess的值，以便用户输入新词到变量theguess中后便于与上次theguess作比较
            start hardmode(thehardguess, theresult);  //定义一个strat类的对象，储存上次猜测的词与结果
            getline(cin, theguess);
            if (wordle.in_acceptable_set(theguess)) {
                if (task > 2) {
                    if (!HardMode(hardmode, theguess)) {
                        cout << "INVALID" << endl;
                        theguess = thehardguess;  //该行用于新输入的词不满足要求之后，将theguess的值重新变成上一次的猜测词，防止不满足要求的新词被当成比较词影响函数判断
                        continue;
                    }
                }
                theresult = "RRRRR";  //每次猜测后的返回结果1都要重新重置.

                WordleStart(theguess, thefinal, theresult, theresult2);  //运行wordle游戏核心函数

                num++;  //该变量只在theguess在可用词库中的条件下才会增加，以满足出现非可用词时不增加游戏次数的要求
                cout << theresult << ' ' << theresult2 << endl;
                if (theguess == thefinal) break;
            }
            else {
                theguess = thehardguess; //同上
                cout << "INVALID" << endl;
            }

        };
        if (theguess == thefinal) {
            cout << "CORRECT" << " " << num << endl;
            thewin++;
            round++;
            thetry += num;
            theaveragetry = (float)thetry / (round - 1);
        }
        else {
            string fail;
            for (int i = 0; i < 5; i++) fail.push_back(thefinal[i] - 32);  //该行用于满足打印出正确答案时将小写字母转换成大写字母的要求
            cout << "FAILED" << ' ' << fail << endl;
            thefail++;
        }
        if (task == 4) {
            cout << thewin << ' ' << thefail << ' ';

            // 下面两行代码用于保证输出结果截到小数点后两位
            cout.setf(std::ios::fixed);
            cout.precision(2);
            cout << theaveragetry << endl;
        }
        if (task > 1) {
            while (cin >> option) {
                if (option == "Y" || option == "N") break;
            }
        }
        else break;
    }

    return 0;
}