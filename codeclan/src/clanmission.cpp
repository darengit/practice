#include <unistd.h>
#include <sys/wait.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "clanmission.h"
#include "clanutils.h"

ClanMission::ClanMission(std::string d, int *g, std::pair<std::string,bool>(*f)(std::string)):
    dir{d}, gamestate{g}, parsefunc{f} {
    name = codeclan::nameFromDir(d);
    missionstatement = missionStatementFromDir(d);
    parsedmessage = "";
    solved = false;
}

std::string ClanMission::missionStatementFromDir(std::string dir) {
    std::ifstream ifs(dir + "/" + "statement.txt");
    std::string content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
    return content;
}

bool ClanMission::parse(std::string in) {
    std::pair<std::string, bool> parsed = parsefunc(in);
    parsedmessage = parsed.first;
    return parsed.second;
}

bool ClanMission::solve() {
    pid_t pid = fork();
    if(pid == 0) {
        chdir(dir.c_str());
        const char *const argv[] = {"gcc", "-Wall", "-std=c11", "problem.c", NULL};
        int err = execvp("gcc", const_cast<char *const *>(argv));
        perror("execve returned with error");
        exit(err);
    } else if (pid > 0) {
        int status;
        if(waitpid(pid, &status, 0)==pid && status) {
            std::cout << "compilation error occured" << std::endl;
            return false;
        }
    }

    pid = fork();
    if(pid == 0) {
        chdir(dir.c_str());
        const char *const argv[] = {"a.out", NULL};
        int err = execvp("./a.out", const_cast<char *const *>(argv));
        perror("execve returned with error");
        exit(err);
    } else if (pid > 0) {
        int status;
        if(waitpid(pid, &status, 0)==pid && status) {
            std::cout << "runtime error occured or solution incorrect" << std::endl;
            return false;
        }
    }
    return true;
}

void ClanMission::run() {
    solved = false;
    while(!solved) {
        std::string input;
        do {
            std::cout << "'b' to go back to missions" << std::endl;
            std::cout << "'q' or 'quit' to quit" << std::endl;
            std::cout << missionstatement << std::endl;
            std::cout << ":";
            std::getline(std::cin, input);
            std::cout << "your input : " << input << std::endl;

            if(input=="b" || input=="back")
                goto goback;
            else if(input=="q" || input=="quit") {
                gamestate[0] = -2;
                goto goback;
            }
        } while(!parse(input));

        std::ofstream solutionfile(dir + "/solution.txt", std::ofstream::out|std::ofstream::trunc);
        solutionfile << parsedmessage;
        solutionfile.close();

        solved = solve();

        if(!solved)
            std::cout << "incorrect, try again" << std::endl;
        else
            std::cout << name << " solved!" << std::endl;
        std::cout << std::endl;
    }

goback:
    gamestate[1] = -1;
    return;
}

