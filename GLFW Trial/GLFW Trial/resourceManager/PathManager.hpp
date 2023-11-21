#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <filesystem>
#include <fstream>

class PathManager
{
public:
	static std::string resourceIndexFilePath;
	static std::string resourceIndexFileName;

	static void MapPaths();
	static void ResetPaths();

	static inline const std::string& GetFilePath(unsigned int a_uniqueID) { return m_idPathMap[a_uniqueID]; }

private:
	static std::unordered_map<unsigned int, std::string> m_idPathMap;

	static const std::string m_fileExtention;

	static void getResourceIndex(std::unordered_map<unsigned int, std::string>& a_uMap);
	static std::pair<unsigned int, std::string> fromMetaFile(std::istream& a_metaFile);
	static void toMetaFile(std::ostream& a_metaFile, const unsigned int a_id, std::string_view a_constName);
	static unsigned int findLowestUntaken(const std::vector<unsigned int>& a_takenSorted, unsigned int a_potentialUntaken = 0);
	static std::string toConstName(std::string_view a_fileName);
};


