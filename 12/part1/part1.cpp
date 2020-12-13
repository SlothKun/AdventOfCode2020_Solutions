#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 
int manathan_distance;
//char all_pos[4] = {'W', 'N', 'E', 'S'};
map<int, char> all_pos = {
    {0, 'E'},
    {1, 'S'},
    {2, 'W'},
    {3, 'N'}
};

map<int, int> unit_to_pos = {
    {90, 1},
    {180, 2},
    {270, 3}
};

map<char, int> all_coordinates = {
    {'N', 0},
    {'E', 0},
    {'S', 0},   
    {'W', 0}
};

map<int, int> negative_fix = {
    {-1, 3},
    {-2, 2},
    {-3, 1},
};

int current_pos = 0;

int north_south_pos;
int east_west_pos;

int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    
    while (getline(my_file, line)) {
        char move = line[0];
        int units = stoi(line.substr(1));
        cout << "move : " << move << " Units : " << units << '\n';
        
        if (move == 'R') {
            cout << "R\n";
            current_pos = (current_pos + unit_to_pos[units]) % 4;
        } else if (move == 'L') {
            cout << "L\n";
            current_pos = current_pos - unit_to_pos[units];
            if (current_pos < 0) {
                current_pos = negative_fix[current_pos];
            }
        } else if (move == 'F') {
            cout << "F\n";
            all_coordinates[all_pos[current_pos]] += units;
        } else {
            cout << move << "\n";
            all_coordinates[move] += units;
        }

        cout << "--------------------\n";
        cout << "north : " << all_coordinates['N'] << '\n';
        cout << "south : " << all_coordinates['S'] << '\n';
        cout << "east : " << all_coordinates['E'] << '\n';
        cout << "west : " << all_coordinates['W'] << '\n';
        cout << "--------------------\n";
    }

    north_south_pos = abs(all_coordinates['N'] - all_coordinates['S']);
    east_west_pos = abs(all_coordinates['E'] - all_coordinates['W']);
    manathan_distance = north_south_pos + east_west_pos;
    cout << "north_south_pos result : " << north_south_pos << "\n";
    cout << "east_west_pos result : " << east_west_pos << "\n";
    cout << "final result : " << manathan_distance;
}