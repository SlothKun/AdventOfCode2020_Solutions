#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 
list<int> adapter;
 unsigned long long int nb_arrangements = 0;

void arrangement_counter(int current_nb) {
    if (current_nb == adapter.back()) {
        nb_arrangements += 1;
    } else {
        list<int> nb_within_range;
        for (auto i : adapter) {
            if (current_nb+3 < i) {
                break;
            } else {     
                if (current_nb+1 == i || current_nb+2 == i || current_nb+3 == i) {
                    nb_within_range.push_front(i);
                }
            }
        }
        //cout << "len : " << nb_within_range.size() << "\n";

        for (auto y : nb_within_range) {
            
            arrangement_counter(y);
        }
        //cout << "nb arrangement : " << nb_arrangements << "\n";
        //return nb_arrangements;
    }
}


int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    // Get all instructions & value & put them in a dict
    while (getline(my_file, line)) {
        adapter.push_back(stoi(line));
    }

    adapter.sort();
    arrangement_counter(0);
    cout << "result : " << nb_arrangements;
    //cout << "\nresult : " << diff_of_3 * diff_of_1 << '\n';
}