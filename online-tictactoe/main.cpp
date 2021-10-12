#include <iostream>
#include <winsock2.h>
#include <windows.h>

int main(int argc, char* argv[]) {
  WSADATA wsa;
  SOCKET s;
  struct sockaddr_in server;

  printf("\nInitialising Winsock...");
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    printf("Failed. Error Code : %d", WSAGetLastError());
    return 1;
  }

  printf("Initialised.\n");

  // Create a socket
  if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    printf("Could not create socket : %d", WSAGetLastError());
  }

  printf("Socket created.\n");

  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(8080);

  // Connect to remote server
  if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
    puts("connect error");
    return 1;
  }

  puts("Connected");

  const char* message = "JOIN 3333";
  char buffer[1024];
  int size = -1;

  if (send(s, message, strlen(message), 0) < 0) {
    printf("Send failed!\n");
    return 1;
  }

  size = recv(s, buffer, sizeof(buffer), 0);
  printf("Size: %d\t%s\n", size, buffer);

  closesocket(s);
  return 0;
}