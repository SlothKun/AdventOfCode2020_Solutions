#include <iostream>
#include <list>
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
    
    float highest_id = 0;
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
                    maxrow = ceil(maxrow - ((maxrow - minrow) / 2)); // take the lower half
                } else if (line[i] == 'B') {
                    minrow = floor(maxrow - ((maxrow - minrow) / 2));  // take the upper half
                }
            }
            if (line[6] == 'F') {
                actual_row = minrow; // take the lower half
            } else if (line[6] == 'B') {
                actual_row = maxrow;  // take the upper half
            }

            cout << "maxrow " << maxrow << '\n';
            cout << "minrow " << minrow << '\n';
            cout << "actual_row " << actual_row << '\n';

            float mincol = 0;
            float maxcol = 7;
            for (int i=7; i < 9; i++) {
                if (line[i] == 'L') {
                    maxcol = ceil(maxcol - ((maxcol - mincol) / 2)); // take the lower half
                } else if (line[i] == 'R') {
                    mincol = floor(maxcol - ((maxcol - mincol) / 2));  // take the upper half
                }
            }


            if (line[9] == 'L') {
                actual_col = mincol; // take the lower half
            } else if (line[9] == 'R') {
                actual_col = maxcol;  // take the upper half
            } 

            cout << "maxcol " << maxcol << '\n';
            cout << "mincol " << mincol << '\n';
            cout << "actual_col " << actual_col << '\n';
            
            actual_id = actual_row * 8 + actual_col;
            cout << actual_id << "\n";
            if (actual_id > highest_id) {
                highest_id = actual_id;
            }
        }
    }
    cout << "highest_id : " << highest_id;
    
}