enum EServerCommands
{
    EServerCommands_None = -1,
    EServerCommands_SendScore,
    EServerCommands_GetScore
};


void socketLoop();
bool initSocketServer();