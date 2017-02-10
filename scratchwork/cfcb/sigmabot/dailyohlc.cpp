std::vector<std::vector<std::string>> dailyOHLC(std::vector<int> timestamp, std::vector<std::string> instrument, std::vector<std::string> side, std::vector<double> price, std::vector<int> size) {
    vector<string> timestrs;
    char buffer[50];
    for(long t: timestamp) {
        strftime(buffer,20,"%Y-%m-%d",gmtime(&t));
        timestrs.push_back(string(buffer));
    }
    
    unordered_map<string,unordered_map<string,vector<vector<double>>>> tradedata;
    
    for(int i=0; i<timestamp.size(); ++i)
        tradedata[timestrs[i]][instrument[i]].push_back({(double)timestamp[i],(double)i,price[i]});
    
    vector<vector<string>> ret;
    for(auto &kvbytimestr: tradedata) {
        for(auto &kvbyticker: kvbytimestr.second) {
            char buffer[50];
            
            sort(kvbyticker.second.begin(), kvbyticker.second.end());
            sprintf(buffer,"%.2f",kvbyticker.second.front()[2]);
            string open=string(buffer);
            sprintf(buffer,"%.2f",kvbyticker.second.back()[2]);
            string close=string(buffer);
            
            sort(kvbyticker.second.begin(), kvbyticker.second.end(), [](vector<double> &v1, vector<double> &v2)->bool{return v1[2]<v2[2];});
            
            sprintf(buffer,"%.2f",kvbyticker.second.front()[2]);
            string low=string(buffer);
            sprintf(buffer,"%.2f",kvbyticker.second.back()[2]);
            string high=string(buffer);
            
            ret.push_back({kvbytimestr.first,kvbyticker.first,open,high,low,close});
        }
    }
    
    sort(ret.begin(), ret.end());
    return ret;
}

