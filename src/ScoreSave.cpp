#include "Utils.h"
#include "ScoreSave.h"
#include "SaveSystem.h"
#include <algorithm>
#include "Logger.h"
#include "Config.h"



ScoreSave scoreSave;

std::vector<ScoreSaveData> ScoreSave::saveLocal(char* personName, int score)
{
    std::string path = getDocumentsPath() + SAVE_FOLDER_NAME + "\\" + SCORE_SAVE_FILENAME;
    FILE* readFile = fopen(path.c_str(), "rb");

    std::vector<ScoreSaveData> scores = std::vector<ScoreSaveData>();
    if(readFile == NULL)
    {
        fclose(readFile);
        FILE* writeFile = fopen(path.c_str(), "wb");

        //se nao existir o arquivo, cria-se um novo ficheiro
        scores.push_back({personName, score});
        for(int i = 0;i < 7;i++){scores.push_back({"NULL",-1});}

        for(int i = 0; i < 8;i++)
        {
            int len =  strlen(scores[i].personName);
            fwrite(&len, sizeof(int), 1, writeFile);
            fwrite(scores[i].personName, sizeof(char), len, writeFile);
            fwrite(&scores[i].score, sizeof(int), 1, writeFile);
        }

        fclose(writeFile);
        return scores;
    }

    for(int i = 0; i < 8;i++)    //caso exista ler scores do ficheiro 
    {
        int len;
        int score;
        fread(&len, sizeof(int), 1, readFile);
        char* name = new char[len];
        fread(name, sizeof(char), len, readFile);
        fread(&score, sizeof(int), 1, readFile);
        scores.push_back({name, score});
    }
    fclose(readFile);
    scores.push_back({personName, score});    //adionar novo score
    std::sort(scores.begin(), scores.end(), [](ScoreSaveData a, ScoreSaveData b){return a.score > b.score;});    //ordenar os scores
    scores.pop_back();    //remove ultimo
    FILE* writeFile = fopen(path.c_str(), "wb");
    for(int i = 0; i < 8;i++)
    {
        int len =  strlen(scores[i].personName) +1;
        fwrite(&len, sizeof(int), 1, writeFile);
        fwrite(scores[i].personName, sizeof(char), len, writeFile);
        fwrite(&scores[i].score, sizeof(int), 1, writeFile);
    }
    fclose(writeFile);

    return scores;
}

std::vector<ScoreSaveData> ScoreSave::loadLocal()
{
    std::string path = getDocumentsPath() + SAVE_FOLDER_NAME + "\\" + SCORE_SAVE_FILENAME;
    log("path: %s\n", path.c_str());

    std::vector<ScoreSaveData> scores = std::vector<ScoreSaveData>();
    FILE* file = fopen(path.c_str(), "rb");

    if (file == NULL){return scores;}

    for (int i = 0; i < 8; i++)
    {
        ScoreSaveData data;
        int nameLength;
        fread(&nameLength, sizeof(int), 1, file);
        data.personName = new char[nameLength + 1];
        fread(data.personName, sizeof(char), nameLength, file);
        data.personName[nameLength] = '\0';
        fread(&data.score, sizeof(int), 1, file);
        scores.push_back(data);
        std::transform(data.personName, data.personName + nameLength, data.personName, ::toupper);//uppercase personName
        
    }
    fclose(file);
    return scores;
}





void ScoreSave::init()
{
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    if (WSAStartup(wVersionRequested, &wsaData) != 0)
    {
        printf("[-] WSAStartup failed with error: %d\n", WSAGetLastError());
        getchar();
        WSACleanup();
        exit(1);
    }
    readConfigFile();
}

bool ScoreSave::connectServer()
{
    // Create a socket
    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET)
    {
        printf("[-] Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return false;
    }


    u_short port = (u_short)atoi(ServerPort);
    // Connect to server
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(ServerIp);
    clientService.sin_port = htons(port);

    if (connect(connectSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        printf("[-] Failed to connect. Error code: %ld\n", WSAGetLastError());
        closesocket(connectSocket);
        WSACleanup();
        return false;
    }
    return true;
}


bool ScoreSave::saveOnline(char* personName,int score)
{
    if(!connectServer()){return false;}
    char sendBuffer[256];
    sprintf_s(sendBuffer, "%d %s %d ", EServerCommands_SendScore, personName, score);
    send(connectSocket, sendBuffer, strlen(sendBuffer), 0);
    closesocket(connectSocket);
     return true;
}
bool ScoreSave::loadOnline(std::vector<ScoreSaveData>& scores)
{
    if(!connectServer()){return false;}
    char sendBuffer[50];
    sprintf_s(sendBuffer, "%d", EServerCommands_GetScore);
    send(connectSocket, sendBuffer, strlen(sendBuffer) + 1, 0);
    char recvbuf[1024];
    int iResult = recv(connectSocket, recvbuf, 1024, 0);
    if(iResult <= 0){return false;}
    int ScoreNum = atoi(strtok(recvbuf, " ")); 
    for (int i = 0; i < ScoreNum; i++)
    {
        ScoreSaveData data;
        char* temp =  strtok(NULL, " ");
        data.personName = new char[strlen(temp) + 1];
        strcpy_s(data.personName, strlen(temp) + 1, temp);
        data.score = atoi(strtok(NULL, " "));
        scores.push_back(data);
    }
    closesocket(connectSocket);
    return true;
}
