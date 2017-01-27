int nightRoute(std::vector<std::vector<int>> city) {
    int s = city.size();

    vector<vector<int>> shortest = city;
    for(int i=0; i<s; ++i)
        shortest[i][i] = 0;

    for(int r=0; r<s; ++r) {
    for(int c=0; c<s; ++c) {
        if(city[r][c] >= 0) {
        // recalculate every shortest between every node connected to r
        // to every node c connects to
                
        for(int i=0; i<s; ++i) {
            if(shortest[i][r]>=0) {
            for(int j=0; j<s; ++j) {
                if(shortest[c][j]>=0) {
                    if(shortest[i][j]<0 || shortest[i][j] > shortest[i][r]+city[r][c]+shortest[c][j])
                        shortest[i][j] = shortest[i][r] + city[r][c] + shortest[c][j];
                    }
                }
            }
        }
        }
    }
    }

    return shortest[0][s-1];
}

