#include "SevCli.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw std::runtime_error("Wrong number of arguments");

		struct sockaddr_in server_address;

		int server_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (server_fd < 0)
		{
			perror("cannot create socket");
			return 0;
		}

		memset((char*)&server_address, 0, sizeof(server_address));
		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(std::atoi(av[1]));
		if (inet_pton(AF_INET,"127.0.0.1", &server_address.sin_addr) <= 0)
		{
			perror("Invalid address");
			return 0;
		}
		if (connect(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
		{
			perror("Connection failed");
			return 0;
		}
		send(server_fd , av[2] , strlen(av[2]) , 0 );
		std::cout << "Hello message sent" << std::endl;
		char buffer[1024] = {0};
		int valread = read(server_fd , buffer, 1024);
		std::cout << buffer << std::endl;
		return 0;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}