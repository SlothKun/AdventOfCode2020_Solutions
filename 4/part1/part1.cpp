#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

int passport_count = 0;
int main() {
    fstream my_file;
    my_file.open("input/input_aoc_day4.txt", ios::in);
    string line;
    
    vector <string> passport;
    
    int valid_password = 0;
    bool cid_missing = true;
    const string delimiter = ":";


    while (1) {
        getline(my_file, line);
        cout << line << '\n';
        if (my_file.eof()) {
            break;
        }
        else if (line.length() == 0) {
            passport_count += 1;
            cout << "passport : " << passport.size() << "\n";
            if (passport.size() == 8) {
                cout << "valid\n\n";
                valid_password += 1;
            }
            else if (passport.size() == 7 && cid_missing) {
                cout << "valid\n\n";
                valid_password += 1;
            }
            passport.clear();
            cid_missing = true;
        }
        else {
            while (1) {
                int pos = line.find(delimiter);
                //cout << pos << '\n';
                if (pos == string::npos) {
                    break;
                }
                string field = line.substr(0, pos);
                cout << "field : " << field << "\n";

                if (field.compare("cid") == 0) {
                    cid_missing = false;
                }
                

                passport.push_back(field);
                //cout << line.find(' ') << '\n';
                line.erase(0, pos+1);
                line.erase(0, line.find(' ')+1);
                cout << "after erase : " << line << "\n";
            }
        }
    }
    cout << valid_password << '\n';
    cout << passport_count;
    
}