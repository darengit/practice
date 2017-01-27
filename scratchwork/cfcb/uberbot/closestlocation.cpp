bool similar(string x, string y) {
    int s = x.size();
    if(y.size() < s-1) return false;
    
    if(y.size() >= s) {
        int d = 0;
        for(int i=0; i<s; ++i)
            d += x[i]!=y[i];
        
        if(d<2) return true;
    }
    
    for(int i=0; i<s; ++i) {
        char tmp = x[i];
        x.erase(x.begin()+i);
        if(x==y.substr(0,s-1))
            return true;
        x.insert(x.begin()+i,tmp);
    }
    
    for(int i=0; i<s; ++i) {
        char tmp = y[i];
        y.erase(i);
        if(x==y.substr(0,s-1))
            return true;
        y.insert(y.begin()+i,tmp);
    }
    
    return false;
    
}

//dfos - distance from origin squared
//pol - point or line
int dfos(vector<int> pol) {
    if(pol.size()==2)
        return pol[0]*pol[0]+pol[1]*pol[1];
    
    if(pol[0]==pol[2]) { // vertical
        if(pol[1]<0 && pol[3]<0)
            return dfos({pol[0],pol[3]});
        else if (pol[1]>0 && pol[3]>0)
            return dfos({pol[0],pol[1]});
        else
            return pol[0]*pol[0];
    } else { // horizontal
        if(pol[0]<0 && pol[2]<0)
            return dfos({pol[2],pol[3]});
        else if (pol[0]>0 && pol[2]>0)
            return dfos({pol[0],pol[3]});
        else
            return pol[1]*pol[1];
    }
}

std::string closestLocation(std::string address, std::vector<std::vector<int>> objects, std::vector<std::string> names) {
    transform(address.begin(), address.end(), address.begin(), ::tolower);
    auto orig = names;
    for(auto &s: names)
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        
    int ds = INT_MAX; // distance from origin squared
    string r;

    for(int i=0; i<objects.size();++i) {
        int tmp = dfos(objects[i]);
        if(similar(address,names[i]) && tmp<ds)
            ds = tmp, r=orig[i];
    }
    
    return r;
}

