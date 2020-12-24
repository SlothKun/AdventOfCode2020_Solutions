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
#include <typeinfo>

using namespace std;

//string input = "784235916"; // my input
string input = "389125467"; // Test

int main() {
    int current_cup_pos = 0;
    string next_cups = "";
    char dest;
    cout << input << "\n";
    for (int i = 0; i < 11; i++) {
        cout << "CUPS ROUND " << i+1 << " : " << input << "\n";
        int current_cup = input[current_cup_pos] - 48;
        cout << "current_cup : " << current_cup << '\n';
        cout << "current_cup_pos : " << current_cup_pos << '\n';
        
        for (int y = 1; y <= 3; y++) {
            next_cups += input[(current_cup_pos + y) % input.size()];
        }
        cout << "next_cups : " << next_cups << "\n";

        do {
            current_cup--;
            if (current_cup == 0) {
                current_cup = 9;
            }
            dest = current_cup + 48;
        }
        while (next_cups.find(dest) != string::npos);

        
        // Erase
        for (int y = 0; y < 3; y++) {
            //cout << "next_cups[y] : " << next_cups[y] << "\n";
            //cout << "next_cups[y] t : " << typeid(next_cups[y]).name() << "\n";
            //int pos = input.find("next_cups[y]");
            int nextpos = input.find(next_cups[y]);
            //cout << nextpos << " pos\n";
            input.erase(input.begin() + nextpos);
        }



        cout << "after erase : " << input << "\n";
        cout << "dest : " << dest << "\n";
        int dest_pos = input.find(dest);
        cout << "dest pos: " << dest_pos << "\n";

        for (int y = 1; y <= 3; y++) {
            int dest_newpos = dest_pos+y;
            if (dest_newpos == 10) {
                current_cup_pos = 0;
            }
            input.insert(dest_newpos, 1, next_cups[y-1]);
        }
        cout << "after insert : " << input << "\n";
        
        
        
        current_cup_pos++;
        if (current_cup_pos == 10) {
            current_cup_pos = 0;
        }
        next_cups.clear();

        cout << input << "\n";
        cout << "---------\n";
    }   

    cout << "Result : " << input;
}
