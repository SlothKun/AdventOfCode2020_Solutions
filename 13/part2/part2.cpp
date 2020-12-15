#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

/*
Faire en sorte de prendre le plus gros nombre et de faire du + 59 dans le cas du gros input, et tous les 59 on check
on fait - si le nb de min est plus petit que celui du nombre choisi et sinon on add
et on check 
*/


int earliest_timestamp;
unsigned long long int actual_timestamps;

map<int, int> bus_id;
int highest_id = 0;

int main() {
    fstream my_file;
    my_file.open("../input/test.txt", ios::in);
    string line;

    getline(my_file, line);
    earliest_timestamp = stoi(line);
    actual_timestamps = earliest_timestamp;
    getline(my_file, line);
    
    string subline;
    int delay = 0;
    while (line.find(',') != string::npos) {
        subline = line.substr(0, line.find(','));
        if (subline != "x") {
            bus_id[stoi(subline)] = delay;
            if (stoi(subline) > highest_id) {
                highest_id = stoi(subline);
            }
        }
        delay += 1;
        line = line.substr(line.find(',')+1);
    }
    if (line != "x") {
        bus_id[stoi(line)] = delay;
    }

    
    for (auto id : bus_id) {
        cout << id.first << " : " << id.second << "\n";
    }
    
    /*
    while (true) {
        actual_timestamps += 1;
        if (remainder(actual_timestamps, highest_id) == 0) {
            break;
        }
    }
    */
    

    int found;
    cout << actual_timestamps << '\n';

    while (found != bus_id.size()) {
        found = 0;
        actual_timestamps += 1;
        if (remainder((actual_timestamps + bus_id[highest_id]), highest_id) == 0) {
            for (auto id : bus_id) {
                int departure = remainder((actual_timestamps + id.second), id.first);
                //cout << departure << "\n";
                if (departure == 0) {
                    found += 1;
                    //cout << found << '\n';
                } else {
                    break;
                }
            }
        }
    }
    cout << "final result : " << actual_timestamps;
}