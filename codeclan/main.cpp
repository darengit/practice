#include "codeclan.h"

int main() {
    int state[2] = {-1, -1};

    CodeClan c(state, "clanrepo");
    c.run();

    return 0;    
}
