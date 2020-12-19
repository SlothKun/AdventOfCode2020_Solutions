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


int ticket_error_rate = 0;
map<string, vector<pair<int, int>>> rules;
vector<int> my_ticket;
vector<int> nearby_ticket;
int all_fields = 0;

int main() {
    fstream my_file;
    my_file.open("../input/test.txt", ios::in);
    string line;
    int step = 0;

    while (getline(my_file, line)) {
        if (line.size() == 0) {
            step++;
        } else if (step == 0) {
            vector<pair<int, int>> all_minmax;

            string field = line.substr(0, line.find(":"));
            line = line.substr(line.find(":") + 2);
            string minmaxstr = line.substr(0, line.find("or"));
            line = line.substr(line.find("or") + 3);

            
            int min = stoi(minmaxstr.substr(0, minmaxstr.find("-")));
            int max = stoi(minmaxstr.substr(minmaxstr.find("-")+1));
            pair<int, int> minmaxpair = pair<int, int> (min, max);
            all_minmax.push_back(minmaxpair);

            
            minmaxstr = line;
            
            min = stoi(minmaxstr.substr(0, minmaxstr.find("-")));
            max = stoi(minmaxstr.substr(minmaxstr.find("-")+1));
            minmaxpair = pair<int, int> (min, max);
            all_minmax.push_back(minmaxpair);
            rules[field] = all_minmax;
            all_fields++;
            
        } else if (step == 1 && line.find("your ticket:") == string::npos) {
            cout << "line : " << line << "\n";
            while (line.find(",") != string::npos) {
                my_ticket.push_back(stoi(line.substr(0, line.find(','))));
                line = line.substr(line.find(',') + 1);
            }
            my_ticket.push_back(stoi(line));
            
        } else if (step == 2 && line.find("nearby tickets:") == string::npos) {
            while (line.find(",") != string::npos) {
                nearby_ticket.push_back(stoi(line.substr(0, line.find(','))));
                line = line.substr(line.find(',') + 1);
            }
            nearby_ticket.push_back(stoi(line));
        }
        
    }

    for (auto ticket : nearby_ticket) {
        int valid_field = false;
        for (auto rule : rules) {
            if (!valid_field) {
                for (auto minmax : rule.second) {
                    if (get<0>(minmax) <= ticket && ticket <= get<1>(minmax)) {
                        valid_field = true;
                        break;
                    }
                }
            }
        }
        if (!valid_field) {
            cout << "ticket : " << ticket << "\n";
            ticket_error_rate += ticket;
        }
    }

    cout << "final result : " << ticket_error_rate;
}