#pragma once
#include <string>
#include <vector>

bool fileExists(const char *fileName);
bool getFileExtension(std::string FileName, std::string& extension); // get file extension
std::string swapExtension(std::string FileName, std::string extension);
void strSplit(std::string str, std::string splitBy, std::vector<std::string>& tokens);
std::string getDocumentsPath();
void strRemoveChar(std::string& s1, char l);
float lerp(float start,float end,float percentage);
int intLength(int n);