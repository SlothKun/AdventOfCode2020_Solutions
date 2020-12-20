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

int main() {
    fstream my_file;
    my_file.open("../input/test.txt", ios::in);
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

    cout << "\n\n";

    for (int i = 0; i < 6; i++) {
        cout << "\n\nAfter " << i << " cycle: \n";
        dimensionsvector = addRow(dimensionsvector);
        dimensionsvector = addCol(dimensionsvector);
        dimensionsvector = addDimension(dimensionsvector);
        //dimensionsvector = applyCycle(dimensionsvector);
        
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