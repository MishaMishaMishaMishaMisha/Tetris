#include "Server.h"

int main()
{
	sf::IpAddress ip = sf::IpAddress::LocalHost;
	uint16_t port = 53000;
	uint16_t port_udp = 53001;

	Server server(ip, port, port_udp);

	try
	{
		server.init_server();
	}
	catch (const std::exception& error)
	{
		//std::cout << error.what() << std::endl;
		system("pause");
		return 1;
	}

	server.run();




	system("pause");
	return 0;
}