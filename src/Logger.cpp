#include "Logger.h"
#include <stdio.h>
#include <Windows.h>

//#define DEBUG_MODE

void initLogger()
{
    #ifdef DEBUG_MODE
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
    #else
        FreeConsole();
    #endif
}

void log(const char* format, ...)
{
    #ifdef DEBUG_MODE
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    #endif
}

void log(bool condition,char* filename,int line, const char* format, ...)
{
    #ifdef DEBUG_MODE
        if(!condition)
        {
            //messageBox using va_start and va_end
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            //add filename and line number
            printf(" %s:%d\n",filename,line);
            va_end(args);
        }
    #endif
}