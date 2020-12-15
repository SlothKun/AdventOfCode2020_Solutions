#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <bitset>

using namespace std;
 
map<int, unsigned long long> addresses;
string mask;
const int  BITMAX = 36;
unsigned long long final_sum = 0;


unsigned long long apply_mask(string binary, string current_mask) {
    string new_bin = "";
    for (int i = 0; i < binary.size(); i++) {
        if (current_mask[i] == 'X') {
            new_bin += binary[i];
        } else if (current_mask[i] == '0') {
            new_bin += '0';
        } else {
            new_bin += '1';
        }
    }
    cout << "new : " << new_bin << "\n";
    return bitset<BITMAX>(new_bin).to_ullong();
}

int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;

    while (getline(my_file, line)) {
        if (line.find("mask") != string::npos) {
            mask = line.substr(line.find("=") + 2);
            cout << mask << "\n";
        } else {
            int address = stoi(line.substr(line.find("[") + 1, line.find("]")));
            cout << address << "\n";
            int dec_value = stoi(line.substr(line.find("=") + 2));
            string bin_value = bitset<BITMAX>(dec_value).to_string();
            cout << bin_value << "\n";
            //unsigned long new_dec = apply_mask(bin_value, mask);
            // cout << "decimal new : " << new_dec << "\n";
            addresses[address] = apply_mask(bin_value, mask);
        }
    }

    for (auto addr_value : addresses) {
        final_sum += addr_value.second;
    }

    cout << "final result : " << final_sum;
}