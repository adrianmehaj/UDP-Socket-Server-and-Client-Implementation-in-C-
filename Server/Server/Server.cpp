#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <fstream>
#include <unordered_map>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080

std::unordered_map<std::string, sockaddr_in> clients;
std::string fullAccessClientIp; // IP address of the client with full access

std::string listFilesInDirectory() {
    std::string directoryPath = "C:\\Users\\Admin\\Desktop\\Detyra";
    std::string fileList = "Files in project folder:\n";
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind;

    std::string searchPath = directoryPath + "\\*";
    hFind = FindFirstFileA(searchPath.c_str(), &findFileData);