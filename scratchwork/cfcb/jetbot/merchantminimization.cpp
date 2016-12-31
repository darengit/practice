bool merchantCombos(std::vector<std::string> items, std::vector<std::vector<std::string>> merchants, vector<vector<int>> &ret, int offset) {

    if(items.empty()) {
        ret.push_back({});
        return true;
    }
    if(merchants.empty())
        return false;

    bool found = false;
    
    for(int m=0; m<merchants.size(); ++m) {
        auto merchant = merchants[m];
        vector<string> remainingitems;
        for(int i=0; i<items.size(); ++i)
            if(find(merchant.begin(),merchant.end(),items[i]) == merchant.end())
                remainingitems.push_back(items[i]);
        if(items.size() == remainingitems.size())
            continue;
        
        // merchant m has at least 1 item from items
        vector<vector<string>> remainingmerchants(merchants.begin()+m+1, merchants.end());
        
        vector<vector<int>> intermediateresult;
        if(!merchantCombos(remainingitems, remainingmerchants, intermediateresult, offset+m+1)) {
            continue;
        } else {
            found = true;
            
            for(auto &v: intermediateresult) {
                v.push_back(m+offset);
                ret.push_back(move(v));
            }
        }            
    }
    return found;
}

std::vector<int> merchantMinimization(std::vector<std::string> items, std::vector<std::vector<std::string>> merchants) {
    vector<vector<int>> res;
    
    if(!merchantCombos(items,merchants,res,0) && res.empty())
        return {-1};
    
    for(auto &v: res)
        sort(v.begin(), v.end());
    
    sort(res.begin(), res.end(), [](auto a, auto b)->bool{return a.size()<b.size() || (a.size()==b.size() && a<b);});

    return res[0];
}

