#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 
int sum_acc = 0;

//map<string, int> all_instructions;
vector<pair<string, int>> all_instructions;
map<int, bool> dejavu_path;
int value;
string instruction;




int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;

    // Get all instructions & value & put them in a dict
    while (getline(my_file, line)) {
        instruction = line.substr(0, line.find(" "));

        if (line.find("+") != string::npos) {
            value = stoi(line.substr(line.find("+") + 1));
        } else {
            value = -stoi(line.substr(line.find("-") + 1));
        }
        all_instructions.push_back(pair<string, int>(instruction, value));

    }

    int node = 0;
    while (true) {
        if (dejavu_path.find(node) != dejavu_path.end()) {
            break;
        } else {
            pair<string, int> current_instruction = all_instructions[node];
            if (get<0>(current_instruction).find("jmp") != string::npos) {
                dejavu_path[node] = true;
                node += get<1>(current_instruction);
            } else if (get<0>(current_instruction).find("acc") != string::npos) {
                dejavu_path[node] = true;
                cout << get<0>(current_instruction) << " : " << get<1>(current_instruction) << "\n";
                sum_acc += get<1>(current_instruction);
                node += 1;
            } else {
                node += 1;
            }
        }
    }

    cout << "sum : " << sum_acc << '\n';
}