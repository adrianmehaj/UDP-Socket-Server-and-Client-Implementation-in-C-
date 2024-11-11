#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>


#pragma comment(lib, "Ws2_32.lib") // Link with Winsock library

#define SERVER_IP "192.168.178.79" // Replace with your server's actual IP address
#define PORT 8080


void sendMessage(SOCKET sockfd, sockaddr_in& serverAddr, const std::string& message) {
    int sentBytes = sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (sentBytes == SOCKET_ERROR) {
        std::cerr << "Failed to send message.\n";
        return;
    }

    char buffer[1024];
    int addrLen = sizeof(serverAddr);
    int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&serverAddr, &addrLen);
    if (n == SOCKET_ERROR) {
        std::cerr << "Failed to receive server response.\n";
        return;
    }

buffer[n] = '\0';
std::cout << "Server response: " << buffer << std::endl;
}
int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }
