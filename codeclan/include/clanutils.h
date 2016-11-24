#ifndef CLAN_UTILS_H
#define CLAN_UTILS_H

#include <string>

namespace codeclan {

    inline void toupper(char &c) {
        if(c>='a' && c<='z') c += 'A'-'a';
    }

    inline std::string nameFromDir(std::string dir) {
        std::string ret = dir.substr(dir.find_last_of('/')+1);
        codeclan::toupper(ret[0]);

        for(int i=1; i<(int)ret.size(); ++i) {
            if(ret[i-1]=='_') {
                ret[i-1] = ' ';
                codeclan::toupper(ret[i]);
            }
        }

        return ret;
    }
}

#endif
