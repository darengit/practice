inline bool inPlay(vector<int> v) {
   return abs(v[0]) < 22 && abs(v[1]) < 22;
}

int bfs(const vector<int> &loggingCamp, const vector<vector<int>> &curr, set<vector<int>> &visited, const vector<vector<int>> &impassable, int steps) {
   /* 
   for(v: visited) {
       cout << v[0] << "," << v[1] << " - "  ;
   } 
   cout << endl;
   */ 
   // base case
   if(visited.find(loggingCamp) != visited.end())
       return steps;

   if(curr.empty())
       return -1;
    
   vector<vector<int>> next;
   for(vector<int> v: curr) {
       vector<vector<int>> neighbors;
       for(int i: {-1,1}) {
           neighbors.push_back({v[0]+i,v[1]});
           neighbors.push_back({v[0],v[1]+i});
           
           neighbors.push_back({v[0]+i,v[1]-i});
       }

       for(vector<int> n: neighbors) {
           // should change impassable to a set
           if(inPlay(n) && visited.find(n)==visited.end()  && find(impassable.begin(),impassable.end(),n)==impassable.end()) {
               next.push_back(n);
               visited.insert(n);
               //printf("reached %d %d %d\n", n[0], n[1], steps+1);
           }
       }
   }

   
    
   return bfs(loggingCamp, next, visited, impassable, steps+1);
}


bool farmingResources(std::vector<int> friendlyTroops, std::vector<int> enemyTroops, std::vector<int> loggingCamp, std::vector<std::vector<int>> impassableCells) {
   vector<int> friendlyStart {friendlyTroops[0], friendlyTroops[1]};
   set<vector<int>> visited;
   visited.insert(friendlyStart);
   int friendlySteps = bfs(loggingCamp, vector<vector<int>>{friendlyStart}, visited, impassableCells, 0);
   if(friendlySteps == -1) return false;

   vector<int> enemyStart {enemyTroops[0], enemyTroops[1]};
   visited.clear();
   visited.insert(enemyStart);
   int enemySteps = bfs(loggingCamp, vector<vector<int>>{enemyStart}, visited, impassableCells, 0);
   if(enemySteps == -1) return true;

   //printf("%d %d\n", friendlySteps, enemySteps); 
    
   return friendlySteps*friendlyTroops[2] < enemySteps*enemyTroops[2];
}
