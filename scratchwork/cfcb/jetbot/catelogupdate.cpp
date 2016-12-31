std::vector<std::vector<std::string>> catalogUpdate(std::vector<std::vector<std::string>> catalog, std::vector<std::vector<std::string>> updates) {
    unordered_map<string, vector<string>> cat;
    for(auto category: catalog)
        cat[category[0]] = vector<string>(category.begin()+1, category.end());
    
    for(auto update: updates)
        cat[update[0]].push_back(update[1]);
    
    vector<vector<string>> ret;
    for(auto &p: cat) {
        sort(p.second.begin(), p.second.end());
        p.second.insert(p.second.begin(),p.first);
        ret.push_back(p.second);
    }
    
    sort(ret.begin(), ret.end());
    
    return ret;
    
}

