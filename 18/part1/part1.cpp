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

unsigned long long int final_sum = 0;

unsigned long long int doTheMath(string expression);
unsigned long long int sanitizeExpression(string expression);


int main() {
    fstream my_file;
    my_file.open("../input/input.txt", ios::in);
    string line;
    while (getline(my_file, line)) {
        final_sum += sanitizeExpression(line);
    }
    cout << "final result : " << final_sum;
}

unsigned long long int sanitizeExpression(string expression) {
    while (expression.rfind('(') != string::npos) {
        int start = expression.rfind('(');
        int end = expression.find(')', start);
        int len = end-1-start;
        string subexpre = expression.substr(start+1, len);
        len = subexpre.size()+2;
        expression.erase(start, len);
        unsigned long long int sum = doTheMath(subexpre+" ");
        expression.insert(start, to_string(sum));
        cout << expression << "\n";
    }
    cout << "---\n";
    return doTheMath(expression+" ");
}

unsigned long long int doTheMath(string expression) {
    string subsum;
    string firstnb;
    string secondnb;
    while (true)
    {
        int add = expression.find(" + ");
        int multiply = expression.find(" * ");
        if (add != string::npos && (add < multiply || multiply == string::npos)) {
            firstnb = expression.substr(0, expression.find(" + "));
            expression = expression.substr(expression.find(" + ")+3); 
            secondnb = expression.substr(0, expression.find(' '));
            subsum = to_string(stoull(firstnb) + stoull(secondnb));
            
            expression.erase(0, secondnb.size());
            expression.insert(0, subsum);
            cout << "expr après + : " << expression << "\n";
        } else if (multiply != string::npos && (multiply < add || add == string::npos)) {
            firstnb = expression.substr(0, expression.find(" * "));
            expression = expression.substr(expression.find(" * ")+3); 
            secondnb = expression.substr(0, expression.find(' '));
            subsum = to_string(stoull(firstnb) * stoull(secondnb));
            
            expression.erase(0, secondnb.size());
            expression.insert(0, subsum);
            cout << "expr après * : " << expression << "\n";
        } else {
            cout << "expr final : " << expression << "\n";
            cout << "expr final stoull : " << stoull(expression) << "\n";
            return stoull(expression);
        }
    }
}