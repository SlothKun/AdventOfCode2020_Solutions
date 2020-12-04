#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include<vector>

using namespace std;

int max_width;
int max_height;
vector <string> path;
int ping_char = '#';

int get_path(int w_move, int h_move) {
    int tree_encountered = 0;
    int w_pos = 0;
    int h_pos = 0;
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
        if (h_pos >= max_height) {
            break;
        }

        if (path[h_pos][w_pos] == ping_char) {
            tree_encountered += 1;
        }
    }
    return tree_encountered;
}

int main() {
    fstream my_file;
    my_file.open("input/input.txt", ios::in);
    string line;

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
    int tmp_encounter;
    unsigned int final_nb = 0;
    final_nb = get_path(1, 1);
    tmp_encounter = get_path(3, 1);
    final_nb *= tmp_encounter;
    tmp_encounter = get_path(5, 1);
    final_nb *= tmp_encounter;
    tmp_encounter = get_path(7, 1);
    final_nb *= tmp_encounter;
    tmp_encounter =get_path(1, 2);
    final_nb *= tmp_encounter;


    cout << final_nb;
    
}