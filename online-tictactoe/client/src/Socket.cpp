#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include "Socket.hpp"

Socket::Socket() {
  // Initialize
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    printf("Failed. Error Code : %d", WSAGetLastError());
    exit(1);
  }

  // Create socket
  if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    printf("Could not create socket : %d", WSAGetLastError());
    exit(1);
  }

  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(8080);

  // Connect to remote server
  if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
    puts("connect error");
    exit(1);
  }
}

Socket::~Socket() {
  closesocket(s);
}

bool Socket::sendToServer(std::string msg) {
  const char* message = "CREATEROOM"; //msg.c_str();

  if (send(s, message, strlen(message), 0) < 0) {
    printf("Send failed!\n");
    return false;
  }

  return true;
}

std::string Socket::receiveFromServer() {
  char buffer[1024];
  recv(s, buffer, sizeof(buffer), 0);

  std::string msg(buffer);
  return msg;
}
