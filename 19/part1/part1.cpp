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
#include <regex>

using namespace std;

string ROOT_RULE = "0";

int matched = 0;
map<string, vector<vector<string>>> subrules;
map<string, string> letter_rules;
string regex_str = "^";
basic_regex<char> regexobj;

void parseRule(string rule);
void createRegex(string rulenb);
void combinaisonChecker(string message);


int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    bool new_phase = false;
    while (getline(my_file, line)) {
        if (line.size() == 0) {
            createRegex(ROOT_RULE);
            regex_str += "$";
            regexobj = regex_str;
            new_phase = true;
        } else if (!new_phase) {
            parseRule(line);
        } else if (new_phase) {
            combinaisonChecker(line);
        }
    }

    cout << "--- REGEX ---\n";
    cout << regex_str << '\n';

    
    cout << "--- Letter rule ---\n";
    for (auto rule : letter_rules) {
        cout << rule.first << " : " << rule.second << "\n";
    }

    cout << "--- subrule ---\n";
    for (auto rule : subrules) {
        cout << rule.first << " : { ";
        for (auto subrule : rule.second) {
            cout << "{ ";
            for (auto subsubrule : subrule) {
                cout << subsubrule << ", ";
            }
            cout << "}, ";
        }
        cout << "}\n";
    }

    cout << "final result : " << matched << "\n";
}

void combinaisonChecker(string message) {
    if (regex_match(message, regexobj)) {
        matched++;
    }
}




void createRegex(string rulenb) {
    /*
        Recursively build the regex with rules
    */
    bool check = false;
    regex_str += "(?:";
    for (auto rules : subrules[rulenb]) {
        //subrules[rulenb].size()
        regex_str += "(?:";
        for (auto sub_rule : rules) {
            cout << sub_rule << "\n";
            
            for (auto letter : letter_rules) {
                if (letter.first == sub_rule) {
                    regex_str += letter.second;
                    check = true;
                }
            }
            if (!check) {
                createRegex(sub_rule);
            }
            check = false;
            cout << regex_str << "\n";
        }
        if (regex_str.back() == '|') {
            regex_str.pop_back();
        }
        regex_str += ")|";
        
    }
    if (regex_str.back() == '|') {
        regex_str.pop_back();
    }
    regex_str += ")";
}

void parseRule(string rule) {
    string rulenb = rule.substr(0, rule.find(":"));
    rule.erase(0, rulenb.size()+2);
    vector<vector<string>> parser;
    vector<string> subparser;
    //cout << rule << "\n";
    if (rule.find('a') != string::npos) {
        int pos = rule.find('a');
        letter_rules[rulenb] = rule.substr(pos, pos);
        return;
    } else if (rule.find('b') != string::npos) {
        int pos = rule.find('b');
        letter_rules[rulenb] = rule.substr(pos, pos);
        return;
    } else {
        for (int next_pos = rule.find(' '); rule.find(' ') != string::npos; next_pos++) {
            string subrule = rule.substr(0, rule.find(' '));
            if (subrule.find('|') != string::npos) {
                parser.push_back(subparser);
                subparser.clear();
            } else {
                subparser.push_back(subrule);
            }
            rule.erase(0, rule.find(' ')+1);
            //cout << rule << "\n";
        }
        subparser.push_back(rule);
        parser.push_back(subparser);
        rule.erase(0, rule.size());
        //cout << "---  end ---" << "\n";
        subrules[rulenb] = parser;
    }
}