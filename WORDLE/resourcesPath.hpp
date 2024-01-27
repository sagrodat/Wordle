#pragma once
#include <Windows.h>
#include <iostream>
#include <cstring>
class ResourcesPath
{
public:
	ResourcesPath();
private:
	char path[MAX_PATH];
	DWORD length;
	void cutExecutableName();
	int backslashPos;
public:
	void printPath();
	std::string concatenate(const char* path);
};
inline ResourcesPath resourcesPath;
