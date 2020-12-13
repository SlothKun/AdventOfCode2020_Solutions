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
 
int manathan_distance;

vector<char> ordered_pos = {'E', 'S', 'W', 'N'};
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

map<char, int> ship_coordinates = {
    {'E', 0},
    {'S', 0},
    {'W', 0},   
    {'N', 0}
};

map<char, int> waypoint_coordinates = {
    {'E', 10},
    {'S', 0},
    {'W', 0},
    {'N', 1}
};

map<int, int> negative_fix = {
    {-1, 3},
    {-2, 2},
    {-3, 1},
};



int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    int current_pos = 0;

    while (getline(my_file, line)) {
        char move = line[0];
        int units = stoi(line.substr(1));
        cout << "Move : " << move << " | Units : " << units << '\n';
        
        if (move == 'R') { // Rotate the waypoint's coordinate clockwise
            cout << "Before rotation\n";
            for (auto &item : waypoint_coordinates) {
                cout << item.first << " : " << item.second << "\n";
            }

            vector<int> temp_vec;
            for (int i = 0; i < ordered_pos.size(); i++) {
                temp_vec.push_back(waypoint_coordinates[ordered_pos[i]]);
            }

            rotate(temp_vec.rbegin(), (temp_vec.rbegin() + unit_to_pos[units]), temp_vec.rend());
            
            for (int i = 0; i < ordered_pos.size(); i++) {
                waypoint_coordinates[ordered_pos[i]] = temp_vec[i];
            }

            cout << "---------------\n";
            cout << "After rotation\n";
            for (auto &item : waypoint_coordinates) {
                cout << item.first << " : " << item.second << "\n";
            }
        } else if (move == 'L') { // Rotate the waypoint's coordinate counter-clockwise
            cout << "Before rotation\n";
            for (auto &item : waypoint_coordinates) {
                cout << item.first << " : " << item.second << "\n";
            }

            vector<int> temp_vec;
            for (int i = 0; i < ordered_pos.size(); i++) {
                temp_vec.push_back(waypoint_coordinates[ordered_pos[i]]);
            }

            rotate(temp_vec.begin(), (temp_vec.begin() + unit_to_pos[units]), temp_vec.end());

            for (int i = 0; i < ordered_pos.size(); i++) {
                waypoint_coordinates[ordered_pos[i]] = temp_vec[i];
            }

            cout << "---------------\n";
            cout << "After rotation\n";
            for (auto &item : waypoint_coordinates) {
                cout << item.first << " : " << item.second << "\n";
            }
        } else if (move == 'F') { // Make the ship move by unit times the waypoint coordinates
            for (int i = 0; i < all_pos.size(); i++) {
                ship_coordinates[all_pos[i]] += waypoint_coordinates[all_pos[i]] * units;
            }
        } else { // Update waypoint coordinates
            waypoint_coordinates[move] += units;
        }

        cout << "---------BOAT-----------\n";
        cout << "east : " << ship_coordinates['E'] << '\n';
        cout << "south : " << ship_coordinates['S'] << '\n';
        cout << "west : " << ship_coordinates['W'] << '\n';
        cout << "north : " << ship_coordinates['N'] << '\n';
        cout << "--------------------\n\n";
                
        cout << "----------WAYPOINT----------\n";
        
        cout << "east : " << waypoint_coordinates['E'] << '\n';
        cout << "south : " << waypoint_coordinates['S'] << '\n';
        cout << "west : " << waypoint_coordinates['W'] << '\n';
        cout << "north : " << waypoint_coordinates['N'] << '\n';
        cout << "--------------------\n\n";
    }


    // Compute Manathan distance & print final result
    int north_south_pos = abs(ship_coordinates['N'] - ship_coordinates['S']);
    int east_west_pos = abs(ship_coordinates['E'] - ship_coordinates['W']);
    manathan_distance = north_south_pos + east_west_pos;

    cout << "north_south_pos result : " << north_south_pos << "\n";
    cout << "east_west_pos result : " << east_west_pos << "\n";
    cout << "final result : " << manathan_distance;
}