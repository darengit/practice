int unionsize(const vector<string> &v1, const vector<string> &v2) {
    unordered_set<string> un;
    for(string s: v1) un.insert(s);
    for(string s: v2) un.insert(s);
    return un.size();
}

int intersize(const vector<string> &v1, const vector<string> &v2) {
    unordered_set<string> un;
    for(string s: v1) un.insert(s);
    int ret = 0;
    for(string s: v2)
        if(un.find(s)!=un.end())
            ++ret;
    return ret;
}


std::string categoryRecommendations(std::vector<std::vector<std::string>> requestData, std::vector<std::string> proSelections) {
    unordered_map<string,double> data;
    unordered_map<string,int> counts;
    
    for(auto v: requestData) {
        int un = unionsize(v, proSelections);
        int in = intersize(v, proSelections);
        for(string s: v)
            if(find(proSelections.begin(), proSelections.end(),s)==proSelections.end())
                data[s] += (double)in/un,++counts[s];
    }
    
    if(data.empty()) return "";
    
    vector<pair<string,double>> vdata;
    for(auto p: data)
        vdata.push_back(p);
    
    for(auto &p: vdata)
        p.second /= counts[p.first];
    
    sort(vdata.rbegin(), vdata.rend(),[](pair<string,double>p1, pair<string,double>p2)->bool {
        return p1.second<p2.second || p1.second==p2.second && p1.first>p2.first;
    });
    
    return (vdata[0].second>0)?vdata[0].first:"";
}
