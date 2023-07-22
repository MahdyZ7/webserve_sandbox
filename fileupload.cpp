#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

int main() {
  // Create a TCP socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    return 1;
  }

  // Set up the server address
  struct sockaddr_in serverAddr;
  memset((char*)&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(8080); // Replace with the appropriate port number
  if (inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr)) <= 0) {
    std::cerr << "Invalid address/Address not supported" << std::endl;
    return 1;
  }

  // Connect to the server
  if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
    std::cerr << "Failed to connect to server" << std::endl;
    return 1;
  }

  // Construct the HTTP request
  std::string request = "POST /upload HTTP/1.1\r\n"
                        "Host: example.com\r\n"
                        "Content-Type: multipart/form-data; boundary=---------------------------1234567890\r\n"
                        "Content-Length: 123\r\n"
                        "\r\n"
                        "-----------------------------1234567890\r\n"
                        "Content-Disposition: form-data; name=\"file\"; filename=\"file.jpg\"\r\n"
                        "Content-Type: image/jpeg\r\n"
                        "\r\n"
                        "File data goes here\r\n"
                        "-----------------------------1234567890--\r\n";

  // Send the request
  if (send(sockfd, request.c_str(), request.length(), 0) == -1) {
    std::cerr << "Failed to send request" << std::endl;
    return 1;
  }

  // Receive the response
  char buffer[4096];
  std::string response;
  while (true) {
    ssize_t bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) {
      std::cerr << "Failed to receive response" << std::endl;
      return 1;
    } else if (bytesRead == 0) {
      break; // Connection closed by the server
    } else {
      buffer[bytesRead] = '\0';
      response += buffer;
    }
  }

  // Print the response
  std::cout << response << std::endl;

  // Close the socket
  close(sockfd);

  return 0;
}
