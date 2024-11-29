#include "DataBase.h"

void DataBase::init_db()
{
    // bind the listener to a port
    if (listener.listen(port, sf::IpAddress::Any) != sf::Socket::Done)
    {
        throw std::runtime_error("Failed dataBaseServer to bind listener to this port");
    }

    // подключение к бд
    // инициализация объекта для отправки запросов в бд
    conn = mysql_init(nullptr);

    if (!conn)
    {
        throw std::runtime_error("mysql_init() failed");
    }

    // подключение к бд
    if (!mysql_real_connect(conn, "localhost", "bleed4me", "krabik123", "my_first_db", 0, nullptr, 0))
    {
        mysql_close(conn);
        throw std::runtime_error("Connection to mariadb failed:");
    }

    std::cout << "Connected to MariaDB! ";

    std::cout << "DataBase is ready to accept queries: " << serverIP.toString() << ": " << port << std::endl;
}

void DataBase::run()
{

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



        threads.emplace_back(&DataBase::playerHandler, this, newConnectionIndex);
    }


    for (auto& thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    mysql_close(conn);

}

void DataBase::playerHandler(int index)
{
    std::shared_ptr<sf::TcpSocket> player = getConnection(index);

    sf::Packet packet_player;

    while (connections[index])
    {
        packet_player.clear();

        // получаем пакет от игрока
        if (player->receive(packet_player) != sf::Socket::Done)
        {
            // отключаем игрока
            std::cout << "Player " << index + 1 << " disconnected.\n";
            player->disconnect();
            resetConnection(index);
            return;
        }

        // смотрим какой запрос был от игрока
        std::string msg;
        if (!(packet_player >> msg))
        {
            player->disconnect();
            resetConnection(index);
            std::cout << "Can't extract msg from Player " << index + 1 << "\n";
            return;
        }


        if (msg == "IsUserInDB")
        {
	    std::cout << "isUserInDB\n";
            std::string name;
            if (!(packet_player >> name))
            {
                player->disconnect();
                resetConnection(index);
                std::cout << "Can't extract msg from Player " << index + 1 << "\n";
                return;
            }
            std::string password;
            if (!(packet_player >> password))
            {
                player->disconnect();
                resetConnection(index);
                std::cout << "Can't extract msg from Player " << index + 1 << "\n";
                return;
            }
            checkUserInDB(index, name, password);
        }
        else if (msg == "AddNewUser")
        {

	    std::cout << "AddNewUser\n";
            std::string name;
            if (!(packet_player >> name))
            {
                player->disconnect();
                resetConnection(index);
                std::cout << "Can't extract msg_name from Player " << index + 1 << "\n";
                return;
            }
            std::string password;
            if (!(packet_player >> password))
            {
                player->disconnect();
                resetConnection(index);
                std::cout << "Can't extract msg_pass from Player " << index + 1 << "\n";
                return;
            }
            addNewUser(index, name, password);
        }
        else if (msg == "UploadRecord")
        {

	    std::cout << "UploadRecord\n";
            std::string name;
            std::array<uint32_t, 5> record;
            if (!(packet_player >> name))
            {
                player->disconnect();
                resetConnection(index);
                std::cout << "Can't extract msg from Player " << index + 1 << "\n";
                return;
            }
            for (int i = 0; i < 5; i++)
            {
                if (!(packet_player >> record[i]))
                {
                    player->disconnect();
                    resetConnection(index);
                    std::cout << "Can't extract msg from Player " << index + 1 << "\n";
                    return;
                }
            }
            updateRecord(index, name, record);

        }
        else if (msg == "DownloadRecord")
        {

	    std::cout << "DownloadRecord\n";
            std::string name;
            if (!(packet_player >> name))
            {
                player->disconnect();
                resetConnection(index);
                std::cout << "Can't extract msg from Player " << index + 1 << "\n";
                return;
            }
            downloadRecord(index, name);
        }
        else if (msg == "DownloadMyRating")
        {

	    std::cout << "DownloadMyRating\n";
            std::string name;
            if (!(packet_player >> name))
            {
                player->disconnect();
                resetConnection(index);
                std::cout << "Can't extract msg from Player " << index + 1 << "\n";
                return;
            }
            downloadUserRating(index, name);
        }
        else if (msg == "DownloadTop5")
        {

	    std::cout << "DownloadTop5\n";
            downloadTop5(index);
        }
        else
        {
            std::cout << "Unknown msg: " << msg << "\n";
        }

    }
}


void DataBase::addConnection(std::shared_ptr<sf::TcpSocket> client)
{
    std::lock_guard<std::mutex> lock(connections_mutex);
    connections.emplace_back(std::move(client));
}

std::shared_ptr<sf::TcpSocket> DataBase::getConnection(size_t index)
{
    std::lock_guard<std::mutex> lock(connections_mutex);
    return connections[index];
}

void DataBase::resetConnection(size_t index)
{
    std::lock_guard<std::mutex> lock(connections_mutex);
    connections[index].reset();
}


void DataBase::checkUserInDB(size_t user_index, std::string name, std::string pass)
{
    // Подготовка SQL-запроса
    std::string query = "SELECT COUNT(*) FROM PLAYERS WHERE username = '" + name + "' AND hash_password = '" + pass + "';";
    sf::Packet packet;

    // Выполнение запроса
    if (mysql_query(conn, query.c_str())) 
    {
        std::cout << "Query failed: " << mysql_error(conn) << std::endl;
        
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;
    }

    // Получение результата запроса
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) 
    {
        std::cout << "Failed to store result: " << mysql_error(conn) << std::endl;
        
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;
    }

    // Чтение строки результата
    MYSQL_ROW row = mysql_fetch_row(result);

    if (row && std::stoi(row[0]) > 0) 
    {
        packet << "success" << "Yes";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;
    }

    // Освобождаем память
    mysql_free_result(result);

    packet << "success" << "No";
    if (getConnection(user_index)->send(packet) != sf::Socket::Done)
    {
        std::cout << "sending msg error" << std::endl;
    }
}

void DataBase::addNewUser(size_t user_index, std::string name, std::string password)
{
    std::lock_guard<std::mutex> lock(db_mutex);

    // 1. проверяем нет ли в таблице пользователя с таким ником
        // Подготовка SQL-запроса
    std::string query1 = "SELECT COUNT(*) FROM PLAYERS WHERE username = \'" + name + "\';";

    sf::Packet packet;

    // Выполнение запроса
    if (mysql_query(conn, query1.c_str()))
    {
        std::cout << "Query failed: " << mysql_error(conn) << std::endl;

        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;
    }

    // Получение результата запроса
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result)
    {
        std::cout << "Failed to store result: " << mysql_error(conn) << std::endl;

        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;
    }

    // Чтение строки результата
    MYSQL_ROW row = mysql_fetch_row(result);

    int count = 0;
    if (row && row[0])
    {
	count = std::stoi(row[0]);
    }
    // Освобождаем память
    mysql_free_result(result);

    if (count > 0)
    {
        packet << "success" << "ThisNameIsAlreadyInDB";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;

    }


    ////////
    // 2. добавляем в таблицу

    // Формируем SQL-запрос
    std::string query = "INSERT INTO PLAYERS (username, hash_password, record_score, record_lines, record_level, count_pvp_games, count_pvp_wins) VALUES ('"
        + name + "', '" + password + "', 0, 0, 1, 0, 0);";

    // Выполняем запрос
    if (mysql_query(conn, query.c_str()))
    {
        std::cout << "Failed to add new player: " + std::string(mysql_error(conn));
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;
    }

    packet << "success" << "UserAdded";
    if (getConnection(user_index)->send(packet) != sf::Socket::Done)
    {
        std::cout << "sending msg error" << std::endl;
    }

}

void DataBase::updateRecord(size_t user_index, std::string name, std::array<uint32_t, 5> record)
{
    std::lock_guard<std::mutex> lock(db_mutex);
    sf::Packet packet;

    // Формируем SQL-запрос
    std::string query = "UPDATE PLAYERS SET record_score = " + std::to_string(record[0]) +
        ", record_lines = " + std::to_string(record[1]) +
        ", record_level = " + std::to_string(record[2]) +
        ", count_pvp_games = " + std::to_string(record[3]) +
        ", count_pvp_wins = " + std::to_string(record[4]) +
        " WHERE username = '" + name + "';";

    // Выполняем запрос
    if (mysql_query(conn, query.c_str()))
    {
        std::cout << "Failed to update player stats: " + std::string(mysql_error(conn));
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;
    }

    packet << "successUpload";
    if (getConnection(user_index)->send(packet) != sf::Socket::Done)
    {
        std::cout << "sending msg error" << std::endl;
    }
}

void DataBase::downloadRecord(size_t user_index, std::string name)
{
    sf::Packet packet;
    // Подготовка SQL-запроса
    std::string query = "SELECT  record_score, record_lines, record_level, count_pvp_games, count_pvp_wins FROM PLAYERS WHERE username = '" + name + "';";

    // Выполнение SQL-запроса
    if (mysql_query(conn, query.c_str()))
    {
        std::cout << "Query failed: " + std::string(mysql_error(conn));
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;
    }

    // Получение результата запроса
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result)
    {
        std::cout << "Failed to store result: " + std::string(mysql_error(conn));
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
	return;
    }

    // Проверка, есть ли строка с таким именем
    if (mysql_num_rows(result) == 0)
    {
        std::cout << "No player found with name: " << name << std::endl;
        mysql_free_result(result);
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg  error" << std::endl;
        }
        return;
    }

    // Извлечение строки из результата
    MYSQL_ROW row = mysql_fetch_row(result);

    packet << "success";
    for (size_t i = 0; i < 5; ++i)
    {
	unsigned int value = std::stoul(row[i]);
	packet << value;
    }

    if (getConnection(user_index)->send(packet) != sf::Socket::Done)
    {
        std::cout << "sending msg  error" << std::endl;
    }

    // Очистка ресурсов
    mysql_free_result(result);
}

void DataBase::downloadTop5(size_t user_index)
{
    sf::Packet packet;

    // Формируем SQL-запрос
    std::string query = "SELECT username, record_score, record_lines, record_level, count_pvp_games, count_pvp_wins FROM PLAYERS ORDER BY record_score DESC LIMIT 10;";

    // Выполнение SQL-запроса
    if (mysql_query(conn, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
        packet << "error";
	if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg  error" << std::endl;
        }
        return;
    }

    // Получение результата
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result)
    {
        std::cerr << "Failed to store result: " << mysql_error(conn) << std::endl;
        packet << "error";
	if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg  error" << std::endl;
        }
        return;
    }

    // Проверяем, есть ли результаты
    if (mysql_num_rows(result) == 0)
    {
        std::cerr << "No players found" << std::endl;
        packet << "error";
        mysql_free_result(result);
	if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
        return;
    }

    // Отправляем успешный ответ
    packet << "successTop5";

    // записываем количество строк
    uint16_t rows = mysql_num_rows(result);

    packet << rows;

    // Извлечение строк результата
    MYSQL_ROW row;
    size_t place = 1;
    while ((row = mysql_fetch_row(result)) != nullptr)
    {
        // считываем данные игроков
	std::string name = row[0];
	std::string score = row[1];
	std::string lines = row[2];
	std::string level = row[3];
	std::string count_pvp_games = row[4];;
	std::string count_pvp_wins = row[5];
	
	std::string player = formatPlayerRow(place, name, score, lines, level, count_pvp_games, count_pvp_wins);

	packet << name;
	packet << player;
	place++;
    }



    if (getConnection(user_index)->send(packet) != sf::Socket::Done)
    {
            std::cout << "sending msg  error" << std::endl;
    }



    // Освобождаем память
    mysql_free_result(result);

}

void DataBase::downloadUserRating(size_t user_index, std::string name)
{
	    sf::Packet packet;

    // Сначала находим место пользователя в рейтинге
    std::string query =
        "WITH RankedPlayers AS ( "
        "    SELECT username, record_score, record_lines, record_level, count_pvp_games, count_pvp_wins, "
        "           ROW_NUMBER() OVER (ORDER BY record_score DESC) AS rank "
        "    FROM PLAYERS "
        ") "
        "SELECT rank FROM RankedPlayers WHERE username = '" + name + "';";

    // Выполняем SQL-запрос для получения позиции игрока
    if (mysql_query(conn, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
        return;
    }

    // Получаем результат
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result)
    {
        std::cerr << "Failed to store result: " << mysql_error(conn) << std::endl;
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
        return;
    }

    // Проверяем, есть ли строки (пользователь найден)
    MYSQL_ROW row = mysql_fetch_row(result);
    if (!row)
    {
        std::cerr << "Player not found" << std::endl;
        packet << "error";
        mysql_free_result(result);
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
        return;
    }

    // Получаем место игрока
    int player_rank = std::stoi(row[0]);

    // Освобождаем память
    mysql_free_result(result);

    // Теперь получаем игроков с места (player_rank - 5) до (player_rank + 4)
    query =
        "WITH RankedPlayers AS ( "
        "    SELECT username, record_score, record_lines, record_level, count_pvp_games, count_pvp_wins, "
        "           ROW_NUMBER() OVER (ORDER BY record_score DESC) AS rank "
        "    FROM PLAYERS "
        ") "
        "SELECT username, record_score, record_lines, record_level, count_pvp_games, count_pvp_wins, rank "
        "FROM RankedPlayers "
        "WHERE rank BETWEEN " + std::to_string(player_rank - 5) + " AND " + std::to_string(player_rank + 4) + ";";

    // Выполняем SQL-запрос для получения данных игроков в пределах диапазона
    if (mysql_query(conn, query.c_str()))
    {
        std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
        return;
    }

    // Получаем результат
    result = mysql_store_result(conn);
    if (!result)
    {
        std::cerr << "Failed to store result: " << mysql_error(conn) << std::endl;
        packet << "error";
        if (getConnection(user_index)->send(packet) != sf::Socket::Done)
        {
            std::cout << "sending msg error" << std::endl;
        }
        return;
    }

    // Записываем успешный ответ
    packet << "successTopPlayers";

    // Отправляем количество игроков в этом запросе
    uint16_t rows = mysql_num_rows(result);
    packet << rows;

    // Извлечение данных игроков и добавление в пакет
    while ((row = mysql_fetch_row(result)) != nullptr)
    {
        std::string name = row[0];
        std::string score = row[1];
        std::string lines = row[2];
        std::string level = row[3];
        std::string count_pvp_games = row[4];
        std::string count_pvp_wins = row[5];
        int rank = std::stoi(row[6]); // Место игрока

        // Формируем строку с данными игрока
        std::string player = formatPlayerRow(rank, name, score, lines, level, count_pvp_games, count_pvp_wins);

        // Добавляем в пакет
	packet << name;
        packet << player;
    }

    // Отправляем данные клиенту
    if (getConnection(user_index)->send(packet) != sf::Socket::Done)
    {
        std::cout << "sending msg error" << std::endl;
    }

    // Освобождаем память
    mysql_free_result(result);
}

std::string DataBase::formatPlayerRow(
    size_t place,
    const std::string& username,
    const std::string& score,
    const std::string& lines,
    const std::string& level,
    const std::string& pvp_games,
    const std::string& pvp_wins)
{
    std::ostringstream oss;

    // вычислим win_rate
    int total = std::stoi(pvp_games);
    int wins = std::stoi(pvp_wins);
    std::string win_rate = "0%"; 
    if (wins)
    {
	    win_rate.clear();
	    win_rate = std::to_string(100*wins/total) + "%";
    }


    // Устанавливаем фиксированные ширины колонок с выравниванием по левому краю
    oss << "| " << std::setw(6) << std::left << place     // Место (до 3 символов)
        << "| " << std::setw(21) << std::left << username // Имя (до 20 символов)
        << "| " << std::setw(8) << std::left << score    // Очки (до 8 символов, выравнивание по правому краю)
        << "| " << std::setw(6) << std::left << lines    // Линии (до 6 символов)
        << "| " << std::setw(6) << std::left << level    // Уровень (до 6 символов)
        << "| " << std::setw(10) << std::left << pvp_games // Игры (до 10 символов)
        << "| " << std::setw(9) << std::left << pvp_wins  // Победы (до 9 символов)
	<< "| " << std::setw(9) << std::left << win_rate
        << "|";

    return oss.str();
}

