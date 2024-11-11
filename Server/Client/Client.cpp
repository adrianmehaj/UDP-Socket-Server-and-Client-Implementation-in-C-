#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>


#pragma comment(lib, "Ws2_32.lib") // Link with Winsock library

#define SERVER_IP "192.168.178.79" // Replace with your server's actual IP address
#define PORT 8080