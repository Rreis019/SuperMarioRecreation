#pragma once
typedef void(*ReadVar)(char* value);
struct FileVar
{
    char* command;
    ReadVar readVar;
};


#define MAX_BUFFFER_CONFIG 32
extern char ServerIp[MAX_BUFFFER_CONFIG];
extern char ServerPort[MAX_BUFFFER_CONFIG];
void readConfigFile();