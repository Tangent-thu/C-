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

/* �����Ŀ�����������ģʽҪ�󣬽���һ�����������ʺͽ�������ڸ���Ķ�����
ͬʱ�����л�������һ����Ա����numberY�Լ������ÿ����ĸ�����е�Y��������������ڳ���Ϊ26��numY������*/
class start {
public:
    string ad, icenter;
    int numY[26];
    start(string guess, string result) {
        ad = guess;
        icenter = result;
        for (int i = 0; i < 26; i++) numY[i] = 0;
    }

    //���������Ա�����������ø���Ķ����numY�����Ա������26����ĸ�����Ӧ��λ�ô�����ĸ�����е�Y�����.
    void numberY() {
        for (int i = 0; i < 5; i++) {
            if (icenter[i] == 'Y') numY[ad[i] - 'a']++; //ad[i] -'a'�������ǽ�Сд��ĸa-z������0-25��Ӧ��
        }
    }
};

//�ú�����Ҫ�ж������������´��Ƿ��������ģʽ��Ҫ��container�������start����newword������û�������´ʣ���󾭹���������true����false.
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
    int repeat1[26], repeat[26];  //repeat��repeat1�������ڴ洢���մʺͲ²������ĸ�ظ��ĸ���.
    char a = 'a';  //�ñ����Ľ�����Ϊ�˹淶������.
    for (int i = 0; i < 26; i++) {
        repeat[i] = 1;
    }
    for (int i = 0; i < 5; i++) {
        if (repeat[thefinal[i] - a] != 1) continue; //�����Ϊ�˱�����ͬ��ĸ����ظ��Ƚϣ�����again��error�ȴʣ���a��r����ĸ�Ƚ���󣬺���������ʱ��ֱ�������������ظ��Ƚ�.
        for (int j = 0; j < 5; j++) {
            if (i == j) continue;
            if (thefinal[i] == thefinal[j]) repeat[thefinal[i] - a]++;
        }
    }
    for (int i = 0; i < 26; i++) {
        repeat1[i] = 0;
    }

    //��ѭ����ȷ���´����Ƿ���ڽ��ΪG����ĸ����ΪG���ȼ���ߣ��ʵ�дһһ��ѭ�������ҳ����е�G.
    for (int i = 0; i < 5; i++) {
        if (theguess[i] == thefinal[i]) {
            theresult[i] = 'G';
            theresult2[theguess[i] - a] = 'G';
            repeat1[theguess[i] - a]++;
        }
    }

    //��ѭ������Ѱ�Ҳ´����Ƿ���ڽ��ΪY����ĸ.
    for (int i = 0; i < 5; i++) {
        int notrepeat = 0;
        for (int j = 0; j < 5; j++) {
            if (j == i) continue;
            if (theguess[i] == thefinal[j] && theresult[i] != 'G' && repeat1[theguess[i] - a] < repeat[theguess[i] - a] && notrepeat == 0) {
                theresult[i] = 'Y';
                repeat1[theguess[i] - a]++;
                notrepeat++;  //�ñ������ڷ�ֹrepeat1����������ֱ�������ظ����ӣ���֤repeat1���Ӧ��λ����������ȷ����repeat�Ƚ�
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
    int num, repeat[26], repeat1[26];  //����num����������һ����Ϸ�ĳ��Դ���
    int thewin, thefail, round, thetry;  //������������ڼ�¼�ɹ�������ʧ�ܾ������ܳ��Դ���
    float theaveragetry; //ͬ�����������¼ƽ�����Դ���
    thewin = thefail = thetry = 0;
    round = 1;
    option = "Y";
    while (option == "Y") {
        num = 0;
        theresult2 = "XXXXXXXXXXXXXXXXXXXXXXXXXX";  //ÿ�����¿�ʼһ����Ϸʱ��theresult2�������³�ʼ��
        theresult = "RRRRR";
        theguess = "RRRRR";  //�ȶ�theguess��ֵ���Է�ֹ���ַ������뵽�����г��ֱ���

        //��ѭ�������������ս���ʣ���������ں�ѡ�ʿ���������ѭ��.
        while (cin >> thefinal) {
            if (wordle.in_final_set(thefinal)) break;
        }
        getline(cin, niu);  //ǰ����cin����ʱû�ж���\n���������û����ǰ����һ��getline������\n�ƿ�.


        while (num < 6) {
            string thehardguess = theguess;  //����һ��thehardguess�±���������һ��theguess��ֵ���Ա��û������´ʵ�����theguess�к�������ϴ�theguess���Ƚ�
            start hardmode(thehardguess, theresult);  //����һ��strat��Ķ��󣬴����ϴβ²�Ĵ�����
            getline(cin, theguess);
            if (wordle.in_acceptable_set(theguess)) {
                if (task > 2) {
                    if (!HardMode(hardmode, theguess)) {
                        cout << "INVALID" << endl;
                        theguess = thehardguess;  //��������������Ĵʲ�����Ҫ��֮�󣬽�theguess��ֵ���±����һ�εĲ²�ʣ���ֹ������Ҫ����´ʱ����ɱȽϴ�Ӱ�캯���ж�
                        continue;
                    }
                }
                theresult = "RRRRR";  //ÿ�β²��ķ��ؽ��1��Ҫ��������.

                WordleStart(theguess, thefinal, theresult, theresult2);  //����wordle��Ϸ���ĺ���

                num++;  //�ñ���ֻ��theguess�ڿ��ôʿ��е������²Ż����ӣ���������ַǿ��ô�ʱ��������Ϸ������Ҫ��
                cout << theresult << ' ' << theresult2 << endl;
                if (theguess == thefinal) break;
            }
            else {
                theguess = thehardguess; //ͬ��
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
            for (int i = 0; i < 5; i++) fail.push_back(thefinal[i] - 32);  //�������������ӡ����ȷ��ʱ��Сд��ĸת���ɴ�д��ĸ��Ҫ��
            cout << "FAILED" << ' ' << fail << endl;
            thefail++;
        }
        if (task == 4) {
            cout << thewin << ' ' << thefail << ' ';

            // �������д������ڱ�֤�������ص�С�������λ
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