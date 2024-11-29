#include "Server.h"
#include "DataBase.h"

int main()
{
	//sf::IpAddress ip = sf::IpAddress::LocalHost;
	//sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::IpAddress ip("34.16.110.198");
	uint16_t port = 53000;
	uint16_t port_udp = 53001;
	uint16_t port_db = 54000; // порт базы данных

	Server server(ip, port, port_udp);
	DataBase dataBase(ip, port_db);

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

	try
	{
		dataBase.init_db();
	}
	catch (const std::exception& error)
	{
		//std::cout << error.what() << std::endl;
		system("pause");
		return 2;
	}

	std::thread thread_db(&DataBase::run, std::ref(dataBase));
	
	server.run();



	if (thread_db.joinable())
	{
		thread_db.join();
	}


	system("pause");
	return 0;
}
