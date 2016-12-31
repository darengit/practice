std::vector<std::vector<double>> jetDashboard(std::vector<int> orders, int n) {
    vector<vector<double>> ret(n, vector<double>(3));
    int s = orders.size();
    ret[0] = {orders[s-n], orders[s-n], -1};
    
    int a = 1;
    for(int i=s-n+1; i<orders.size(); ++i) {
        ret[a][0] = (orders[i]>ret[a-1][0]) ? orders[i] : ret[a-1][0];
        ret[a][1] = (ret[a-1][1]*a+orders[i])/(a+1);
        double variance = 0;
        for(int j=s-n; j<=i; ++j)
            variance += pow(orders[j]-ret[a][1],2);
        
        
        ret[a][2] = sqrt(variance/a);
        ++a;
    }
    
    return ret;
}
