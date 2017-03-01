#include <vector>
#include <iostream>

std::vector<bool> getKth(const std::vector<std::vector<int>> &combinatrix, int from, int choose, int k) {
   if(from == 1 && choose<=1 && !k)
       return std::vector<bool>{(bool)choose};
   if(choose>from || k>=combinatrix[from][choose])
       return std::vector<bool>{};

   if(!choose && !k)
       return std::vector<bool> (from,false);
   if(from==choose && !k)
       return std::vector<bool> (from, true);

   if(k<combinatrix[from][choose]*(from-choose)/from) { // don't choose 1st elt
       std::vector<bool> res = getKth(combinatrix,from-1,choose,k);
       if(!res.empty())
           res.insert(res.begin(),false);
       return res;
   } else {
       std::vector<bool> res = getKth(combinatrix,from-1,choose-1,k-combinatrix[from][choose]*(from-choose)/from);
       if(!res.empty())
           res.insert(res.begin(),true);
       return res;
   }
}

int main() {
   int n = 7;
   int m = 3;

   std::vector<std::vector<int>> combinatrix(n+1, std::vector<int>(m));
   for(auto &v: combinatrix)
       v[0] = 1;

   for(int from=1; from<combinatrix.size(); ++from)
       for(int choose=1; choose<=from; ++choose)
           combinatrix[from][choose] = combinatrix[from-1][choose]+combinatrix[from-1][choose-1];

   for(int k=0; k<combinatrix[n][m]; ++k) {
       std::vector<bool> combo = getKth(combinatrix, n, m, k);

       for(bool b: combo)
           std::cout << b << " ";
       std::cout << std::endl;
   }
   return 0;
}
