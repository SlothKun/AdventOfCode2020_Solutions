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

int actives_count = 0;



// Create proto
vector<vector<string>> addRow(vector<vector<string>> all_dimensions);
vector<vector<string>> addCol(vector<vector<string>> all_dimensions);
vector<vector<string>> addDimension(vector<vector<string>> all_dimensions);
vector<vector<string>> applyCycle(vector<vector<string>> all_dimensions);
int checkXYSide(pair<int, int> point, vector<string> dimension, bool count_himself);
pair<int, int> axis_minmax(int axis, int maxsize);

int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    vector<string> temp_mid_dim;
    vector<vector<string>> dimensionsvector;

    while (getline(my_file, line)) {
        temp_mid_dim.push_back(line);
    }

    dimensionsvector.push_back(temp_mid_dim);

    cout << "Before any cycles: \n";
    for (auto i : dimensionsvector) {
        for (auto y : i) {
            cout << y << "\n";
        }
    }

    for (int i = 0; i < 6; i++) {
        cout << "\n\nAfter " << i+1 << " cycle: \n";
        dimensionsvector = addRow(dimensionsvector);
        dimensionsvector = addCol(dimensionsvector);
        dimensionsvector = addDimension(dimensionsvector);
        dimensionsvector = applyCycle(dimensionsvector);
        
        int counter = 0;
        for (auto dim : dimensionsvector) {
            cout << "DIM " << counter << ":\n";
            for (auto line : dim) {
              cout << line << "\n";
            }
            cout << "\n\n";
            counter++;
        }   
        
    }

    // count the number of active state (multiply by 2 when this is another dim because they work in mirror front/back)
    int anotherdim_count = 0;
    for (int dim = 0; dim < dimensionsvector.size(); dim++) {
        int temp_count = 0;
        for (auto line : dimensionsvector[dim]) {
            for (auto state : line) {
                if (state == '#') {
                    temp_count++;
                }
            }
        }
        if (dim > 0) {
            temp_count *= 2;
        }
        actives_count += temp_count;
    }
    
    cout << "final result : " << actives_count;
}

vector<vector<string>> addRow(vector<vector<string>> all_dimensions) {
    /* 
        Add 2 rows (1 on top, 1 on the bottom)
    */
    vector<vector<string>> temp_all_dimensions;
    string empty_line = "";
    for (int i = 0; i < all_dimensions[0][0].size(); i++) {
        empty_line += ".";
    }

    for (auto dim : all_dimensions) {
        vector<string> temp_dim;
        temp_dim.push_back(empty_line);
        for (auto line : dim) {
            temp_dim.push_back(line);
        }
        temp_dim.push_back(empty_line);
        temp_all_dimensions.push_back(temp_dim);
    }


    return temp_all_dimensions;
}

vector<vector<string>> addCol(vector<vector<string>> all_dimensions) {
    /* 
        Increase col size by 2 for each line (1 on the left, 1 on the right)
    */
    vector<vector<string>> temp_all_dimensions;
    
    for (auto dim : all_dimensions) {
        vector<string> temp_dim;
        for (auto line : dim) {
            string temp_line = "..";
            temp_line.insert(1, line);
            //cout << "temp : " << temp_line << "\n";
            temp_dim.push_back(temp_line);
            
        }
        //cout << "\n\n";
        temp_all_dimensions.push_back(temp_dim);
    }
    return temp_all_dimensions;
}

vector<vector<string>> addDimension(vector<vector<string>> all_dimensions) {
    /* 
        add 2 empty dimensions (1 on the left, 1 on the right) 
    */
    vector<vector<string>> temp_all_dimensions = all_dimensions;
    string empty_line = "";
    vector<string> empty_dim;

    // Create an empty line
    for (int i = 0; i < all_dimensions[0][0].size(); i++) {
        empty_line += ".";
    }

    // Create an empty dim
    for (int i = 0; i < all_dimensions[0].size(); i++) {
        empty_dim.push_back(empty_line);
    }

    temp_all_dimensions.push_back(empty_dim);

    return temp_all_dimensions;
}

vector<vector<string>> applyCycle(vector<vector<string>> all_dimensions) {
    vector<vector<string>> alldimensions_aftercycle;

    for (int d = 0; d < all_dimensions.size(); d++) {
        cout << "Dim n°" << d << '\n';
        vector<string> temp_dim = {};
        for (int y = 0; y < all_dimensions[d].size(); y++) {
            string temp_line = "";
            for (int x = 0; x < all_dimensions[d][y].size(); x++) {
                int active_neighbours = 0;
                if (d == 0) {
                    active_neighbours += checkXYSide(pair<int, int>(x, y), all_dimensions[d], false);
                    active_neighbours += checkXYSide(pair<int, int>(x, y), all_dimensions[d+1], true) * 2;
                } else if (d == all_dimensions.size() - 1) {
                    active_neighbours += checkXYSide(pair<int, int>(x, y), all_dimensions[d], false);
                    active_neighbours += checkXYSide(pair<int, int>(x, y), all_dimensions[d-1], true);
                } else {
                    active_neighbours += checkXYSide(pair<int, int>(x, y), all_dimensions[d-1], true);
                    active_neighbours += checkXYSide(pair<int, int>(x, y), all_dimensions[d], false);
                    active_neighbours += checkXYSide(pair<int, int>(x, y), all_dimensions[d+1], true);   
                }

                cout << "x : " << x << " | y : " << y << " | type : " << all_dimensions[d][y][x] << " | count : " << active_neighbours << "\n";
                //cout << checkXYSide(pair<int, int>(x, y), all_dimensions[d]) << "\n";

                if (all_dimensions[d][y][x] == '#' && (active_neighbours < 2 || active_neighbours > 3)) {
                    cout << "become inactive\n";
                    temp_line += '.';
                } else if (all_dimensions[d][y][x] == '.' && active_neighbours == 3) {
                    cout << "become active\n";
                    temp_line += '#';
                } else {
                    cout << "stay\n";
                    temp_line += all_dimensions[d][y][x];
                }


            }
            temp_dim.push_back(temp_line);
            cout << "---\n";
        }
        alldimensions_aftercycle.push_back(temp_dim);
    }
    return alldimensions_aftercycle;
}

int checkXYSide(pair<int, int> point, vector<string> dimension, bool count_himself) {
    pair<int, int> x_minmax = axis_minmax(get<0>(point), dimension[0].size());
    pair<int, int> y_minmax = axis_minmax(get<1>(point), dimension.size());
    int active_state = 0;

    // Check adjacent states
    for (int y = get<0>(y_minmax); y <= get<1>(y_minmax); y++) {
        for (int x = get<0>(x_minmax); x <= get<1>(x_minmax); x++) {
            if ((x != get<0>(point) || y != get<1>(point)) && dimension[y][x] == '#') {
                active_state++;
            } else if ((x == get<0>(point) && y == get<1>(point)) && dimension[y][x] == '#' && count_himself) {
                active_state++;
            }
        }
    }
    return active_state;
}


pair<int, int> axis_minmax(int axis, int maxsize) {
    if (axis == 0) {
        return pair<int, int> (axis, axis + 1);
    } else if (axis == maxsize - 1) {
        return pair<int, int> (axis - 1, axis);
    } else {
        return pair<int, int> (axis - 1, axis + 1);
    }
}