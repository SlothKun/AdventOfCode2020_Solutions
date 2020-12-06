#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

int main() {
    fstream my_file;
    my_file.open("input/input.txt", ios::in);
    string line;
    
    int sum = 0;
    map<char, int> question_answered;

    int line_ingroup = 0;
    
    while (1) {
        getline(my_file, line);
        if (my_file.eof()) {
            break;
        } else {
            // End of the group
            if (line.length() == 0) {
                for (auto i : question_answered) {
                    if (i.second == line_ingroup) {
                        sum += 1;
                    }
                }
                question_answered.clear();
                line_ingroup = 0;
            } else {
                line_ingroup += 1;
                for (auto const it : line) {
                    /* check if letter is in the dict, if not, add it
                    if it's in, increase its counter by 1*/
                    if (question_answered.count(it) == 0) {
                        question_answered[it] = 1;
                    } else {
                        question_answered[it] += 1;
                    }
                }
            }
        }
    }
    cout << "sum : " << sum;
}