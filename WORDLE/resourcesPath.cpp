#include "ResourcesPath.hpp"

ResourcesPath::ResourcesPath()
{
	DWORD length = GetModuleFileNameA(NULL, path, MAX_PATH);
	cutExecutableName();
}

void ResourcesPath::cutExecutableName()
{
	int i = MAX_PATH - 1;
	while (i >= 0 && path[i] != '\\') {
		path[i] = '\0';
		i--;
	}
	const char* resourcesFolder = "resources\\";
	int at = 0;
	while (resourcesFolder[at] != '\0')
	{
		path[++i] = resourcesFolder[at++];
	}
	backslashPos = i;
}
std::string ResourcesPath::concatenate(const char* toAdd)
{
	int pathCopyAt = backslashPos + 1;
	char pathCopy[MAX_PATH] = { '\0' };
	strcpy_s(pathCopy, path);
	int toAddAt = 0;
	while (toAdd[toAddAt] != '\0')
	{
		pathCopy[pathCopyAt++] = toAdd[toAddAt++];
	}
	std::string toReturn(pathCopy);
	return toReturn;
}

void ResourcesPath::printPath()
{
	for (int i = 0; i < MAX_PATH; i++)
	{
		std::cout << path[i];
	}
}
