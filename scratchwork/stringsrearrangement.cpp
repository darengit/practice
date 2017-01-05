#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

bool diffone(const string &s, const string &t) {
    int diff = 0;
    for(int i=0; i<s.size(); ++i) {
        if(s[i]!=t[i])
            ++diff;
    }
    return diff==1;
}

bool travelingsalesman(vector<unordered_set<int>> &g, unordered_set<int> &v, int i) {
    v.insert(i);
    if(v.size() == g.size()) return true;
    
    for(int j: g[i])
        if(v.find(j)==v.end() && travelingsalesman(g,v,j))
            return true;
    
    v.erase(i);
    return false;
}

bool stringsRearrangement(std::vector<std::string> inputArray) {
    vector<unordered_set<int>> graph(inputArray.size());
    for(int i=0; i<inputArray.size(); ++i) {
        for(int j=0; j<inputArray.size(); ++i) {
            if(diffone(inputArray[i],inputArray[j]))
                graph[i].insert(j);
        }
    }
    
    unordered_set<int> visited;
    for(int i=0; i<inputArray.size(); ++i)
        if(travelingsalesman(graph,visited,i))
            return true;
    
    return false;
    
}

int main() {
	return stringsRearrangement({"aba", "bab", "bbb"});
}
