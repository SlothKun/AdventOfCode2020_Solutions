#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 

vector<string> old_seat_layout;
vector<string> seat_layout;
int sum_occupied_seat;

pair<int, int> x_axis_minmax(int x_axis) {
    if (x_axis == 0) {
        return pair<int, int> (x_axis, x_axis + 1);
    } else if (x_axis == seat_layout[0].size() - 1) {
        return pair<int, int> (x_axis - 1, x_axis);
    } else {
        return pair<int, int> (x_axis - 1, x_axis + 1);
    }
}

pair<int, int> y_axis_minmax(int y_axis) {
    if (y_axis == 0) {
        return pair<int, int> (y_axis, y_axis + 1);
    } else if (y_axis == seat_layout.size() - 1) {
        return pair<int, int> (y_axis - 1, y_axis);
    } else {
        return pair<int, int> (y_axis - 1, y_axis + 1);
    }  
}

vector<string> seat_layout_prediction(vector<string> current_seat_lines) {
    vector<string> new_seat_layout;
    for (int y = 0; y < current_seat_lines.size(); y++) {
        string new_seat_line = "";
        pair<int, int> y_minmax = y_axis_minmax(y);
        for (int x = 0; x < current_seat_lines[y].size(); x++) {
            pair<int, int> x_minmax = x_axis_minmax(x);
            int occupied_seat = 0;

            // Check occupied adjacents seats
            for (int v = get<0>(y_minmax); v <= get<1>(y_minmax); v++) {
                for (int h = get<0>(x_minmax); h <= get<1>(x_minmax); h++) {
                    //cout << "v - h : " << v << " " << h << "\n";
                    //cout << "y - x : " << y << " " << x << "\n";
                    //cout << "seat : " << current_seat_lines[v][h] << "\n";
                    //cout << "seat : " << (v != y || h != x) << "\n";
                    if ((v != y || h != x) && current_seat_lines[v][h] == '#') {
                        occupied_seat++;
                    }
                }
            }
            //cout << occupied_seat << "\n";
            // Change seat status depending on given rules
            if (current_seat_lines[y][x] == 'L' && occupied_seat == 0) {
                new_seat_line += '#';
            } else if (current_seat_lines[y][x] == '#' && occupied_seat >= 4) {
                new_seat_line += 'L';
            } else {
                new_seat_line += current_seat_lines[y][x];
            }
        }
        cout << new_seat_line << "\n";
        new_seat_layout.push_back(new_seat_line);
    }
    cout << "\n";
    return new_seat_layout;
}

int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    // Get all instructions & value & put them in a dict
    while (getline(my_file, line)) {
        seat_layout.push_back(line);
        old_seat_layout.push_back(line);
    }


    //cout << seat_layout.size() << "\n";
    bool first_time = true;
    while (seat_layout != old_seat_layout || first_time) {
        first_time = false;
        old_seat_layout = seat_layout;
        //cout << "------------\n";
        seat_layout = seat_layout_prediction(seat_layout);
    }
    
    //cout << old_seat_layout.size() << "\n";

    for (auto line : seat_layout) {
        for (auto let : line) {
            if (let == '#') {
                sum_occupied_seat++;
            }
        }
    }

    cout << "final result : " << sum_occupied_seat;
}