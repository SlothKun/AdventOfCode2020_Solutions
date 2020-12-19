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
 

vector<int> input = {0,1,4,13,15,12,16};
//vector<int> input = {0,3,6};
//vector<int> input = {1,3,2};
map<int, vector<int>> last_spoken_nb;
int last_nb;
int actual_nb;


int main() {

    for (int i = 0; i < input.size() - 1; i++) {
        last_spoken_nb[input[i]] = {i+1};
        cout << "input : " << input[i] << "\n";
    }

    last_nb = input[input.size()-1];
    cout << "input : " << input[input.size()-1] << "\n";

    for (int round = input.size()+1; round <= 2020; round++) {
        cout << "----- Round : " << round << " -----\n";
        if (last_spoken_nb.find(last_nb) == last_spoken_nb.end()) {
            cout << "last nb : " << last_nb << " not in map\n";
            last_spoken_nb[last_nb] = {round-1};
            last_nb = 0;
            cout << "new last : " << last_nb << '\n';
        } else {
            cout << "last nb : " << last_nb << " in map\n";
            cout << "second to last nb array : " << last_spoken_nb[last_nb].back() << "\n";
            actual_nb = last_nb;
            cout << " last nb array : " << (round-1) << "\n";
            last_nb = (round-1) - last_spoken_nb[last_nb].back();     
            last_spoken_nb[actual_nb].push_back(round-1);
            cout << "new last : " << last_nb << '\n';
        }
    }

    cout << "final result : " << last_nb;
}