#include <stdlib.h>

class ClanMission {
public:

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

            // dont concatenate, overwrite
            solutionfile << parsedmessage;
            // possibly flush
            solve();
        }

        cout << name << " Solved" << endl;
goback:
        gamestate[1] = -1;
        return;
    }

}

class CodeClan {
    int *gamestate;
    std::vector<std::pair<std::string,std::vector<ClanMission>>> missionsByCategory;

public:
    Game(int *s) gamestate(s) {
        loadmissions();
        prompt = "make selection: ";
    }

    void loadmissions() {

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




int main() {
    int state[2] = {-1, -1};

    CodeClan c(state);

    c.run();

    return 0;    
}
