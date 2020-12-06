#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    fstream my_file;
    my_file.open("input/input.txt", ios::in);
    string line;
    
    vector <float> ids;
    float highest_id = 0;
    float my_seat = 0;
    float actual_id = 0;
    float actual_row = 0;
    float actual_col = 0;




    while (1) {
        getline(my_file, line);
        if (my_file.eof()) {
            break;
        } else {
            float minrow = 0;
            float maxrow = 127;

            for (int i=0; i < 6; i++) {
                if (line[i] == 'F') {
                    maxrow = floor(maxrow - ((maxrow - minrow) / 2)); // take the lower half
                } else if (line[i] == 'B') {
                    minrow = ceil(maxrow - ((maxrow - minrow) / 2));  // take the upper half
                }
            }
            if (line[6] == 'F') {
                actual_row = minrow; // take the lower half
            } else if (line[6] == 'B') {
                actual_row = maxrow;  // take the upper half
            }

            //cout << "maxrow " << maxrow << '\n';
            //cout << "minrow " << minrow << '\n';
            //cout << "actual_row " << actual_row << '\n';

            float mincol = 0;
            float maxcol = 7;
            for (int i=7; i < 9; i++) {
                if (line[i] == 'L') {
                    maxcol = floor(maxcol - ((maxcol - mincol) / 2)); // take the lower half
                } else if (line[i] == 'R') {
                    mincol = ceil(maxcol - ((maxcol - mincol) / 2));  // take the upper half
                }
            }


            if (line[9] == 'L') {
                actual_col = mincol; // take the lower half
            } else if (line[9] == 'R') {
                actual_col = maxcol;  // take the upper half
            } 

            //cout << "maxcol " << maxcol << '\n';
            //cout << "mincol " << mincol << '\n';
            //cout << "actual_col " << actual_col << '\n';
            
            actual_id = actual_row * 8 + actual_col;
            if (actual_id > highest_id) {
                highest_id = actual_id;
            }
            ids.push_back(actual_id);
        }
    }
    sort(ids.begin(), ids.end());
    bool found = false;
    for (int i = 1; i < highest_id; i++) {
        if (found) {
            break;
        }
        for (int y = 0; y < ids.size(); y++) {
            //cout << "i : " << i << " / ";
            //cout << "ids[y] : " << ids[y] << '\n';
            if (ids[y] == i-1 && ids[y+1] == i+1) {
                cout << "i : " << i << "\n";
                my_seat = i;
                //found = true;
                //break;
            }
        }
    }

    cout << "highest_id : " << highest_id << "\n";
    cout << "my seat is : " << my_seat;
    
}