#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 
int sum = -1;

map<string, bool> direct_path;
map<string, vector<string>> all_bag;
vector<string> subbag;
string all_digit = "123456789";
string modified_line;

// check if the bag is already known, if not, check the bags in the bag recursively
bool find_path(string selected_bag) {
        if (direct_path.find(selected_bag) != direct_path.end()) {
            return direct_path[selected_bag];
        } else {
            bool pos_value = false;
            for (int i = 0; i < all_bag[selected_bag].size(); i++) {
                bool value = find_path(all_bag[selected_bag][i]);
                if (value) {
                    pos_value = true;
                }
                direct_path[all_bag[selected_bag][i]] = value;

            }
            return pos_value;
        }
}


int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;

    /* Iterate over each rule (line)
        Detect immediate path to shiny gold (bag where shiny gold is mentionned)
        Detect no_path (bag that lead to nothing)
        And for the other, put them in a dict where the key is the name of the bag and value are subbags
        (it'll make our life easir later on)
    */
    while (getline(my_file, line)) {
        if (line.find("shiny gold") != string::npos) {
            if (line.find("shiny gold") != 0) {
                cout << "sgp : " << line.substr(0, line.find(" bags")) << '\n';
                direct_path.insert(pair<string, bool>(line.substr(0, line.find(" bags")), true));
            } else {
                cout << "sgp : " << line.substr(0, line.find(" bags")) << '\n';
                direct_path.insert(pair<string, bool>(line.substr(0, line.find(" bags")), true));
            }
        } else if (line.find("contain no other bags") != string::npos) {
            cout << "nopath : " << line.substr(0, line.find(" bags")) << '\n';
            direct_path.insert(pair<string, bool>(line.substr(0, line.find(" bags")), false));
        } else {
            string key = line.substr(0, line.find(" bags"));
            cout << "BAG INSERT : " << "key : " << key << " | values : ";

            modified_line = line.substr(line.find("contain") + 8);
            while (modified_line.find(" bag") != string::npos) {
                string temp_str = modified_line.substr(0, modified_line.find(" bag"));

                for (int i = 0; i < temp_str.length(); i++) {
                    if (all_digit.find(temp_str[i]) != string::npos) {
                        temp_str = temp_str.substr(i + 2);
                        break;
                    }
                }
                subbag.push_back(temp_str);
                cout << temp_str << ", ";
                modified_line = modified_line.substr(modified_line.find("bag")+1);
            }
            all_bag.insert(pair<string, vector<string>>(key, subbag));
            cout << "\n";
            subbag.clear();
        }
    }

    // Decide if a bag is good or not
    for (auto main_bag : all_bag) {
        bool return_value = false;
        for (int i = 0; i < main_bag.second.size(); i++) {
            if (find_path(main_bag.second[i])) {
                return_value = true;
            }
        }
        direct_path[main_bag.first] = return_value;
    }

    // Count every good bag
    for (auto key : direct_path) {
        if (key.second) {
            sum += 1;
        }
        
    }
    cout << "sum : " << sum << '\n';
}