#include <string>
#include <vector>
#include <winsock.h>
//Class for saving score locally

#define SCORE_SAVE_FILENAME "ScoreSave.dat" 

struct ScoreSaveData{
    char* personName;
    int score;
};

enum EServerCommands
{
    EServerCommands_None = -1,
    EServerCommands_SendScore,
    EServerCommands_GetScore
};




class ScoreSave
{
    public:
        std::vector<ScoreSaveData> saveLocal(char* personName, int score);
        std::vector<ScoreSaveData> loadLocal();
        bool loadOnline(std::vector<ScoreSaveData>& scores);
        bool saveOnline(char* personName, int score);
        void init();

    private:
        bool connectServer();
        SOCKET connectSocket;
};

extern ScoreSave scoreSave;