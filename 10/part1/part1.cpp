#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 
int joltage_rating = 0;
list<int> adapter;
int diff_of_1 = 0;
int diff_of_3 = 1;




int main() {
    fstream my_file;
    my_file.open("../input/test1.txt", ios::in);
    string line;
    // Get all instructions & value & put them in a dict
    while (getline(my_file, line)) {
        adapter.push_back(stoi(line));
    }

    adapter.sort();
    while (adapter.size() != 0) {
        cout << joltage_rating << " to " << adapter.front() << '\n';
        if ((adapter.front() - joltage_rating) == 1) {
            diff_of_1++;
        } else if ((adapter.front() - joltage_rating) == 3) {
            diff_of_3++;
        }
        joltage_rating = adapter.front();
        adapter.pop_front();
    }

    cout << "\nresult : " << diff_of_3 * diff_of_1 << '\n';
}