#ifndef CLAN_MISSION_H
#define CLAN_MISSION_H
#include <string>

class ClanMission {
public:
    std::string dir;
    int *gamestate;
    std::string name;
    std::string missionstatement;
    std::string parsedmessage;
    std::pair<std::string, bool> (*parsefunc)(std::string);
    bool solved;

    ClanMission(std::string d, int *g, std::pair<std::string,bool>(*f)(std::string));
    std::string missionStatementFromDir(std::string dir);
    bool parse(std::string in);
    bool solve();
    void run();
};
#endif
