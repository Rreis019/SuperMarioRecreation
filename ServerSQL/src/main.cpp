#include "Server.h"
#include "ScoreSave.h"
#include "config.h"
#include <stdio.h>

int main()
{
    readConfigFile();
    initMysql();
    initSocketServer();
    socketLoop();
    getchar();
    return 0;
}