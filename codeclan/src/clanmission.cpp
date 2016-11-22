#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

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
    std::string content((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
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
        chdir(dir.c_str());
        const char *const argv[] = {"gcc", "-Wall", "-std=c11", "problem.c", NULL};
        int err = execvp("gcc", const_cast<char *const *>(argv));
        perror("execve returned with error");
        exit(err);
    } else if (pid > 0) {
        int status;
        if(waitpid(pid, &status, 0)==pid && status) {
            std::cout << "compilation error occured, examine " << dir << "/gcc.out" << std::endl;
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
        do {
            std::cout << parseerror << std::endl;
            std::cout << "'b' to go back to missions" << std::endl;
            std::cout << "'q' or 'quit' to quit" << std::endl;
            std::cout << missionstatement << std::endl;
            std::cout << ":";
            std::cin >> input;
            if(input=="b" || input=="back")
                goto goback;
            else if(input=="q" || input=="quit") {
                gamestate[0] = -2;
                goto goback;
            }
        } while(!parse(input));


        std::ofstream solutionfile(dir + "/solution.txt", std::ofstream::out|std::ofstream::trunc);
        // dont concatenate, overwrite
        solutionfile << parsedmessage;
        // possibly flush
        solutionfile.close();

        solved = solve();
    }

goback:
    gamestate[1] = -1;
    return;
}

