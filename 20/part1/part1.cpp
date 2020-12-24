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

unsigned long long int result = 0;
map<string, vector<string>> all_panels;
map<string, vector<string>> arranged_panels; // changer
//vector<vector<string>> extremities;
map<string, vector<string>> extremities;
vector<string> all_ids;

//vector<vector<string>> outermostExtremitiesSearch();
void outermostExtremitiesSearch();
vector<vector<string>> extremitiesSearch();
vector<string> getEdges();
void assembleExtremities();
void horizontalFlip();
void clockwiseRotation();

int main() {
    fstream my_file;
    my_file.open("../input/test.txt", ios::in);
    string line;

    // Get all panel & ID from input and store them in dict
    string id;
    vector<string> panel;
    while (getline(my_file, line)) {
        if (line.find("Tile ") != string::npos) {
            id = line.substr(line.find(" ")+1, (line.find(':')-1 - line.find(" ")));
            all_ids.push_back(id);
            cout << id << '\n';
        } else if (line.size() == 0) {
            cout << "\n";
            all_panels[id] = panel;
            panel.clear();
        } else {
            cout << line << "\n";
            panel.push_back(line);
        }
    }

    cout << "\n";
    outermostExtremitiesSearch();


    cout << "final result : " << result << "\n";
}

vector<string> getEdges(vector<string> panel) {
    vector<string> edges;
    string ledge = "";
    string redge = "";
    for (auto line : panel) {
        ledge += line.front();
        redge += line.back();
    }

    edges.push_back(ledge); // Left
    edges.push_back(panel.front()); // Top
    edges.push_back(redge); // Right
    edges.push_back(panel.back()); // Bottom

    /*
    for (auto edge : edges) {
        cout << "edge : " << edge << "\n";
    }
    cout << "------\n";
    */

    return edges;
}


void outermostExtremitiesSearch() {
    vector<string> outer_extrem_id;
    vector<string>::iterator it;
    for (auto fpanel : all_panels) {
        cout << "ID : " << fpanel.first << "\n";
        vector<string> edges = getEdges(fpanel.second);

        for (auto panel_cmp : all_panels)  {
            if (fpanel != panel_cmp) {
                vector<string> edges_cmp = getEdges(panel_cmp.second);
            
                vector<string> edges_tmp;
                for (auto edge : edges) {
                    for (auto edge_cmp : edges_cmp) {
                        if (edge == edge_cmp) {
                            edges_tmp.push_back(edge);
                            break;
                        }
                    }
                }
                
                it = unique(edges_tmp.begin(), edges_tmp.end());
                edges_tmp.resize(distance(edges_tmp.begin(), it));

                if (edges_tmp.size() != 4) {
                    outer_extrem_id.push_back(fpanel.first);
                }
            }
        }
    }

    cout << "outer\n";

    it = unique(outer_extrem_id.begin(), outer_extrem_id.end());
    outer_extrem_id.resize(distance(outer_extrem_id.begin(), it));

    for (auto i : outer_extrem_id) {
        cout << i << "\n";
    }
    
}




/*
void outermostExtremitiesSearch() {
    vector<string> outer_extrem_id;
    for (int pnb = 0; pnb < all_ids.size()-1; pnb++) {
        cout << "ID : " << all_ids[pnb] << "\n";
        vector<string> edges = getEdges(all_panels[all_ids[pnb]]);

        for (int pnb_cmp = pnb+1; pnb_cmp < all_ids.size(); pnb_cmp++) {
            vector<string> edges_cmp = getEdges(all_panels[all_ids[pnb_cmp]]);

            vector<string> edges_tmp;
            for (auto edge : edges) {
                for (auto edge_cmp : edges_cmp) {
                    if (edge == edge_cmp) {
                        edges_tmp.push_back(edge);
                        cout << "i\n";
                        break;
                    }
                }
            }
            
            vector<string>::iterator it = unique(edges_tmp.begin(), edges_tmp.end());
            edges_tmp.resize(distance(edges_tmp.begin(), it));

            if (edges_tmp.size() != 4) {
                outer_extrem_id.push_back(all_ids[pnb]);
            }
        }
    }

    cout << "outer\n";

}
    */