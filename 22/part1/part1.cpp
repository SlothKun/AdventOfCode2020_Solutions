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

using namespace std;

int result = 0;
vector<list<int>> decks;

int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;

    // Get all panel & ID from input and store them in dict
    int card;
    list<int> deck;
    while (getline(my_file, line)) {
        if (line.size() == 0) {
            decks.push_back(deck);
            deck.clear();
        } else if (line.find("Player") == string::npos) {
            card = stoi(line);
            deck.push_back(card);
        }
    }

    decks.push_back(deck);


    for (auto pdeck : decks) {
        cout << "Deck : \n";
        for (auto card : pdeck) {
            cout << "card : " << card << '\n';
        }
        cout << "-----\n";
    }

    while (decks[0].size() != 0 && decks[1].size() != 0) {
        int p1_card = decks[0].front(); 
        int p2_card = decks[1].front();

        decks[0].pop_front();
        decks[1].pop_front();

        if (p1_card > p2_card) {
            decks[0].push_back(p1_card);
            decks[0].push_back(p2_card);
        } else {
            decks[1].push_back(p2_card);
            decks[1].push_back(p1_card);
        }
    }

    int winner;
    if (decks[0].size() != 0) {
        winner = 0;
    } else {
        winner = 1;
    }

    int card_count = decks[winner].size();
    for (auto card : decks[winner]) {
        result += card * card_count;
        card_count--;
    }
    

    cout << "final result : " << result << "\n";
}
