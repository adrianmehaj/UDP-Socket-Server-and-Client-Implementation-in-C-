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
    if (hFind == INVALID_HANDLE_VALUE) {
        return "Error accessing project folder.\n";
    }
    else {
        do {
            std::string fileName = findFileData.cFileName;
            if (fileName != "." && fileName != "..") {
                fileList += fileName + "\n";
            }
        } while (FindNextFileA(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
    return fileList;
}

std::string readFileContents(const std::string& fileName) {
    std::string directoryPath = "C:\\Users\\Admin\\Desktop\\Detyra2\\" + fileName;
    std::ifstream file(directoryPath);
    if (!file.is_open()) {
        return "Error: Could not open file " + fileName + ".\n";
    }

    std::string content, line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    return content;
}

std::string addFile(const std::string& fileName, const std::string& content) {
    std::string directoryPath = "C:\\Users\\Admin\\Desktop\\Detyra2\\" + fileName;
    std::ofstream file(directoryPath);
    if (!file.is_open()) {
        return "Error: Could not create file " + fileName + ".\n";
    }
    file << content;
    file.close();
    return "File " + fileName + " created successfully.\n";
}

std::string editFile(const std::string& fileName, const std::string& content) {
    return addFile(fileName, content); // Reuse addFile to overwrite
}

std::string deleteFile(const std::string& fileName) {
    std::string directoryPath = "C:\\Users\\Admin\\Desktop\\Detyra2\\" + fileName;
    if (DeleteFileA(directoryPath.c_str())) {
        return "File " + fileName + " deleted successfully.\n";
    }
    else {
        return "Error: Could not delete file " + fileName + ".\n";
    }
}

void handleClientRequest(SOCKET serverSocket, sockaddr_in clientAddr, int addrLen, const std::string& clientMessage) {
    char clientIpStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIpStr, INET_ADDRSTRLEN);
    std::string clientIp(clientIpStr);

    if (clients.find(clientIp) == clients.end()) {
        clients[clientIp] = clientAddr; // Register new client
        if (fullAccessClientIp.empty()) {
            fullAccessClientIp = clientIp; // First client gets full access
            std::cout << "Client " << clientIp << " granted full access.\n";
        }
    }

    std::string response;
    if (clientIp == fullAccessClientIp) {
        // Handle commands for the full-access client
        if (clientMessage == "LIST_FILES") {
            response = listFilesInDirectory();
        }
        else if (clientMessage.rfind("READ_FILE ", 0) == 0) {
            std::string fileName = clientMessage.substr(10);
            response = readFileContents(fileName);
        }
        else if (clientMessage.rfind("ADD_FILE ", 0) == 0) {
            size_t pos = clientMessage.find(' ', 9);
            std::string fileName = clientMessage.substr(9, pos - 9);
            std::string content = clientMessage.substr(pos + 1);
            response = addFile(fileName, content);
        }
        else if (clientMessage.rfind("EDIT_FILE ", 0) == 0) {
            size_t pos = clientMessage.find(' ', 10);
            std::string fileName = clientMessage.substr(10, pos - 10);
            std::string content = clientMessage.substr(pos + 1);
            response = editFile(fileName, content);
        }
        else if (clientMessage.rfind("DELETE_FILE ", 0) == 0) {
            std::string fileName = clientMessage.substr(12);
            response = deleteFile(fileName);
        }
        else {
            response = "Invalid command.\n";
        }
    }
    else if (clientMessage == "LIST_FILES" || clientMessage.rfind("READ_FILE ", 0) == 0) {
        // Handle commands for read-only clients
        if (clientMessage == "LIST_FILES") {
            response = listFilesInDirectory();
        }
        else if (clientMessage.rfind("READ_FILE ", 0) == 0) {
            std::string fileName = clientMessage.substr(10);
            response = readFileContents(fileName);
        }
    }
    else {
        response = "Access Denied: Full access is granted to another client.\n";
    }

    int bytesSent = sendto(serverSocket, response.c_str(), response.size(), 0, (struct sockaddr*)&clientAddr, addrLen);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Error sending response to client.\n";
    }
}