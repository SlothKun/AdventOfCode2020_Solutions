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

int check_top_seats(int initial_x, int initial_y);
int check_topright_seats(int initial_x, int initial_y);
int check_right_seats(int initial_x, int initial_y);
int check_bottomright_seats(int initial_x, int initial_y);
int check_bottom_seats(int initial_x, int initial_y);
int check_bottomleft_seats(int initial_x, int initial_y);
int check_left_seats(int initial_x, int initial_y);
int check_topleft_seats(int initial_x, int initial_y);

vector<string> seat_layout_prediction(vector<string> current_seat_lines);

int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    // Get all instructions & value & put them in a dict
    while (getline(my_file, line)) {
        cout << line << '\n';
        seat_layout.push_back(line);
        old_seat_layout.push_back(line);
    }
    cout << "\n";


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


vector<string> seat_layout_prediction(vector<string> current_seat_lines) {
    vector<string> new_seat_layout;
    for (int y = 0; y < current_seat_lines.size(); y++) {
        string new_seat_line = "";
        for (int x = 0; x < current_seat_lines[y].size(); x++) {
            if (current_seat_lines[y][x] != '.') {
                int occupied_seat = 0;
                //cout << "-----------\n";
                //cout << "coordinate : " << y << " " << x << '\n';
                //cout << "type : " << current_seat_lines[y][x] << '\n';
                // Check occupied first seen seats
                occupied_seat += check_top_seats(x, y);
                //cout << occupied_seat << '\n';
                occupied_seat += check_topright_seats(x, y);
                //cout << occupied_seat << '\n';
                occupied_seat += check_right_seats(x, y);
                //cout << occupied_seat << '\n';
                occupied_seat += check_bottomright_seats(x, y);
                //cout << occupied_seat << '\n';
                occupied_seat += check_bottom_seats(x, y);
                //cout << occupied_seat << '\n';
                occupied_seat += check_bottomleft_seats(x, y);
                //cout << occupied_seat << '\n';
                occupied_seat += check_left_seats(x, y);
                // cout << occupied_seat << '\n';
                occupied_seat += check_topleft_seats(x, y);
                //cout << occupied_seat << '\n';

                // Change seat status depending on given rules
                if (current_seat_lines[y][x] == 'L' && occupied_seat == 0) {
                    new_seat_line += '#';
                } else if (current_seat_lines[y][x] == '#' && occupied_seat >= 5) {
                    new_seat_line += 'L';
                } else {
                    new_seat_line += current_seat_lines[y][x];
                }
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



int check_top_seats(int initial_x, int initial_y) {
    if (initial_y == 0) {
        return 0;
    } else {
        for (int y = initial_y-1; y >= 0; y--) {
            if (seat_layout[y][initial_x] == 'L') {
                return 0;
            } else if (seat_layout[y][initial_x] == '#') {
                return 1;
            }
        }
    }
    return 0;
}

int check_topright_seats(int initial_x, int initial_y) {
    while (initial_x < seat_layout[0].size() && initial_y > 0) {
        initial_y--;
        initial_x++;

        if (seat_layout[initial_y][initial_x] == 'L') {
            return 0;
        } else if (seat_layout[initial_y][initial_x] == '#') {
            return 1;
        }            
    }
    return 0;
}

int check_right_seats(int initial_x, int initial_y) {
    if (initial_x == seat_layout[0].size() - 1) {
        return 0;
    } else {
        for (int x = initial_x + 1; x < seat_layout[0].size(); x++) {
            if (seat_layout[initial_y][x] == 'L') {
                return 0;
            } else if (seat_layout[initial_y][x] == '#') {
                return 1;
            }
        }
    }
    return 0;
}

int check_bottomright_seats(int initial_x, int initial_y) {
    while (initial_x < seat_layout[0].size() - 1 && initial_y < seat_layout.size() - 1) {
        initial_y++;
        initial_x++;

        if (seat_layout[initial_y][initial_x] == 'L') {
            return 0;
        } else if (seat_layout[initial_y][initial_x] == '#') {
            return 1;
        }
        
    }
    return 0;
}

int check_bottom_seats(int initial_x, int initial_y) {
    if (initial_y == seat_layout.size() - 1) {
        return 0;
    } else {
        for (int y = initial_y + 1; y < seat_layout.size(); y++) {
            if (seat_layout[y][initial_x] == 'L') {
                return 0;
            } else if (seat_layout[y][initial_x] == '#') {
                return 1;
            }
        }
    }
    return 0;
}

int check_bottomleft_seats(int initial_x, int initial_y) {
    while (initial_x > 0 && initial_y < seat_layout.size() - 1) {
        initial_y++;
        initial_x--;

        if (seat_layout[initial_y][initial_x] == 'L') {
            return 0;
        } else if (seat_layout[initial_y][initial_x] == '#') {
            return 1;
        }
    }
    return 0;
}

int check_left_seats(int initial_x, int initial_y) {
    if (initial_x == 0) {
        return 0;
    } else {
        for (int x = initial_x - 1; x >= 0; x--) {
            if (seat_layout[initial_y][x] == 'L') {
                return 0;
            } else if (seat_layout[initial_y][x] == '#') {
                return 1;
            }
        }
    }
    return 0;
}

int check_topleft_seats(int initial_x, int initial_y) {
    while (initial_x > 0 && initial_y > 0) {
        initial_y--;
        initial_x--;

        if (seat_layout[initial_y][initial_x] == 'L') {
            return 0;
        } else if (seat_layout[initial_y][initial_x] == '#') {
            return 1;
        }
    }
    return 0;
}
