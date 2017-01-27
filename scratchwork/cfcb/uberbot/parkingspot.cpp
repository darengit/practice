bool parkingSpot(std::vector<int> carDimensions, std::vector<std::vector<int>> parkingLot, std::vector<int> luckySpot) {
    int cl = carDimensions[0]; // car length
    
    if(luckySpot[3]-luckySpot[1]+1 == cl) {
        int s = parkingLot[0].size();
        int f = luckySpot[3]; // space front
        int b = luckySpot[1]; // space back
        int l = luckySpot[0]; // space left
        int r = luckySpot[2]; // space right
        
        bool ss = true; // small side
        for(int i=0; i<=f; ++i)
            for(int j=l; j<=r; ++j)
                if(parkingLot[j][i])
                    ss = false;
    
        bool ls = true; // large side
        for(int i=b; i<s; ++i)
            for(int j=l; j<=r; ++j)
                if(parkingLot[j][i])
                    ls = false;

    
        return ss || ls;

        
    } else {
        int s = parkingLot.size();
        int f = luckySpot[2]; // space front
        int b = luckySpot[0]; // space back
        int l = luckySpot[1]; // space left
        int r = luckySpot[3]; // space right
        
        bool ss = true; // small side
        for(int i=0; i<=f; ++i)
            for(int j=l; j<=r; ++j)
                if(parkingLot[i][j])
                    ss = false;
    
        bool ls = true; // large side
        for(int i=b; i<s; ++i)
            for(int j=l; j<=r; ++j)
                if(parkingLot[i][j])
                    ls = false;

    
        return ss || ls;
        
    }
}

