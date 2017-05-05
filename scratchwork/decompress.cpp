#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
Compression algorithm
--

Naive 2-gram compression algorithm.

Example:

Input of "abcdabcdghe"

iter0: ab cd ab cd gh e
freq0: ab: 2, cd: 2, gh: 1
grammar0: {ab: !, cd: @}
out0: !@!@ghe

iter1: !@ !@ gh e
freq1: !@: 2, gh: 1
grammar1: {ab: !, cd: @, !@: #}
out1: ##ghe

iter2: ## gh e
freq2: ##: 1, gh: 1

grammar: {ab: !, cd: @, !@: #}
out: ##ghe


Decompression algorithm
--

1. Reverse engineer the compression algorithm.
2. Added constraint that we perform computation as we process the string
> We do not process the string entirely in an iterative method

iterative
0) averylong##st!ring
1) averylong!@!@stabring
2) averylongabcdabcdstabring

sequential
0) averylong##st!ring
1) averylongabcdabcdstabring



Input
--

map<string,char> grammar -- could be either a constructor arg or passed into a function
string compressed -- has to be in the function

*/

string decompress(string compressed, map<string,char> g) {
    unordered_map<char, string> reverse_g;
    for(auto p: g)
        reverse_g[p.second]=p.first; // assumes values are unique;
    string res; 
    // critical section
    for(char c: compressed) {
        // decompress c to string tmp;
        // initialize these outside for loop with some initial size
        string tmp = string(1,c);
        string tmp1;
        
        while(tmp.size()!=tmp1.size()) {
            tmp1.clear();
            for(char tmpc: tmp) {
                if(reverse_g.count(tmpc)) {
                    tmp1 += reverse_g[tmpc];
                } else
                    tmp1.push_back(tmpc);
            }
            swap(tmp, tmp1);
        }
        res += tmp;
    }
    
    return res;
}

int main() {
    
    // This is the 2gram compressed text
    string compressed = "All +s\"!ings#/a 6/lik\"+m#cam\"to pass i(/clos\"upo(!\"d04l%y04n\"65*(hu&re%5*nty-fi*.";

    // With corresponding grammar
    map<string,char> grammar;
    grammar["23"] = '6';
    grammar["th"] = '!';
    grammar["e "] = '"';
    grammar[", "] = '#';
    grammar["an"] = '$';
    grammar["d "] = '%';
    grammar["nd"] = '&';
    grammar[" t"] = '\'';
    grammar["n "] = '(';
    grammar["se"] = ')';
    grammar["ve"] = '*';
    grammar["!e"] = '+';
    grammar["$%"] = '/';
    grammar["ea"] = '0';
    grammar["r "] = '1';
    grammar["!o"] = '2';
    grammar["us"] = '3';
    grammar["1o"] = '4';
    grammar["/)"] = '5';
    
    // Original text:
    // "All these things, and a thousand like them, came to pass " +
    // "in and close upon the dear old year one thousand seven hundred and seventy-five."
    
    cout << decompress(compressed, grammar);
    
    return 0;
    
}
