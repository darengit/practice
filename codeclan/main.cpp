#include "codeclan.h"

int main(int argc, char *argv[]) {
    int state[2] = {-1, -1};
    CodeClan c(state, (argc>1)?argv[1]:"clanrepo");
    c.run();
    return 0;    
}
