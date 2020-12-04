#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

using namespace std;

bool value_verif(map<string, string> input) {
    int year;
    string eye_color = "amb blu brn gry grn hzl oth";
    string allowed_char = "abcdef0123456789";
    for (auto const& it : input) {
        if (it.first.compare("byr") == 0) {
            year = stoi(it.second);
            if (year < 1920 || year > 2002) {
                cout << "byr\n";
                return false;
            }
        } else if (it.first.compare("iyr") == 0) {
            year = stoi(it.second);
            if (year < 2010 || year > 2020) {
                cout << "iyr\n";
                return false;
            }
        } else if (it.first.compare("eyr") == 0) {
            year = stoi(it.second);
            if (year < 2020 || year > 2030) {
                cout << "eyr\n";
                return false;
            }
        } else if (it.first.compare("hgt") == 0) {
            int height_pos = it.second.find("cm");
            int h_measure = stoi(it.second.substr(0, height_pos));
            if (height_pos != string::npos && (h_measure < 150 || h_measure > 193)) {
                cout << "hgt1\n";
                return false;
            } else if (height_pos == string::npos) {
                int height_pos = it.second.find("in");
                if (height_pos == string::npos) {
                    cout << "hgt2\n";
                    return false;
                }
                else if (height_pos != string::npos && (h_measure < 59 || h_measure > 76)) {
                    cout << "hgt3\n";
                    return false;
                }
            }
        } else if (it.first.compare("hcl") == 0) {
            if (it.second.length() != 7) {
                cout << "hcl\n";
                return false;
            } else if (it.second[0] != '#') {
                cout << "hcl\n";
                return false;
            } else {
                for (char const c: it.second.substr(1)) {
                    if (allowed_char.find(c) == string::npos) {
                        cout << "hcl\n";
                        return false;
                    }
                }
            }
        } else if (it.first.compare("ecl") == 0) {
            if (eye_color.find(it.second) == string::npos) {
                cout << "ecl\n";
                return false;
            }
        } else if (it.first.compare("pid") == 0) {
            if (it.second.length() != 9) {
                cout << "pid\n";
                return false;
            }
        }
    }
    return true;
}


int main() {
    fstream my_file;
    my_file.open("input/input.txt", ios::in);
    string line;
    
    //vector <string> passport;
    map<string, string> passport;
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
            cout << "passport : " << passport.size() << "\n";
            if (passport.size() == 8) {
                if (value_verif(passport)) {
                    cout << "valid\n\n";
                    valid_password += 1;
                }
                
            }
            else if (passport.size() == 7 && cid_missing) {
                if (value_verif(passport)) {
                    cout << "valid\n\n";
                    valid_password += 1;
                }
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

                if (field.compare("cid") == 0) {
                    cid_missing = false;
                }
                line.erase(0, pos+1);
                pos = line.find(' ');
                string value = line.substr(0, pos);
                cout << "field : " << field << " / ";
                cout << "value : " << value << "\n";
                

                passport.insert(pair<string, string>(field, value));
                //cout << line.find(' ') << '\n';
                
                line.erase(0, pos+1);
                //cout << "after erase : " << line << "\n";
            }
        }
    }
    cout << valid_password;
}