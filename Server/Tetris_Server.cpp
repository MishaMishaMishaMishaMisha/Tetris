#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <map>
#include <memory>
#include <SFML/Network.hpp>


std::vector<std::shared_ptr<sf::TcpSocket>> connections;
size_t counter = 0;
std::map<int, int> pairs; // Хранит пары клиентов (client1 -> client2)

// Поток для обработки клиента
void ClientHandler(int index)
{
    std::shared_ptr<sf::TcpSocket> client = connections[index];

    size_t msg_type_size;
    size_t msg_size;
    while (true)
    {
        // Получение размера типа сообщения
        std::size_t received;
        if (client->receive(&msg_type_size, sizeof(msg_type_size), received) != sf::Socket::Done || received != sizeof(msg_type_size))
        {
            std::cout << "Client " << index + 1 << " disconnected.\n";

            // Отключение клиента и уведомление его пары
            int pairIndex = pairs[index];
            if (pairIndex >= 0)
            {
                std::string str = "Your partner has disconnected";
                std::size_t str_size = str.size();

                std::shared_ptr<sf::TcpSocket> partner = connections[pairIndex];
                if (partner->send(&str_size, sizeof(str_size)) != sf::Socket::Done)
                {
                    std::cout << "sending error" << std::endl;
                }
                if (partner->send(str.c_str(), str_size) != sf::Socket::Done)
                {
                    std::cout << "sending error" << std::endl;
                }
                //partner->send(&str_size, sizeof(str_size));
                //partner->send(str.c_str(), str_size);
                pairs[pairIndex] = -1; // Убираем пару
            }
            pairs[index] = -1;
            client->disconnect();
            connections[index].reset();
            return;
        }
        if (msg_type_size == 0)
        {
            continue;
        }

        // Получение типа сообщения
        char* msg_type = new char[msg_type_size + 1];
        msg_type[msg_type_size] = '\0';
        if (client->receive(msg_type, msg_type_size, received) != sf::Socket::Done || received != msg_type_size)
        {
            std::cout << "Error receiving message from client " << index + 1 << std::endl;
            delete[] msg_type;
            continue;
        }

        // получение размера сообщения
        if (client->receive(&msg_size, sizeof(msg_size), received) != sf::Socket::Done || received != sizeof(msg_size))
        {
            std::cout << "Error receiving message from client " << index + 1 << std::endl;
            continue;
        }

        // Получение сообщения
        char* msg = new char[msg_size + 1];
        msg[msg_size] = '\0';
        if (client->receive(msg, msg_size, received) != sf::Socket::Done || received != msg_size)
        {
            std::cout << "Error receiving message from client " << index + 1 << std::endl;
            delete[] msg;
            continue;
        }
        
        

        // Передача сообщения партнеру
        int pairIndex = pairs[index];
        if (pairIndex >= 0)
        {
            std::shared_ptr<sf::TcpSocket> partner = connections[pairIndex];

            if (partner->send(&msg_type_size, sizeof(msg_type_size)) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }
            if (partner->send(msg_type, msg_type_size) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }
            if (partner->send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }
            if (partner->send(msg, msg_size) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }

            //partner->send(&msg_type_size, sizeof(msg_type_size));
            //partner->send(msg_type, msg_type_size);
            //partner->send(&msg_size, sizeof(msg_size));
            //partner->send(msg, msg_size);
        }

        delete[] msg_type;
        delete[] msg;

    }
}

int main()
{
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(53000, sf::IpAddress::LocalHost) != sf::Socket::Done)
    {
        // error...
        std::cout << "listener can't bind to a port" << std::endl;
        system("pause");
        return 1;
    }

    std::cout << "Server is ready to accept clients" << std::endl;



    std::vector<std::thread> threads;

    while (true)
    {
        // accept a new connection
        auto client = std::make_shared<sf::TcpSocket>();
        if (listener.accept(*client) != sf::Socket::Done)
        {
            std::cout << "Client can't connect.\n";
            continue;
        }

        // Find a free slot in the connections vector
        int newConnectionIndex = -1;
        for (int i = 0; i < connections.size(); ++i) 
        {
            // nullptr indicates a free slot
            if (!connections[i]) 
            {
                connections[i] = std::move(client);
                newConnectionIndex = i;
                break;
            }
        }
        // if no free slots, push in the end
        if (newConnectionIndex == -1)
        {
            connections.emplace_back(std::move(client));
            newConnectionIndex = connections.size() - 1;
            counter++;
        }

        std::cout << "Client " << newConnectionIndex + 1 << " connected!\n";


        // Отправка приветственного сообщения
        std::string welcomeMsg = "Searhing for opponent...";
        size_t msg_size = welcomeMsg.size();

        if (connections[newConnectionIndex]->send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
        {
            std::cout << "cant send msg_size to client " << newConnectionIndex + 1 << std::endl;
        }
        if (connections[newConnectionIndex]->send(welcomeMsg.c_str(), msg_size) != sf::Socket::Done)
        {
            std::cout << "cant send msg to client " << newConnectionIndex + 1 << std::endl;
        }


        // поиск пары
        // Проверяем, есть ли незанятый клиент для пары
        int pairIndex = -1;
        for (int i = 0; i < counter; i++)
        {
            // создаем пару, если: 
            // - это другой клиент, а не он сам
            // - это клиент, а не nullptr
            // - это свободный клиент без пары
            if (pairs[i] == -1 && i != newConnectionIndex && connections[i])
            {
                // Найден клиент без пары
                pairIndex = i;
                break;
            }
        }

        if (pairIndex >= 0)
        {
            // Создаем пару
            pairs[pairIndex] = newConnectionIndex;
            pairs[newConnectionIndex] = pairIndex;

            std::string msg = "Opponent found!";
            size_t msg_size = msg.size();

            if (connections[newConnectionIndex]->send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }
            if (connections[newConnectionIndex]->send(msg.c_str(), msg_size) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }

            if (connections[pairIndex]->send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }
            if (connections[pairIndex]->send(msg.c_str(), msg_size) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }

            //connections[newConnectionIndex]->send(&msg_size, sizeof(msg_size));
            //connections[newConnectionIndex]->send(msg.c_str(), msg_size);

            //connections[pairIndex]->send(&msg_size, sizeof(msg_size));
            //connections[pairIndex]->send(msg.c_str(), msg_size);

            // отправляем общий сид
            msg = "Seed";
            msg_size = msg.size();
            uint32_t seed = static_cast<uint32_t>(time(0));

            if (connections[newConnectionIndex]->send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }
            if (connections[newConnectionIndex]->send(msg.c_str(), msg_size) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }
            if (connections[newConnectionIndex]->send(&seed, sizeof(seed)) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }

            if (connections[pairIndex]->send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }
            if (connections[pairIndex]->send(msg.c_str(), msg_size) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }
            if (connections[pairIndex]->send(&seed, sizeof(seed)) != sf::Socket::Done)
            {
                std::cout << "sending error" << std::endl;
            }

            //connections[newConnectionIndex]->send(&msg_size, sizeof(msg_size));
            //connections[newConnectionIndex]->send(msg.c_str(), msg_size);
            //connections[newConnectionIndex]->send(&seed, sizeof(seed));

            //connections[pairIndex]->send(&msg_size, sizeof(msg_size));
            //connections[pairIndex]->send(msg.c_str(), msg_size);
            //connections[pairIndex]->send(&seed, sizeof(seed));

            std::cout << "Client " << newConnectionIndex + 1 << " paired with Client " << pairIndex + 1 << ".\n";
        }
        else
        {
            // Клиент ждет пару
            pairs[newConnectionIndex] = -1;
            //std::string msg = "Waiting for a partner...";
            //size_t msg_size = msg.size();
            //send(newConnection, (char*)&msg_size, sizeof(size_t), NULL);
            //send(newConnection, msg.c_str(), msg_size, NULL);
        }



        threads.emplace_back(ClientHandler, newConnectionIndex);
    }



    for (auto& thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
    


    system("pause");
    return 0;
}
