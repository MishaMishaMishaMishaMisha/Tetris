#include "Server.h"

void Server::init_server()
{
    // bind the listener to a port
    if (listener.listen(port, serverIP) != sf::Socket::Done)
    {
        throw std::runtime_error("Failed to bind listener to this port");
    }

    // UDP socket
    if (udp_socket.bind(port_udp) != sf::Socket::Done)
    {
        throw std::runtime_error("Failed to bind UDP socket to this port");
    }
    udp_socket.setBlocking(false);

    std::cout << "Server is ready to accept players" << std::endl;
}

void Server::run()
{
    udp_thread = std::thread(&Server::udpPlayerHandler, this);

    while (true)
    {
        // accept a new connection
        auto player = std::make_shared<sf::TcpSocket>();
        if (listener.accept(*player) != sf::Socket::Done)
        {
            std::cout << "Player can't connect.\n";
            continue;
        }

        // Find a free slot in the connections vector
        int newConnectionIndex = -1;
        for (int i = 0; i < connections.size(); ++i)
        {

            std::lock_guard<std::mutex> lock(connections_mutex);
            if (!connections[i])
            {
                connections[i] = std::move(player);
                newConnectionIndex = i;
                break;
            }
        }
        // if no free slots, push in the end
        if (newConnectionIndex == -1)
        {
            addConnection(std::move(player));
            newConnectionIndex = connections.size() - 1;
            counter++;
        }

        std::cout << "Player " << newConnectionIndex + 1 << " connected!\n";



        // ������� ������ � udp ������
        sf::Packet packet;
        if (getConnection(newConnectionIndex)->receive(packet) != sf::Socket::Done)
        {
            std::cout << "Failed to receive UDP info from player " << newConnectionIndex + 1 << std::endl;
            getConnection(newConnectionIndex)->disconnect();
            resetConnection(newConnectionIndex);
            continue;
        }
        // ��������� �� ������
        std::string ip_str;
        sf::IpAddress udpIP;
        uint16_t udpPort;
        packet >> ip_str >> udpPort;
        udpIP = sf::IpAddress(ip_str);
        // ���������� �� � �������
        udpIPs[newConnectionIndex] = udpIP;
        udpPorts[newConnectionIndex] = udpPort;



        // �������� ���������
        packet_main.clear();
        std::string msg = "Searhing for opponent...";
        packet_main << msg;
        if (getConnection(newConnectionIndex)->send(packet_main) != sf::Socket::Done)
        {
            std::cout << "cant send msg_size to player " << newConnectionIndex + 1 << std::endl;
        }


        // ����� ����
        // ���������, ���� �� ��������� ������ ��� ����
        int pairIndex = -1;
        for (int i = 0; i < counter; i++)
        {
            // ������� ����, ����: 
            // - ��� ������ ������, � �� �� ���
            // - ��� ������, � �� nullptr
            // - ��� ��������� ������ ��� ����
            if (getPair(i) == -1 && i != newConnectionIndex && getConnection(i))
            {
                // ������ ������ ��� ����
                pairIndex = i;
                break;
            }
        }

        if (pairIndex >= 0)
        {
            // ������� ����
            addPair(pairIndex, newConnectionIndex);
            addPair(newConnectionIndex, pairIndex);

            // �������� ��������� � ��������� ���������
            packet_main.clear();
            std::string msg = "Opponent found!";
            packet_main << msg;
            if (getConnection(newConnectionIndex)->send(packet_main) != sf::Socket::Done)
            {
                std::cout << "sending msg (opponent found) error" << std::endl;
            }
            if (getConnection(pairIndex)->send(packet_main) != sf::Socket::Done)
            {
                std::cout << "sending msg (opponent found) error" << std::endl;
            }


            // ���������� ����� ���
            packet_main.clear();
            msg = "Seed";
            uint32_t seed = static_cast<uint32_t>(time(0));
            packet_main << msg << seed;
            if (getConnection(newConnectionIndex)->send(packet_main) != sf::Socket::Done)
            {
                std::cout << "sending msg (seed) error" << std::endl;
            }
            if (getConnection(pairIndex)->send(packet_main) != sf::Socket::Done)
            {
                std::cout << "sending msg (seed) error" << std::endl;
            }


            std::cout << "Player " << newConnectionIndex + 1 << " paired with Player " << pairIndex + 1 << ".\n";
        }
        else
        {
            // ������ ���� ����
            addPair(newConnectionIndex, -1);

        }

        threads.emplace_back(&Server::playerHandler, this, newConnectionIndex);
    }



    for (auto& thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    if (udp_thread.joinable())
    {
        udp_thread.join();
    }
}

void Server::playerHandler(int index)
{
    std::shared_ptr<sf::TcpSocket> player = getConnection(index);

    sf::Packet packet_player;

    while (true)
    {
        packet_player.clear();

        // �������� ����� �� ������
        if (player->receive(packet_player) != sf::Socket::Done)
        {
            std::cout << "Player " << index + 1 << " disconnected.\n";

            // ���������� ������� � ����������� ��� ����
            std::lock_guard<std::mutex> lock(pairs_mutex);
            int pairIndex = pairs[index];
            if (pairIndex >= 0)
            {
                std::string msg = "Your partner has disconnected";
                packet_player.clear();
                packet_player << msg;

                std::shared_ptr<sf::TcpSocket> partner = getConnection(pairIndex);

                if (partner->send(packet_player) != sf::Socket::Done)
                {
                    std::cout << "Sending error" << std::endl;
                }

                pairs[pairIndex] = -1; // ������� ����
            }
            pairs[index] = -1;
            player->disconnect();
            resetConnection(index);
            return;
        }

        // �������� �����a ���������
        std::lock_guard<std::mutex> lock(pairs_mutex);
        int pairIndex = pairs[index];
        if (pairIndex >= 0)
        {
            std::shared_ptr<sf::TcpSocket> partner = getConnection(pairIndex);

            if (partner->send(packet_player) != sf::Socket::Done)
            {
                std::cout << "Sending packet error" << std::endl;
                // �������� ���������� ����?
            }

        }

    }
}


void Server::addConnection(std::shared_ptr<sf::TcpSocket> client)
{
    std::lock_guard<std::mutex> lock(connections_mutex);
    connections.emplace_back(std::move(client));
}

std::shared_ptr<sf::TcpSocket> Server::getConnection(size_t index)
{
    std::lock_guard<std::mutex> lock(connections_mutex);
    return connections[index];
}

void Server::resetConnection(size_t index)
{
    std::lock_guard<std::mutex> lock(connections_mutex);
    connections[index].reset();
}


void Server::addPair(size_t index, int value)
{
    std::lock_guard<std::mutex> lock(pairs_mutex);
    pairs[index] = value;
}

int Server::getPair(size_t index)
{
    std::lock_guard<std::mutex> lock(pairs_mutex);
    return pairs[index];
}

void Server::udpPlayerHandler()
{
    sf::Packet packet;
    sf::IpAddress senderIP;
    uint16_t senderPort;

    while (true) 
    {
        packet.clear();
        if (udp_socket.receive(packet, senderIP, senderPort) == sf::Socket::Done) 
        {

            // ����� �����������
            int senderID = -1;
            for (const auto& pair : udpIPs)
            {
                int id = pair.first;
                const sf::IpAddress& ip = pair.second;

                if (ip == senderIP && udpPorts[id] == senderPort)
                {
                    senderID = id;
                    break;
                }
            }
            if (senderID == -1) continue;

            // ����� ���� � ��������� ���������
            int pairID = getPair(senderID);
            if (pairID >= 0) 
            {
                udp_socket.send(packet, udpIPs[pairID], udpPorts[pairID]);
            }
        }

        // ��������, ����� �������� ���������� �������� CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}