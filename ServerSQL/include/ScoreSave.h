#pragma once
#include <mysql.h>
#include <vector>

struct ScoreSaveData
{
    char* personName;
    int score;
};

void printScore(ScoreSaveData& scoreData);

void initMysql();
bool addPerson(char* personName,int score);
bool getScores(std::vector<ScoreSaveData>& scores);