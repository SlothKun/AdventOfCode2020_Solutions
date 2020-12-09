#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
 
int sum_acc = 0;

vector<pair<string, int>> all_instructions;
map<int, bool> dejavu_path;
int value;
string instruction;


int main() {
    cout << "test\n";
    fstream my_file;
    my_file.open("../input/test.txt", ios::in);
    string line;
    //pair<string, int> current_instruction;

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
    
    int last_node = 0;
    int node = 0;
    pair<string, int> current_instruction;
    while (true) {
        cout << node << '\n';
        if (dejavu_path.find(node) != dejavu_path.end()) {
            break;
        } else {
            current_instruction = all_instructions[node];
            if (get<0>(current_instruction).find("jmp") != string::npos) {
                last_node = node;
                dejavu_path[node] = true;
                node += get<1>(current_instruction);
            } else if (get<0>(current_instruction).find("acc") != string::npos) {
                last_node = node;
                dejavu_path[node] = true;
                sum_acc += get<1>(current_instruction);
                node += 1;
            } else {
                last_node = node;
                node += 1;
            }
        }
        
        cout << get<0>(current_instruction) << " : " << get<1>(current_instruction) << "\n";
    }
    /*

    cout << get<0>(all_instructions[last_node]) << " 1: " << get<1>(all_instructions[last_node]) << "\n";

    
    if (get<0>(all_instructions[last_node]).find("jmp") != string::npos) {
        get<0>(all_instructions[last_node]) = "nop";
    } else {
        get<0>(all_instructions[last_node]) = "jmp";
    }

    cout << get<0>(all_instructions[last_node]) << " 2: " << get<1>(all_instructions[last_node]) << "\n";
    node = 0;
    sum_acc = 0;

    while (true) {
        if (node >= all_instructions.size() - 1) {
            break;
        } else {
            if (get<0>(all_instructions[node]).find("jmp") != string::npos) {
                node += get<1>(all_instructions[node]);
            } else if (get<0>(all_instructions[node]).find("acc") != string::npos) {
                sum_acc += get<1>(all_instructions[node]);
                node += 1;
            } else {
                node += 1;
            }
        }
    }
    

    cout << "sum : " << sum_acc << '\n';
    */
}