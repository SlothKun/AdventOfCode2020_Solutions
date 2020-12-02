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
    
    int minlimit;
    int maxlimit;
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
            minlimit = stoi(nblimit.substr(0, subpos));
            nblimit.erase(0, subpos + delimiternb.length());
            maxlimit = stoi(nblimit);
            
            // Get the letter concerned
            pos = line.find(delimiterlet);
            letter = line.substr(0, pos)[0];
            line.erase(0, pos + delimiterlet.length() + 1);

            // Get the password to check
            password = line;
            charcount = 0;
            for (int i = 0; i != password.length(); i++) {
                if (password[i] == letter) {
                    charcount += 1;
                }
            }
            if (charcount >= minlimit && charcount <= maxlimit) {
                rightpassword += 1;
            }
        }
    }
    cout << rightpassword;
}