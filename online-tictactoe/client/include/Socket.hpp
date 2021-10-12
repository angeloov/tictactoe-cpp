#pragma once
#include <iostream>
#include <winsock2.h>
#include <windows.h>

class Socket {
 public:
  WSADATA wsa;
  SOCKET s;
  struct sockaddr_in server;

  Socket();
  ~Socket();
  bool sendToServer(std::string msg);
  std::string receiveFromServer();
};