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
vector<vector<string>> dimensionsvector;


// Create proto
vector<vector<string>> addRow(vector<vector<string>> all_dimensions);
vector<vector<string>> addCol(vector<vector<string>> all_dimensions);
vector<vector<string>> addDimension(vector<vector<string>> all_dimensions);
vector<vector<string>> applyCycle(vector<vector<string>> all_dimensions);

int main() {
    fstream my_file;
    my_file.open("../input/test.txt", ios::in);
    string line;
    vector<string> temp_mid_dim;

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

    cout << "\n\n";



    for (int i = 0; i < 6; i++) {
        cout << "After " << i+1 << " cycle: \n";
        dimensionsvector = addRow(dimensionsvector);
        dimensionsvector = addCol(dimensionsvector);
        dimensionsvector = addDimension(dimensionsvector);
        //dimensionsvector = applyCycle(dimensionsvector);
        
        int counter = 0;
        for (auto dim : dimensionsvector) {
            //cout << "DIM " << counter << ":\n";
            for (auto line : dim) {
                //cout << line << "\n";
            }
            counter++;
        }   
    }

    //cout << "final result : " << actives_count;
}

vector<vector<string>> addRow(vector<vector<string>> all_dimensions) {
    /* Add 2 rows (1 on top, 1 on the bottom) */
    vector<vector<string>> temp_all_dimensions;
    string empty_line = "";
    for (int i = 0; i < all_dimensions[0][0].size(); i++) {
        empty_line += ".";
    }

    for (auto dim : all_dimensions) {
        dim.push_back(empty_line);
        dim.insert(dim.begin(), empty_line);
        temp_all_dimensions.push_back(dim);
    }
    return temp_all_dimensions;
}

vector<vector<string>> addCol(vector<vector<string>> all_dimensions) {
    /* Increase col size by 2 for each line (1 on the left, 1 on the right) */
    vector<vector<string>> temp_all_dimensions;
    vector<string> temp_dim;
    for (auto dim : all_dimensions) {
        for (auto line : dim) {
            string temp_line = "..";
            temp_line.insert(1, line);
            temp_dim.push_back(temp_line);
        }
        temp_all_dimensions.push_back(temp_dim);
    }
    return temp_all_dimensions;
}

vector<vector<string>> addDimension(vector<vector<string>> all_dimensions) {
    /* add 2 empty dimensions (1 on the left, 1 on the right) */
    vector<vector<string>> temp_all_dimensions;
    string empty_line = "";
    vector<string> empty_dim;

    // Create an empty line
    for (int i = 0; i < all_dimensions[0][0].size(); i++) {
        empty_line += ".";
    }
    //cout << "size : " << empty_line.size() << "\nLine : " << empty_line << "\n";

    // Create an empty dim
    for (int i = 0; i < all_dimensions[0].size(); i++) {
        empty_dim.push_back(empty_line);
    }
    
    for (auto line : empty_dim) {
        cout << line << "\n";
    }

    temp_all_dimensions.push_back(empty_dim);
    temp_all_dimensions.push_back(empty_dim);
    for (int i = 0; i < all_dimensions.size(); i++) {
        temp_all_dimensions.insert(temp_all_dimensions.begin()+(i+1), all_dimensions[i]);
    }

    return temp_all_dimensions;
}