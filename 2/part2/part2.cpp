#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    fstream my_file;
    my_file.open("input/input.txt", ios::in);
    
    const string delimiter = " ";
    const string delimiternb = "-";
    const string delimiterlet = ":";
    
    int pos1;
    int pos2;
    string line;
    string nblimit;
    char letter;
    string password;
    int rightpassword = 0;
    int pos;
    int subpos;
    int charcount;
    while (1) {
        getline(my_file, line); 
        if (my_file.eof()) {
            break;
        }
        else {
            // Get the min & max number (in text)
            pos = line.find(delimiter);
            nblimit = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
            
            // Get the min & max number (in int)
            subpos = nblimit.find(delimiternb);
            pos1 = stoi(nblimit.substr(0, subpos)) - 1;
            nblimit.erase(0, subpos + delimiternb.length());
            pos2 = stoi(nblimit) - 1;
            
            // Get the letter concerned
            pos = line.find(delimiterlet);
            letter = line.substr(0, pos)[0];
            line.erase(0, pos + delimiterlet.length() + 1);

            // Get the password to check
            password = line;
            charcount = 0;
            for (int i = 0; i != password.length(); i++) {
                if (password[i] == letter && (i == pos1 || i == pos2)) {
                    charcount += 1;
                }
            }
            if (charcount == 1) {
                rightpassword += 1;
            }
        }
    }
    cout << rightpassword;
}