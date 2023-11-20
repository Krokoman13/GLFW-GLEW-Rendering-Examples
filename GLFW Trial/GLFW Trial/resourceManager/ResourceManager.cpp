#include "ResourceManager.hpp"
#include <algorithm>
#include <cstring>

const std::string ResourceManager::fileExtention = "resc";
std::string ResourceManager::filePath = "Resources";
std::string ResourceManager::resourceIndexFileName = "resourceIndex.hpp";
std::unordered_map<unsigned int, std::string> ResourceManager::idPathMap;

void ResourceManager::Reset()
{
    std::ofstream resourceIndex(filePath + '/' + resourceIndexFileName);
    resourceIndex.close();

    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(filePath)) {
        if (!entry.is_regular_file()) continue;

        std::string filename = entry.path().filename().string();

        if (filename.find('.' + fileExtention) == std::string::npos) continue;
        std::remove(entry.path().string().data());
    }
}

void ResourceManager::Run()
{
    std::unordered_map<unsigned int, std::string> oldConstants;
    getResourceIndex(oldConstants);

    std::vector<unsigned int> taken;
    for (std::pair<unsigned int, std::string> it : oldConstants) {
        unsigned int key = it.first;
        taken.push_back(key);
    }

    std::sort(taken.begin(), taken.end());
    unsigned int lowestUntaken = findLowestUntaken(taken);

    std::unordered_map<unsigned int, std::string> newConstants;


    for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(filePath)) {
        if (!entry.is_regular_file()) continue;

        std::string filename = entry.path().filename().string();
        if (resourceIndexFileName == filename) continue;

        if (filename.find('.' + fileExtention) == std::string::npos) {  //If it is NOT a meta file
            std::string metaFilename = filename + '.' + fileExtention;
            std::filesystem::path metaPath = entry.path().parent_path() / metaFilename;
            if (std::filesystem::exists(metaPath)) continue;

            std::ofstream metaFile(metaPath);

            if (!metaFile.is_open()) continue;

            unsigned int uniqueID = lowestUntaken;
            taken.push_back(uniqueID);
            lowestUntaken = findLowestUntaken(taken, lowestUntaken + 1);

            std::string constantName = toConstName(filename);

            toMetaFile(metaFile, uniqueID, constantName);
            metaFile.close();

            idPathMap[uniqueID] = entry.path().string();
            newConstants[uniqueID] = "#define " + constantName;

            continue;
        }
        
        //if it is a meta file
        std::ifstream metaFile(entry.path());

        std::pair<unsigned int, std::string> file = fromMetaFile(metaFile);
        idPathMap[file.first] = entry.path().string();

        auto fileTag = oldConstants.find(file.first);
        if (fileTag != oldConstants.end()) {
            newConstants[file.first] = fileTag->second;
            continue;
        }

        newConstants[file.first] = file.second;
        idPathMap[file.first] = entry.path().string().substr(0, (fileExtention.size() + 2));
    }

    std::ofstream resourceIndex(filePath + '/' + resourceIndexFileName);

    if (!resourceIndex.is_open()) return;
    resourceIndex << "////////////////////////////////////////////////////////////////////" << std::endl;
    resourceIndex << "//    A file to keep track of all resources and their uniqueID's  //" << std::endl;
    resourceIndex << "////////////////////////////////////////////////////////////////////" << std::endl << std::endl;
    resourceIndex << "//The interger is the only value that matters, the comments refer to the last known path/name of the relevant file" << std::endl << std::endl;

    for (std::pair<unsigned int, std::string> it : newConstants) {
        resourceIndex << it.second << '\t' << it.first << "\t\t //" << idPathMap[it.first] << std::endl;
    }
    resourceIndex.close();
}

void ResourceManager::getResourceIndex(std::unordered_map<unsigned int, std::string>& a_uMap)
{
    std::ifstream ifs(filePath + '/' + resourceIndexFileName);

    if (ifs.bad()) return;

    std::string currentLine;

    while (std::getline(ifs, currentLine)) {
        std::stringstream ss(currentLine);
        std::string constName;    
        std::string uniqueID;

        std::getline(ss, constName, '\t');
        std::getline(ss, uniqueID, '\t');

        if (uniqueID == "") continue;

        unsigned int key = std::stoul(uniqueID, nullptr, 0);
        a_uMap[key] = constName;
    }

    ifs.close();
}

std::pair<unsigned int, std::string> ResourceManager::fromMetaFile(std::istream& a_metaFile)
{
    std::string firstLine;
    std::getline(a_metaFile, firstLine);

    unsigned int id = std::stoul(firstLine, nullptr, 0);

    std::string secondLIne;
    std::getline(a_metaFile, secondLIne);

    return std::pair<unsigned int, std::string>(id, secondLIne);
}

void ResourceManager::toMetaFile(std::ostream& a_metaFile, const unsigned int a_id, std::string_view a_constName)
{
    a_metaFile << a_id << std::endl;
    a_metaFile << a_constName << std::endl;
}

unsigned int ResourceManager::findLowestUntaken(const std::vector<unsigned int>& a_takenSorted, unsigned int a_potentialUntaken)
{
    if (a_takenSorted.size() <= a_potentialUntaken) return a_potentialUntaken;

    for (const unsigned int i : a_takenSorted) {
        if (a_potentialUntaken == i) a_potentialUntaken++;
    }

    return a_potentialUntaken;
}

std::string ResourceManager::toConstName(std::string_view a_fileName)
{
    std::string outp = "RS__";

    for (const char c : a_fileName)
    {
        if (c > 96 && c < 122) outp += (c - 32);
        else if (c > 31 && c < 47) outp += '_';
        else outp += c;
    }

    return outp;
}
