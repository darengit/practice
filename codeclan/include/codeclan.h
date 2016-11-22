#ifndef CODE_CLAN_H
#define CODE_CLAN_H

#include <vector>
#include <string>

#include "clanmission.h"

class CodeClan {
public:
    int *gamestate;
    std::vector<std::pair<std::string,std::vector<ClanMission>>> missionsByCategory;
    std::string prompt;

    CodeClan(int *s, std::string missiondir);

    void loadmissions(std::string dir);
    void run();
    void categorymenu(std::vector<std::pair<std::string,std::vector<ClanMission>>> m);
    void missionmenu(std::vector<ClanMission> missons);
};
#endif
