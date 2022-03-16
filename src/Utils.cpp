#include "Utils.h"
#include <fstream>
#include <algorithm>
#include <cmath>

bool fileExists(const char *fileName){
    std::ifstream infile(fileName);
    return infile.good();
}

bool getFileExtension(std::string FileName, std::string& extension)
{
    size_t index = FileName.find_last_of(".");

    //Não tem extensão
    if ((int)index == -1)
        return false;

    extension = FileName.substr(index + 1);
    return true;
}

std::string swapExtension(std::string FileName, std::string extension)
{
    int index = FileName.find_last_of(".") + 1;

    FileName.erase(index);
    FileName += extension;
    return FileName;
}

void strSplit(std::string str, std::string splitBy, std::vector<std::string>& tokens)
{
    size_t splitAt;
    size_t splitLen = splitBy.size();
    std::string frag;
    tokens.clear();
    tokens.push_back(str);

    while (true)
    {
        frag = tokens.back();

        splitAt = frag.find(splitBy);

        if ((int)splitAt == -1)
        {
            break;
        }

        tokens.back() = frag.substr(0, splitAt);
        tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
    }
}

std::string getDocumentsPath()
{
    std::string documentsPath;
    documentsPath = getenv("USERPROFILE");
    documentsPath += "\\Documents\\";
    return documentsPath;
}

void strRemoveChar(std::string& s1, char l)
{
    s1.erase(std::remove(s1.begin(), s1.end(), l), s1.end());
}

//function lerp because std::lerp is only implemented in c++20
float lerp(float start,float end,float percentage)
{
    if(percentage > 1)
        percentage = 1;
    
    if(percentage < 0)
        percentage = 0;

    return start + (end - start) * percentage;
}

int intLength(int n)
{
    if (n == 0) return 1;
    else if (n < 0) return 2 + static_cast<std::size_t>(std::log10(-n));
    else if (n > 0) return 1 + static_cast<std::size_t>(std::log10(n));
}