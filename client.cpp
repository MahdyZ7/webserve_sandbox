#include "SevCli.hpp"

int main()
{
	struct sockaddr_in address;

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("cannot create socket");
		return 0;
	}

	memset((char*)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
}