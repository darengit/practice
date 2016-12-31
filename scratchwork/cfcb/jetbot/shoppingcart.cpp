std::vector<std::string> shoppingCart(std::vector<std::string> requests) {
    vector<pair<string,int>> ret;
    
    for(string request: requests) {
        if(request == "checkout")
            ret = vector<pair<string,int>>{};
        
        else if(request[0]=='a') {
            ret.push_back(pair<string,int>(request.substr(6),1));
        } else if(request[0]=='r') {
            string toremove = request.substr(9);
            ret.erase(find_if(ret.begin(),ret.end(),[&toremove](auto p)->bool{return p.first == toremove;}));
        } else {
            string temp = request.substr(15);
            int colondex = temp.find(':');
            string item = temp.substr(0,colondex-1);
            int qty = stoi(temp.substr(colondex+2));
            auto itr = find_if(ret.begin(), ret.end(), [&item](auto p)->bool{return p.first == item;});
            itr->second += qty;
        }
    }
    
    vector<string> r;
    for(auto p: ret)
        r.push_back(p.first + " : " + to_string(p.second));
    
    return r;
}

