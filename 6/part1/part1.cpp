#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    fstream my_file;
    my_file.open("input/input.txt", ios::in);
    string line;
    
    int sum = 0;
    string question_answered = "";




    while (1) {
        getline(my_file, line);
        if (my_file.eof()) {
            break;
        } else {
            if (line.length() == 0) {
                sum += question_answered.length();
                question_answered = "";
            } else {
                for (auto const it : line) {
                //cout << "letter : " << it << '\n';
                //cout << "answered ? : " << question_answered.find(it) << '\n';
                if (question_answered.find(it) == string::npos) {
                    question_answered += it;
                }
            }
            cout << "question_answered : " << question_answered << '\n';
            }

        }
    }
    cout << "sum : " << sum;
    
}