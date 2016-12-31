std::vector<int> minimalBasketPrice(int maxPrice, std::vector<int> vendorsDelivery, std::vector<std::vector<int>> vendorsProducts) {
    int items = vendorsProducts[0].size();
    int vendors = vendorsProducts.size();
    
    // change every -1 to maxPrice+1 for easier computation later on
    for(auto &vendor: vendorsProducts)
        for(auto &price: vendor)
            if(price == -1)
                price = maxPrice+1;
    
    // insert at the head of every vendorsProducts vendor number and vendor delivery time
    for(int v=0; v<vendors; ++v) {
        vendorsProducts[v].insert(vendorsProducts[v].begin(), v);
        vendorsProducts[v].insert(vendorsProducts[v].begin(), vendorsDelivery[v]);
    }
    
    // sort by vendor delivery times, for equal deliery times sort rest
    sort(vendorsProducts.begin(), vendorsProducts.end());
 
    // min prices found for each item
    vector<int> minPrices(items,maxPrice+1);
    // the vendor which provides the min price
    vector<int> fromVendor(items, -1);

    for(int v=0; v<vendors; ++v) {
        // update minPrices and fromVendor
        for(int i=2; i<items+2; ++i) {
            if(vendorsProducts[v][i]<minPrices[i-2]) {
                minPrices[i-2] = vendorsProducts[v][i];
                fromVendor[i-2] = vendorsProducts[v][1];
            }
        }
        
        int tot = 0;
        for(int price: minPrices) tot += price;
        // if total price is within range goto end game
        if(tot<=maxPrice) {
            if(v+1<vendors && vendorsProducts[v+1][0]==vendorsProducts[v][0])
                continue;
            
            sort(fromVendor.begin(), fromVendor.end());
            auto toerase = unique(fromVendor.begin(), fromVendor.end());
            fromVendor.erase(toerase, fromVendor.end());
            
            return fromVendor;
        }
    }

    return {};
}
