int packageBoxing(std::vector<int> pkg, std::vector<std::vector<int>> boxes) {
    sort(pkg.begin(), pkg.end());
    
    for(auto &box: boxes) sort(box.begin(), box.end());
    
    int volumn = INT_MAX;
    int retbox = -1;
    for(int i=0; i<boxes.size(); ++i) {
        auto box = boxes[i];
        if(box[0]>=pkg[0] && box[1]>=pkg[1] && box[2]>=pkg[2]) {
            int boxvol = box[0]*box[1]*box[2];
            if(boxvol < volumn) {
                retbox = i;
                volumn = boxvol;
            }
        }
    }
    
    return retbox;
}

