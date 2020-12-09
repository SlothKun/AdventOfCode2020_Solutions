#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>

using namespace std;


// follow instructions and detect loop in program or end of the program
pair<int, bool> instruction_following(vector<pair<string, int>> instructions) {
    pair<string, int> current_instruction;
    int last_node = 0;
    int node = 0;
    int sum_acc = 0;
    map<int, bool> dejavu_path;
    int iterator = 0;
    while (true) {
        cout << node+1 << '\n';
        if (dejavu_path.find(node) != dejavu_path.end()) {
            cout << "dejavu : " << node+1 << '\n';
            return pair<int, bool>(sum_acc, false);
        } else if (node >= instructions.size()) {
            cout << "end\n";
            cout << get<0>(current_instruction) << " : " << get<1>(current_instruction) << "\n";
            return pair<int, bool>(sum_acc, true);
        } else {
            current_instruction = instructions[node];
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
    }
}


int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    vector<pair<string, int>> all_instructions;
    int value;
    string instruction;

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
    

    // get original path (don't include acc as we don't need them for the path)
    vector<int> original_path;
    pair<string, int> c_inst;
    int l_node = 0;
    int c_node = 0;
    bool looped = false;

    while (true) {
        for (auto c_path : original_path) {
            if (c_path == c_node) {
                looped = true;
                break;
            }
        }
        if (looped) {
            break;
        } else {
            c_inst = all_instructions[c_node];
            if (get<0>(c_inst).find("jmp") != string::npos) {
                l_node = c_node;
                original_path.push_back(c_node);
                c_node += get<1>(c_inst);
            } else if (get<0>(c_inst).find("acc") != string::npos) {
                l_node = c_node;
                c_node += 1;
            } else {
                original_path.push_back(c_node);
                l_node = c_node;
                c_node += 1;
            }
        }
    }
 

    vector<pair<string, int>> modified_instructions = all_instructions;

    // transform last instruction to nop if jmp and jmp if nop
    if (get<0>(modified_instructions[original_path.back()]).find("jmp") != string::npos) {
        get<0>(modified_instructions[original_path.back()]) = "nop";
    } else {
        get<0>(modified_instructions[original_path.back()]) = "jmp";
    }

    /*
    Call the instruction following function that'll report if a loop was detected
    if this is the case, then we'll try to change the last jmp/nop before the one we tried
    we do this again until there's no loop anymore
    */
    while (true) {
        cout << "test with " << get<0>(modified_instructions[original_path.back()]) << " at pos " << original_path.back()+1 << "\n";
        pair<int, bool> returned_value = instruction_following(modified_instructions);
        if (get<1>(returned_value) == 1) {
            cout << "sum : " << get<0>(returned_value) << '\n';
            break;
        } else {
            original_path.pop_back();
            if  (original_path.size() == 0) {
                cout << "No answer possible";
                break;
            } else if (get<0>(modified_instructions[original_path.back()]).find("jmp") != string::npos) {
                get<0>(modified_instructions[original_path.back()]) = "nop";
            } else {
                get<0>(modified_instructions[original_path.back()]) = "jmp";
            }
        }
    }
}