#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <filesystem>
#include <sstream>
#include <fstream>

class ResourceManager
{
public:
	static std::string filePath;
	static std::string resourceIndexFileName;
	static std::unordered_map<unsigned int, std::string> idPathMap;

	static void Run();
	static void Reset();

	static inline std::string_view GetFilePath(unsigned int a_uniqueID) { return idPathMap[a_uniqueID]; }

private:
	static const std::string fileExtention;

	//static void createFile(const std::unordered_map<std::string, std::string>& resources);
	static void getResourceIndex(std::unordered_map<unsigned int, std::string>& a_uMap);
	static std::pair<unsigned int, std::string> fromMetaFile(std::istream& a_metaFile);
	static void toMetaFile(std::ostream& a_metaFile, const unsigned int a_id, std::string_view a_constName);
	static unsigned int findLowestUntaken(const std::vector<unsigned int>& a_takenSorted, unsigned int a_potentialUntaken = 0);
	static std::string toConstName(std::string_view a_fileName);
};


