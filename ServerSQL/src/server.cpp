#include "config.h"
#include "server.h"
#include <winsock.h>
#include <stdio.h>
#include <string>
#include "ScoreSave.h"



#define SOCKET_MAX_CONNECTIONS 10
bool serverIsRunning = true;
SOCKET socketServer;

bool initSocketServer()
{
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        printf("[-] WSAStartup failed with error: %d\n", err);
        return false;
    }

    socketServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketServer == INVALID_SOCKET)
    {
        printf("[-] socket() failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return false;
    }
    
    puts("[+] Socket created.");

    //bind address
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(ServerPort));
    addr.sin_addr.s_addr = inet_addr(ServerIp);
    if (bind(socketServer, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        printf("[-] bind() failed with error: %ld\n", WSAGetLastError());
        closesocket(socketServer);
        WSACleanup();
        return false;
    }

    printf("[+] Socket binded %s:%s.\n", ServerIp, ServerPort);

    //listen
    if (listen(socketServer, SOCKET_MAX_CONNECTIONS) == SOCKET_ERROR)
    {
        printf("[-] listen() failed with error: %ld\n", WSAGetLastError());
        closesocket(socketServer);
        WSACleanup();
        return false;
    }

    puts("[+] Socket listening.\n");
    return true;
}


void socketLoop()
{
    while (serverIsRunning)
    {
        SOCKET clientSocket = accept(socketServer, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {continue;}

        printf("[+] Client connected.\n");

        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        if(bytesReceived <= 0){continue;}


        if(bytesReceived > 0)
        {
            char* command = strtok(buffer, " ");
            if(EServerCommands_GetScore == atoi(command))
            {
                std::vector<ScoreSaveData> scores = std::vector<ScoreSaveData>();
                if(getScores(scores))
                {
                    printf("[+] Sending scores.\n");
                    
                    
                    std::string scoresString = "";
                    scoresString += std::to_string(scores.size()) + " ";
                    for (int i = 0; i < scores.size(); i++)
                    {
                        scoresString += scores[i].personName;
                        scoresString += " ";
                        scoresString += std::to_string(scores[i].score);
                        scoresString += " ";
                    }
                    send(clientSocket, scoresString.c_str(), scoresString.length() + 1, 0);
                    printf("[+] Scores sent.\n");
                    
                }
                else{
                    printf("[-] Error getting scores.\n");
                }
            }
            else if(EServerCommands_SendScore == atoi(command))
            {
                printf("[+] SendScore command received.\n");
                char* name = strtok(NULL, " ");
                char* score = strtok(NULL, " ");
                int scoreInt = atoi(score);
                char scoreName[32]; 
                strcpy(scoreName, name);

                if(addPerson(scoreName, scoreInt))
                {
                    char buffer[256];
                    sprintf(buffer, "Score added: %s %d", scoreName, scoreInt);
                    send(clientSocket, buffer, strlen(buffer), 0);
                }
                else{
                    char buffer[256];
                    sprintf(buffer, "Score not added: %s %d", scoreName, scoreInt);
                    send(clientSocket, buffer, strlen(buffer), 0);
                }
            }
        }
    }
}
