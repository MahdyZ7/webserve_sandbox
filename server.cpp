# include "SevCli.hpp"

int main()
{
	std:: cout << AF_INET << std::endl;

	struct sockaddr_in address;
	const int PORT = 8080;

	memset((char*)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("cannot create socket");
		return 0;
	}
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		return 0;
	}
	if (listen(server_fd, 10) < 0)
	{
		perror("listen failed");
		return 0;
	}
	while (1)
	{
		std::cout << "Waiting for connection..." << std::endl;
		int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&address);
		if (new_socket < 0)
		{
			perror("accept failed");
			return 0;
		}

		std::cout << "Connection accepted" << std::endl;
		char buffer[3000] = {0};
		int valread = read(new_socket,buffer, 3000);
		std::cout << buffer << std::endl;
		send(new_socket, "Hello from server", strlen("Hello from server"), 0);
		std::cout << "Hello message sent" << std::endl;
		close(new_socket);
	}
	return 0;
}