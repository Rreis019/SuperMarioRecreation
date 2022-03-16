#include "Config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Logger.h"

char ServerIp[MAX_BUFFFER_CONFIG] =  "127.0.0.1";
char ServerPort[MAX_BUFFFER_CONFIG] = "8888";

void readServerIp(char* value) { strcpy(ServerIp, value); }
void readServerPort(char* value) { strcpy(ServerPort, value); }


#define FILE_VARS_COUNT 2
FileVar fileVars[FILE_VARS_COUNT] =
{
    {"ServerIp", readServerIp},
    {"ServerPort", readServerPort}
};


void readConfigFile()
{
    FILE* serverFile;
    fopen_s(&serverFile, "server.cfg", "r");
    if(serverFile == NULL)
    {
        log("[-] Failed to open server.cfg\n");
    }

    while (!feof(serverFile))
    {
        char line[256];
        fgets(line, 256, serverFile);
        char* command = strtok(line, "=");
        char* value =  strtok(NULL, "=");
        command = strtok(command, " ");
        value =  strtok(value, " ");
        if(value[strlen(value) - 1] == '\n'){value[strlen(value) - 1] = '\0';}

        for (int i = 0; i < FILE_VARS_COUNT; i++)
        {
            if (strcmp(fileVars[i].command, command) == 0){
                fileVars[i].readVar(value);
                break;
            }
        }
    }
    fclose(serverFile);

    log("ServerIp: %s\n", ServerIp);
    log("ServerPort: %s\n", ServerPort);
}

