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
 
int earliest_timestamp;
int actual_timestamps;
int good_id;
vector<int> bus_id;


int main() {
    fstream my_file;
    my_file.open("../input/test.txt", ios::in);
    string line;

    getline(my_file, line);
    earliest_timestamp = stoi(line);
    actual_timestamps = earliest_timestamp;
    getline(my_file, line);
    
    string subline;
    while (line.find(',') != string::npos) {
        subline = line.substr(0, line.find(','));
        if (subline != "x") {
            bus_id.push_back(stoi(subline));
        }
        line = line.substr(line.find(',')+1);
    }
    if (line != "x") {
        bus_id.push_back(stoi(line));
    }

    bool found = false;
    while (found != true) {
        actual_timestamps += 1;
        for (auto id : bus_id) {
            int departure = remainder(actual_timestamps, id);
            if (departure == 0) {
                good_id = id;
                found = true;
                break;
            }
        }
    }


    cout << "final result : " << (actual_timestamps - earliest_timestamp) * good_id;
}