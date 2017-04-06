#include <iostream>
#include <string>
#include <cmath>

void printDiamond(double h, double w) {
//    std::cout << std::string(std::round(w/2-0.5),' ') << std::string(1,'#') << std::endl;

    for(double i=0; i<h; ++i) {
        int side = std::round((w-1.0)/(h-1.0)*std::abs((h-1.0)/2-i));
        //int middle = std::max(w-2-2*side,0.0);
        int middle = w-2-2*side;

        std::cout << std::string(side,' ') << std::string(1,'#');
        if(middle>=0)
            std::cout << std::string(middle,' ') << std::string(1,'#');
        std::cout << std::endl;
    }

//    std::cout << std::string(std::round(w/2-0.5),' ') << std::string(1,'#') << std::endl;
}

int main() {
    int h=-1,w=-1;
    while(h<3 || w<2) {
        if(h>=0 || w>=0)
            std::cout << "height of at least 3 and width of at least 2 for output to make sense." << std::endl; 

        std::cout << "Enter height:";
        std::cin >> h;
        std::cout << "Enter width:";
        std::cin >> w;
    }

    std::cout << "Entered h=" << h << ", w=" << w << std::endl;

    printDiamond(h,w);
}
