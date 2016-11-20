#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

class ClanMission {
public:

    int *gamestate;
    std::string dir;
    std::string name;
    std::string solveerror;
    std::string parseerror;
    std::string missionstatement;
    std::string parsedmessage;
    std::pair<std::string, bool> (*parsefunc)(std::string);
    bool solved;

    ClanMission(std::string dir, int *gamestate, std::string (*f)(std::string()):
        dir(dir), gamestate(gamestate), parsefunc(f) {
        name = nameFromDir(dir);
        solveerror = "";
        parseerror = "";
        missionstatement = missionStatementFromDir(dir);
        parsedmessage = "";
        solved = false;
    }

    std::string nameFromDir(std::string dir) {
        return dir.substr(dir.find_last_of('/')+1);
    }

    std::string missionStatementFromDir(std::string dir) {
        std::ifstream ifs(dir + "/" + "statement.txt");
        std::string content( (std::istreambuf_iterator<char>(ifs) ),
            (std::istreambuf_iterator<char>()    ) );
        return content;
    }

    bool parse(std::string in) {
        std::pair<std::string, bool> parsed = parsefunc(in);
        if(parsed.second)
            parsedmessage = parsed.first;
        else
            parseerror = parsed.first;
        return parsed.second;
    }

    bool solve() {
        pid_t pid = fork();
        if(pid == 0) {
            execve("gcc", {"-Wall", "-std=c11", dir+"/problem.c", "-o "+dir+"/a.out", ">", dir+"/gcc.out", "2>&1"}, CodeClan.envp);

        } else if (pid > 0) {
            if(waitpid(pid)) {
                cout << "compilation error occured, example " << dir << "/gcc.out" << endl;
                return false;
            }
        }

        pid_t pid = fork();
        if(pid == 0) {
            execve("gcc", {"-Wall", "-std=c11", dir+"/problem.c", "-o "+dir+"/a.out", ">", dir+"/gcc.out", "2>&1"}, CodeClan.envp);
        } else if (pid > 0) {
            if(waitpid(pid)) {
                cout << "solution incorrect, examine " << dir << "/aout.out for clues" << endl;
                return false;
            }
        }

        return true;

    }

    void run() {
        solved = false;
        while(!solved) {
            cout << solveerror << endl;
            std::string input;
            while(!parse(input)) {
                cout << parseerror << endl;
                cout << "'b' to go back to categories" << endl;
                cout << missionstatement << endl;
                cout << ":";
                cin >> input;
                if(input=='b' || input=='B')
                    goto goback;
            }


            std::ofstream solutionfile(dir + "/solution.txt", std::ofstream::out|std::ofstream::trunc);
            // dont concatenate, overwrite
            solutionfile << parsedmessage;
            // possibly flush
            solutionfile.close();

            solved = solve();
        }

        cout << name << " Solved" << endl;
goback:
        gamestate[1] = -1;
        return;
    }

}

class CodeClan {
public:
    int *gamestate;
    std::vector<std::pair<std::string,std::vector<ClanMission>>> missionsByCategory;

    static char *const envp;

    Game(int *s): gamestate(s) {
        loadmissions("clanrepo");
        prompt = "make selection: ";
    }

    void loadmissions(std::string dir) {
        DIR *d;
struct dirent *ent;
if (d=opendir(dir.c_str())) {
  /* print all the files and directories within directory */
  while (ent=readdir(d)) {
    missionsByCategory.emplace_back(std::pair<std::string,std::vector<ClanMission>> (end->d_name, std::vector<ClanMission>{}));
  }
  closedir (dir);
} else {
  /* could not open directory */
  perror ("");
  return EXIT_FAILURE;
}

    for(std::pair<std::string,std::vector<ClanMission>> &p:missionsByCategory) {
         DIR *d;
struct dirent *ent;
if (d=opendir((dir+"/"+p.first).c_str())) {
  /* print all the files and directories within directory */
  while (ent=readdir(d)) {
    //missionsByCategory.emplace_back(std::pair<std::string,std::vector<ClanMission>> (end->d_name, std::vector<ClanMission>{}));
    p.second.emplace_back(ClanMission(end->d_name,gamestate,
        [](std::string s)->std::string {return s};
    // todo : fill in differentparsing func
  }
  closedir (dir);
} else {
  /* could not open directory */
  perror ("");
  return EXIT_FAILURE;
}
       
    }
    }

    void run() {
        while(gamestate[0] != -2) {
            if(gamestate[0] == -1)
                categorymenu(missionsByCategory);
            else if (gamestate[1] == -1)
                missionmenu(missionsByCategory[gamestate[0]].second);
            else
                missionsByCategory[gamestate[0]][gamestate[1]].run();
        }

        return 0;
    }

    void categorymenu(std::vector<std::pair<std::string,std::vector<ClanMission>>> m) {
        cout << "Categories" << endl;
        for(int i=0; i<m.size(); ++i)
            cout << std::string::to_string(i+1) << ". " << m[i].first << endl;
        cout << "q. quit" << endl;
        cout << prompt;

        std::string input;
        cin >> input;

        if(input=='q' || input=='Q') {
            gamestate[0] = -2;
            return;
        }

        int chosen = atoi(input.c_str());

        if(1<=chosen && chosen<=m.size())
            gamestate[0] = chosen-1;

        return;
    }

    void missionmenu(std::vector<ClanMission> missons) {
        cout << missionsByCategory[gamestate[0]].first << " Missions" << endl;
        for(int i=0; i<m.size(); ++i)
            cout << std::string::to_string(i+1) << ", " << missions[i].name << endl;
        cout << "b. back to categories" << endl;
        cout << "q. quit" << endl;
        cout << prompt;

        std::string input;
        cin >> input;

        if(input=='b' || input=='B') {
            gamestate[1] = -1;
            return;
        }

        if(input=='q' || input=='Q') {
            gamestate[0] = -2;
            return;
        }

        int chosen = atoi(input.c_str());

        if(1<=chosen && chosen<=m.size())
            gamestate[0] = chosen-1;

        return;
    }
}

int main(int argc, char *const argv, char *const envp) {
    int state[2] = {-1, -1};

    CodeClan c(state, envp);
    CodeClan.envp = envp;
    c.run();

    return 0;    
}
