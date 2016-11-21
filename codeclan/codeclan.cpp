#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace codeclan {
    char *const *envp;
}

class ClanMission {
public:
    std::string dir;
    int *gamestate;
    std::string name;
    std::string solveerror;
    std::string parseerror;
    std::string missionstatement;
    std::string parsedmessage;
    std::pair<std::string, bool> (*parsefunc)(std::string);
    bool solved;

    ClanMission(std::string d, int *g, std::pair<std::string,bool>(*f)(std::string));

    std::string nameFromDir(std::string dir);

    std::string missionStatementFromDir(std::string dir);

    bool parse(std::string in);

    bool solve();

    void run();
};


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


    ClanMission::ClanMission(std::string d, int *g, std::pair<std::string,bool>(*f)(std::string)):
        dir{d}, gamestate{g}, parsefunc{f} {
        name = nameFromDir(d);
        solveerror = "";
        parseerror = "";
        missionstatement = missionStatementFromDir(d);
        parsedmessage = "";
        solved = false;
    }

    std::string ClanMission::nameFromDir(std::string dir) {
        return dir.substr(dir.find_last_of('/')+1);
    }

    std::string ClanMission::missionStatementFromDir(std::string dir) {
        std::ifstream ifs(dir + "/" + "statement.txt");
        std::string content( (std::istreambuf_iterator<char>(ifs) ),
            (std::istreambuf_iterator<char>()    ) );
        return content;
    }

    bool ClanMission::parse(std::string in) {
        std::pair<std::string, bool> parsed = parsefunc(in);
        if(parsed.second)
            parsedmessage = parsed.first;
        else
            parseerror = parsed.first;
        return parsed.second;
    }

    bool ClanMission::solve() {
        pid_t pid = fork();
        if(pid == 0) {
            const char *const argv[] = {"-Wall", "-std=c11", (dir+"/problem.c").c_str(), "-o", (dir+"/a.out").c_str(), ">", (dir+"/gcc.out").c_str(), "2>&1"};
            execve("gcc", const_cast<char *const *>(argv), codeclan::envp);

        } else if (pid > 0) {
            int status;
            if(waitpid(pid, &status, 0)==pid && status) {
                std::cout << "compilation error occured, example " << dir << "/gcc.out" << std::endl;
                return false;
            }
        }

        pid = fork();
        if(pid == 0) {
            execve("bin/a.out", (char *const[]){}, codeclan::envp);
        } else if (pid > 0) {
            int status;
            if(waitpid(pid, &status, 0)==pid && status) {
                std::cout << "solution incorrect, examine " << dir << "/aout.out for clues" << std::endl;
                return false;
            }
        }

        return true;

    }

    void ClanMission::run() {
        solved = false;
        while(!solved) {
            std::cout << solveerror << std::endl;
            std::string input;
            while(!parse(input)) {
                std::cout << parseerror << std::endl;
                std::cout << "'b' to go back to categories" << std::endl;
                std::cout << missionstatement << std::endl;
                std::cout << ":";
                std::cin >> input;
                if(input=="b" || input=="B")
                    goto goback;
            }


            std::ofstream solutionfile(dir + "/solution.txt", std::ofstream::out|std::ofstream::trunc);
            // dont concatenate, overwrite
            solutionfile << parsedmessage;
            // possibly flush
            solutionfile.close();

            solved = solve();
        }

        std::cout << name << " Solved" << std::endl;
goback:
        gamestate[1] = -1;
        return;
    }

    CodeClan::CodeClan(int *s, std::string mdir): gamestate{s} {
        loadmissions(mdir);
        prompt = "make selection: ";
    }

    void CodeClan::loadmissions(std::string dir) {
        DIR *d;
struct dirent *drt;
if ((d=opendir(dir.c_str()))) {
  /* print all the files and directories within directory */
  while ((drt=readdir(d))) {
    missionsByCategory.emplace_back(std::pair<std::string,std::vector<ClanMission>> (drt->d_name, std::vector<ClanMission>{}));
  }
  closedir(d);
}

    for(std::pair<std::string,std::vector<ClanMission>> &p:missionsByCategory) {
         DIR *d;
struct dirent *drt;
if ((d=opendir((dir+"/"+p.first).c_str()))) {
  /* print all the files and directories within directory */
  while ((drt=readdir(d))) {
    //missionsByCategory.emplace_back(std::pair<std::string,std::vector<ClanMission>> (end->d_name, std::vector<ClanMission>{}));
    p.second.emplace_back(ClanMission(drt->d_name,gamestate,
        [](std::string s)->std::pair<std::string,bool> {return std::pair<std::string,bool>{s,true};}));
    // todo : fill in differentparsing func
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

        if(input=="q" || input=="Q") {
            gamestate[0] = -2;
            return;
        }

        int chosen = atoi(input.c_str());

        if(1<=chosen && chosen<=(int)m.size())
            gamestate[0] = chosen-1;

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

        if(input=="b" || input=="B") {
            gamestate[1] = -1;
            return;
        }

        if(input=="q" || input=="Q") {
            gamestate[0] = -2;
            return;
        }

        int chosen = atoi(input.c_str());

        if(1<=chosen && chosen<=(int)missions.size())
            gamestate[0] = chosen-1;

        return;
    }




int main(int argc, char *const *argv, char *const *envp) {
    codeclan::envp = envp;
    int state[2] = {-1, -1};

    CodeClan c(state, "clanrepo");
    c.run();

    return 0;    
}
