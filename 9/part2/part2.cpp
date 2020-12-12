#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 
unsigned long long int badnb = 10884537;
//unsigned long long int badnb = 127;
list<unsigned long long int> contiguous_numbers;
vector<unsigned long long int> all_nb;

int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;

    // Get all instructions & value & put them in a dict
    while (getline(my_file, line)) {
        //cout << "line : " << line << '\n';
        size_t sz = 0;
        all_nb.push_back(stoull(line, &sz, 0));
    }

    for (int first = 0; first < all_nb.size(); first++) {
        int sum = all_nb[first];
        contiguous_numbers.push_back(all_nb[first]);
        for (int second = first+1; second < all_nb.size(); second++) {
            contiguous_numbers.push_back(all_nb[second]);
            sum += all_nb[second];
            if (sum == badnb) {
                contiguous_numbers.sort();
                for (auto cnb : contiguous_numbers) {
                    cout << cnb << '\n';
                }
                cout << "Weakness : " << (contiguous_numbers.front() + contiguous_numbers.back());
                exit(0);
            }
        }
        contiguous_numbers.clear();
    }
}