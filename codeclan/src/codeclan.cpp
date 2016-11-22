#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "codeclan.h"
#include "clanmission.h"

CodeClan::CodeClan(int *s, std::string mdir): gamestate{s} {
    loadmissions(mdir);
    prompt = "make selection: ";
}

void CodeClan::loadmissions(std::string dir) {
    DIR *d;
    struct dirent *drt;
    if ((d=opendir(dir.c_str()))) {
        while ((drt=readdir(d))) {
            if(drt->d_type==DT_DIR && strcmp(drt->d_name,".") && strcmp(drt->d_name,".."))
            missionsByCategory.emplace_back(std::pair<std::string,std::vector<ClanMission>> (drt->d_name, std::vector<ClanMission>{}));
        }
        closedir(d);
    }

    for(std::pair<std::string,std::vector<ClanMission>> &p:missionsByCategory) {
        DIR *d;
        struct dirent *drt;
        if ((d=opendir((dir+"/"+p.first).c_str()))) {
            while ((drt=readdir(d))) {
                if(drt->d_type==DT_DIR && strcmp(drt->d_name,".") && strcmp(drt->d_name,".."))
                    p.second.emplace_back(ClanMission(dir+"/"+p.first+"/"+drt->d_name,gamestate,
                        [](std::string s)->std::pair<std::string,bool> {return std::pair<std::string,bool>{s,true};}));
            }
            closedir(d);
        }
   
    }
}

void CodeClan::run() {
    while(gamestate[0] != -2) {
        if(gamestate[0] == -1)
            categorymenu(missionsByCategory);
        else if (gamestate[1] == -1)
            missionmenu(missionsByCategory[gamestate[0]].second);
        else
            missionsByCategory[gamestate[0]].second[gamestate[1]].run();
    }

    return;
}

void CodeClan::categorymenu(std::vector<std::pair<std::string,std::vector<ClanMission>>> m) {
    std::cout << "Categories" << std::endl;
    for(int i=0; i<(int)m.size(); ++i)
        std::cout << std::to_string(i+1) << ". " << m[i].first << std::endl;
    std::cout << "q. quit" << std::endl;
    std::cout << prompt;

    std::string input;
    std::cin >> input;

    if(input=="q" || input=="quit") {
        gamestate[0] = -2;
    } else {
        int chosen = atoi(input.c_str());
        if(1<=chosen && chosen<=(int)m.size())
            gamestate[0] = chosen-1;
    }
    return;
}

void CodeClan::missionmenu(std::vector<ClanMission> missions) {
    std::cout << missionsByCategory[gamestate[0]].first << " Missions" << std::endl;
    for(int i=0; i<(int)missions.size(); ++i)
        std::cout << std::to_string(i+1) << ", " << missions[i].name << std::endl;
    std::cout << "b. back to categories" << std::endl;
    std::cout << "q. quit" << std::endl;
    std::cout << prompt;

    std::string input;
    std::cin >> input;

    if(input=="b" || input=="back") {
        gamestate[0] = -1;
    } else if(input=="q" || input=="quit") {
        gamestate[0] = -2;
    } else {
        int chosen = atoi(input.c_str());
        if(1<=chosen && chosen<=(int)missions.size())
            gamestate[1] = chosen-1;
    }
    return;
}

