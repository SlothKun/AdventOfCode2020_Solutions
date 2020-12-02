#include <iostream>
#include <list>
#include <fstream>
#include <string>

using namespace std;

int main() {
	const int MAXNB = 2020;
	fstream my_file;
	list<int>nblist = {};
	int nbint = 0;
	my_file.open("input/input.txt", ios::in);
	string nbtext;
	// Insert all number in list if they're < MAXNB
	while (1) {
		getline(my_file, nbtext); 
		if (my_file.eof()) {
			break;
		}
		else {
			//cout << nbtext << '\n';
			nbint = stoi(nbtext);
			if (nbint < MAXNB) {
				nblist.push_back(nbint);
			}
		}

	}
	
	// make the sum of each nb and stop when we have the sum
	list <int> :: iterator fnb;
	list <int> :: iterator snb;
	int sum = 0;
	int multiplied = 0;
	bool found = false;
	for (fnb = nblist.begin(); fnb != nblist.end(); fnb++)
	{
		
		int i = 0;
		for (snb = fnb; snb != nblist.end(); snb++) {
			 if (i != 0) {
				 sum = *fnb + *snb;
				 if (sum == 2020) {
					 multiplied = *fnb * *snb;
					 found = true;
					 break;
				 }
			 }
			 i += 1;
		}
		if (found) {
			break;
		}
	}
	
	cout << multiplied;
	return 0;
}