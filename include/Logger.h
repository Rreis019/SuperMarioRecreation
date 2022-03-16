#pragma once

void initLogger();
void log(const char* format, ...);
void log(bool condition,char* filename,int line, const char* format, ...);