#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 
int sum = 0;

map<string, int> deadend;
map<string, map<string, int>> all_bag;
map<string, int> subbag;


string all_digit = "123456789";
string modified_line;
int temp_digit;

// Calculate the number of bags there's is in a given bag recursively
int find_path(string selected_bag, int value) {
    cout << "bag selected : " << selected_bag << '\n';
    if (deadend.find(selected_bag) != deadend.end()) {
        return value * deadend[selected_bag];
    } else {
        int mini_sum = 0;
        for (auto sbag  : all_bag[selected_bag]) {  
            mini_sum += find_path(sbag.first, sbag.second);
        }
        return mini_sum * value + value;
    }
}



int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;

    /* 
        Find the deadend bag (bags that contains nothing)
        and put the rest in a dict of dict that follow this rule :
        {mainbag_name : {subbag1 : nbofsubbag, subbag2 : nbofsubbag}, ...}
    */
    while (getline(my_file, line)) {
        if (line.find("contain no other bags") != string::npos) {
            cout << "NOPATH : " << line.substr(0, line.find(" bags")) << '\n';
            deadend.insert(pair<string, int>(line.substr(0, line.find(" bags")), 1));
        } else {
            string key = line.substr(0, line.find(" bags"));
            cout << "BAG INSERT : " << "key : " << key << " | values : ";

            modified_line = line.substr(line.find("contain") + 8);
            while (modified_line.find(" bag") != string::npos) {
                string temp_str = modified_line.substr(0, modified_line.find(" bag"));
                temp_digit = 0;

                for (int i = 0; i < temp_str.length(); i++) {
                    if (all_digit.find(temp_str[i]) != string::npos) {
                        temp_digit = temp_str[i] - 48;
                        temp_str = temp_str.substr(i + 2);
                        break;
                    }
                }
                subbag.insert(pair<string, int>(temp_str, temp_digit));
                cout << temp_digit << " " <<temp_str << ", ";
                modified_line = modified_line.substr(modified_line.find("bag")+1);
            }
            all_bag.insert(pair<string, map<string, int>>(key, subbag));
            cout << "\n";
            subbag.clear();
        }
    }

    
    // Compute the number of individual bags there's in a shiny gold bag
    for (auto sub_bag : all_bag["shiny gold"]) {
        cout << sub_bag.first << '\n';
        cout << sub_bag.second << '\n';
        sum += find_path(sub_bag.first, sub_bag.second);
    }

    cout << "sum : " << sum << '\n';

}