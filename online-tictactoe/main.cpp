#include <windows.h>
#include <winsock2.h>

#include <iostream>

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
  // if (send(s, message, strlen(message), 0) < 0) {
  //   puts("Send failed");
  //   return 1;
  // }
  // // puts("Data Sent\n");

  // size = recv(s, buffer, sizeof(buffer), 0);
  // printf("Size: %d\t%s\n", size, buffer);
  char buffer[1024];
  int size = -1;
  for (int i = 0; i < 2; i++) {
    if (send(s, message, strlen(message), 0) < 0) {
      puts("Send failed");
      return 1;
    }
   
    size = recv(s, buffer, sizeof(buffer), 0);
    printf("Size: %d\t%s\n", size, buffer);
  }

  // while (size != 0) {
  // }
  // if (size == -1) {
  //   fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
  // }
  // std::cout << buffer << std::endl;

  closesocket(s);
  return 0;
}