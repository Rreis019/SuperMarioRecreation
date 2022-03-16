#include "SaveSystem.h"
#include "Utils.h"
#include "Logger.h"
//mkdir
#include <direct.h>

SaveSystem saveSystem;

SaveSystem::SaveSystem()
{
    saveDirPath = getDocumentsPath() + SAVE_FOLDER_NAME + "\\";

    // Create save directory if it doesn't exist
    if (!fileExists(saveDirPath.c_str()))
    {
        if (mkdir(saveDirPath.c_str()) != 0){log("SaveSystem: Could not create save directory: %s\n", saveDirPath.c_str());}
    }
}
std::string SaveSystem::getPath(int index)
{
    std::string path = saveDirPath + "/Save" + std::to_string(index) + ".dat";

    // Create save directory if it doesn't exist
    if (!fileExists(saveDirPath.c_str()))
    {
        if (mkdir(saveDirPath.c_str()) != 0){log("SaveSystem: Could not create save directory: %s\n", saveDirPath.c_str());}
    }

    return path;
}
void SaveSystem::save(int index,SaveData data)
{
    FILE* file = fopen(getPath(index).c_str(), "wb");
    fwrite(&data, sizeof(SaveData), 1, file);
    fclose(file);
}
void SaveSystem::load(int index, SaveData& data)
{
    FILE* file = fopen(getPath(index).c_str(), "rb");
    fread(&data, sizeof(SaveData), 1, file);
    fclose(file);
}
void SaveSystem::del(int index)
{
    std::string path = getPath(index);
    remove(path.c_str());
    //std::string command = "del " + path;
    //system(command.c_str());
}
