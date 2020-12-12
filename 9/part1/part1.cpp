#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 
int badnb = 10884537;
const int PREAMBLE = 25;
vector<int> preamble_nb;




int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    // Get all instructions & value & put them in a dict
    while (getline(my_file, line)) {
        bool bad = true;
        int nb = stoi(line);
        if (preamble_nb.size() != PREAMBLE) {
            preamble_nb.push_back(nb);
        } else {
            for (int first = 0; first < preamble_nb.size(); first++) {
                for (int second = first; second < preamble_nb.size(); second++) {
                    if ((preamble_nb[first] + preamble_nb[second]) == nb) {
                        bad = false;
                    }
                }
            }
            if (bad) {
                cout << "badnb : " << nb << '\n';
                break;
            }
            preamble_nb.erase(preamble_nb.begin());
            preamble_nb.push_back(nb);
        }
    }
}