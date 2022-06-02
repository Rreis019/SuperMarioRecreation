#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ServerIp[MAX_BUFFFER_CONFIG] =  "127.0.0.1";
char ServerPort[MAX_BUFFFER_CONFIG] = "8888";
char DatabaseIp[MAX_BUFFFER_CONFIG] = "127.0.0.1";
char DatabaseUser[MAX_BUFFFER_CONFIG] = "root";
char DatabasePassword[MAX_BUFFFER_CONFIG] = "";
char DatabasePort[MAX_BUFFFER_CONFIG] = "3306";
char DatabaseName[MAX_BUFFFER_CONFIG] = "teste";


void readServerIp(char* value) { strcpy(ServerIp, value); }
void readServerPort(char* value) { strcpy(ServerPort, value); }
void readDatabaseIp(char* value) { strcpy(DatabaseIp, value); }
void readDatabaseUser(char* value) { strcpy(DatabaseUser, value); }
void readDatabasePassword(char* value) { strcpy(DatabasePassword, value); }
void readDatabasePort(char* value) { strcpy(DatabasePort, value); }
void readDatabaseName(char* value) { strcpy(DatabaseName, value); }

#define FILE_VARS_COUNT 7
FileVar fileVars[FILE_VARS_COUNT] =
{
    {"ServerIp", readServerIp},
    {"ServerPort", readServerPort},
    {"DatabaseIp", readDatabaseIp},
    {"DatabaseUser", readDatabaseUser},
    {"DatabasePassword", readDatabasePassword},
    {"DatabasePort", readDatabasePort},
    {"DatabaseName", readDatabaseName}
};

void readConfigFile()
{
    FILE* serverFile;
    fopen_s(&serverFile, "server.cfg", "r");
    if(serverFile == NULL)
    {
        printf("[-] Failed to open server.cfg\n");
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
}

