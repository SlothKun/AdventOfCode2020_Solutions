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
 
map<unsigned long long, unsigned long long> addresses;
string mask;
const int  BITMAX = 36;
unsigned long long final_sum = 0;

void create_new_subaddresses(vector<int>all_x_pos, string addr_tomodify, int decimalval) {
    int pos_to_modify = all_x_pos[0];
    all_x_pos.erase(all_x_pos.begin());
    for (int i = 0; i < 2; i++) {
        string temp_addr = addr_tomodify;
        cout << "temp_addr before : " << temp_addr << "\n";
        temp_addr.replace(pos_to_modify, 1, to_string(i));
        cout << "temp_addr aaaaaa : " << temp_addr << "\n";
        if (all_x_pos.size() == 0) {
            unsigned long long new_subaddr_dec = bitset<BITMAX>(temp_addr).to_ullong();
            cout << "new_subaddr_dec : " << new_subaddr_dec << "\n";
            addresses[new_subaddr_dec] = decimalval;
        } else {
            create_new_subaddresses(all_x_pos, temp_addr, decimalval);
        }
    }
}


string apply_addr_mask(string binary, string current_mask) {
    string new_bin = "";
    int nb_x = 0;
    for (int i = 0; i < binary.size(); i++) {
        if (current_mask[i] == '0') {
            new_bin += binary[i];
        } else {
            new_bin +=  current_mask[i];
        }
    }
    cout << "new addr : " << new_bin << "\n";
    return new_bin;
}


pair<unsigned long long, vector<int>> apply_value_mask(string binary, string current_mask) {
    string new_bin = "";
    vector<int> nb_x;
    for (int i = 0; i < binary.size(); i++) {
        if (current_mask[i] == 'X') {
            new_bin += binary[i];
            nb_x.push_back(i);
        } else if (current_mask[i] == '0') {
            new_bin += '0';
        } else {
            new_bin += '1';
        }
    }
    cout << "new bin value : " << new_bin << "\n";
    cout << "new dec value : " << bitset<BITMAX>(new_bin).to_ullong() << "\n";
    return pair<unsigned long long, vector<int>>(bitset<BITMAX>(new_bin).to_ullong(), nb_x);
}

void make_sum() {
    for (auto addr_value : addresses) {
        cout << addr_value.first << " : " << addr_value.second << "\n";
        final_sum += addr_value.second;
    }
}

int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;

    while (getline(my_file, line)) {
        if (line.find("mask") != string::npos) {
            mask = line.substr(line.find("=") + 2);
            cout << "mask : " << mask << "\n";
        } else {
            int address = stoi(line.substr(line.find("[") + 1, line.find("]")));
            cout << "Address base : " << address << "\n";
            int dec_value = stoi(line.substr(line.find("=") + 2));
            string bin_value = bitset<BITMAX>(dec_value).to_string();
            string bin_addr = bitset<BITMAX>(address).to_string();
            cout << "bin value : " << bin_value << "\n";
            cout << "bin_addr : " << bin_addr << "\n";

            vector<int> nb_x;
            for (int i = 0; i < mask.size(); i++) {
                if (mask[i] == 'X') {
                    nb_x.push_back(i);
                }
            }
            string new_bin_addr = apply_addr_mask(bin_addr, mask);
            create_new_subaddresses(nb_x, new_bin_addr, dec_value);
        }
    }

    make_sum();
    cout << "final result : " << final_sum;
}