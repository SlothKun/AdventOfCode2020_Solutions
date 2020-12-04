#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include<vector>

using namespace std;

int main() {
    fstream my_file;
    my_file.open("input/input.txt", ios::in);
    
    vector <string> path;
    string line;
    int ping_char = '#';
    int tree_encountered = 0;
    int max_width;
    int max_height;
    const int w_move = 3;
    const int h_move = 1;
    int w_pos = 0;
    int h_pos = 0;

    // Put every line into the list
    while (1) {
        getline(my_file, line); 
        if (my_file.eof()) {
            break;
        }
        else {
          path.push_back(line);
        }
    }

    // Get max height & width of the path
    max_height = path.size();
    max_width = path[0].length();


    for (int i=0; i < max_height-1; i++) {
        /*
            Move 3 to the right & 1 to the bottom
            If we hit the right side of the path, we go back to the left side (because the pattern repeat itself)
            when a tree is encounter, we increase the counter
        */
        w_pos += w_move;
        h_pos += h_move;
        if (w_pos >= max_width) {
            w_pos = w_pos - max_width;
        }
        if (path[h_pos][w_pos] == ping_char) {
            tree_encountered += 1;
        }
    }

    cout << tree_encountered;
    
}