#include "GamePvPOnline.h"

GamePvPOnline::GamePvPOnline(uint16_t height, uint16_t width, sf::RenderWindow& win, Audio& a, sf::Sprite& backgroundSprite, sf::Font& font) :
    GamePvPLocal(height, width, win, a, backgroundSprite, font),
    field_opponent(height, width, win, font, FieldPosition::Right),
    is_opponent_found(false),
    is_connected_to_server(false),
    receiver_thread(),
    seed(0),
    gameOver_opponent(false),
    gameOver_player(false),
    is_youReady(false),
    is_opponentReady(false),
    is_error(false),
    is_textChanged(false),
    is_binded(false),
    time(0),
    ping_time(0),
    serverIP(sf::IpAddress::LocalHost),
    port(53000),
    upd_port(53001)
{

    game_left.setControlsMode(ControlsMode::BOTH);
    field_opponent.initFigure();


    // текст: connetion to server, disconnected, searching opponents...
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(50);
    text.setString("Connection to server...");
    // положение в центре экранa
    auto screen_size = window.getSize();
    sf::FloatRect text_bounds = text.getLocalBounds();
    text.setPosition(screen_size.x / 2.f - text_bounds.width / 2.f, screen_size.y / 4.f);

    // имя игрока слева
    player1.setFont(font);
    player1.setFillColor(sf::Color::White);
    player1.setCharacterSize(30);
    player1.setString("     YOU \n Press enter \n to get ready");
    text_bounds = player1.getLocalBounds();
    player1.setPosition(0, 0);

    // имя соперника
    player2.setFont(font);
    player2.setFillColor(sf::Color::White);
    player2.setCharacterSize(30);
    player2.setString("OPPONENT \n Unready");
    text_bounds = player2.getLocalBounds();
    player2.setPosition(screen_size.x - text_bounds.width, 0);

    // пинг
    ping_text.setFont(font);
    ping_text.setFillColor(sf::Color::White);
    ping_text.setCharacterSize(30);
    ping_text.setString("PING: 000");
    //sf::FloatRect ping_text_bounds = text.getLocalBounds();
    //ping_text.setPosition(text_bounds.getPosition().x - ping_text_bounds.width, 10);
    sf::FloatRect player2_bounds = player2.getGlobalBounds();
    ping_text.setPosition(player2_bounds.left - ping_text.getLocalBounds().width - 20, player2_bounds.top);

}

GameState GamePvPOnline::getNextState()
{
    if (gameOver_player && gameOver_opponent)
    {
        return GameState::GameoverPvPMenu;
    }
    return GameState::PauseMenu;
}

void GamePvPOnline::draw()
{
    // поиск соперника
    if (!is_opponent_found)
    {
        // подключаемся к серверу
        if (is_error)
        {
            window.draw(backgroundSprite);
            //window.draw(text);
            drawText();
        }
        else if (!is_connected_to_server)
        {
            text.setString("Connection to server...");
            is_textChanged = true;
            window.clear();
            window.draw(backgroundSprite);
            //window.draw(text);
            drawText();
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            //sf::Socket::Status status = socket.connect(serverIP, port);
            //if (status != sf::Socket::Done)
            if (!connectToServer())
            {
                text.setString("  Server is unavailable\nPress Esc to back to menu");
                is_textChanged = true;
                is_error = true;
            }
            else
            {
                // start threads
                receiver_thread = std::thread(&GamePvPOnline::receiveMsg, this);
                //ping_thread = std::thread(&GamePvPOnline::checkPing, this);
                is_connected_to_server = true;
            }
            
            window.clear();
            window.draw(backgroundSprite);
            //window.draw(text);
            drawText();
            window.display();
            clock.restart();
        }
        else
        {
            time = clock.getElapsedTime().asSeconds();
            // если поиск длится больше 60 секунд, отключаемся от сервера
            if (time > 60.f)
            {
                disconnect();
                text.setString("   Can't find opponent\nPress Esc to back to menu");
                is_textChanged = true;
                is_error = true;
            }

            window.draw(backgroundSprite);
            //window.draw(text);
            drawText();
        }



    }
    // начало игры
    else
    {
        // заканчиваем когда у обоих игроков game over
        if (gameOver_player && gameOver_opponent)
        {
            audio.stopMusic();
            isActive = false;
        }
        // запускаем тетрис когда оба игрока нажали enter (ready)
        if (!game_left.isGameOver() && is_youReady && is_opponentReady)
        {
            audio.playMusic();

            // забираем изменения
            Field& field = game_left.getField(); // получаем состояние поля текущего игрока
            // и отправляем все изменения сопернику
            if (field.isSwapFigureChanged)
            {
                auto send_data = sender.sendSwapFigure(field);
                send_packet.clear();
                std::string msg = "SwapFigureChanged";
                send_packet << msg << send_data;
                if (socket.send(send_packet) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
            }
            if (field.isNextFigureChanged)
            {
                auto send_data = sender.sendNextFigure(field);
                send_packet.clear();
                std::string msg = "NextFigureChanged";
                send_packet << msg << send_data;
                if (socket.send(send_packet) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
            }
            if (field.isFigureChanged)
            {
                auto send_data = sender.sendCurFigure(field);
                send_packet.clear();
                std::string msg = "FigureChanged";
                send_packet << msg << send_data;
                if (socket.send(send_packet) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
            }
            if (field.isFigurePosChanged)
            {
                auto send_data = sender.sendFigurePosition(field);
                send_packet.clear();
                std::string msg = "FigurePosChanged";
                send_packet << msg << send_data;
                if (socket.send(send_packet) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
            }
            if (field.isNewBlocks)
            {
                auto send_data = sender.sendNewBlocks(field);
                send_packet.clear();
                std::string msg = "NewBlocks";
                send_packet << msg << send_data;
                if (socket.send(send_packet) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
            }
            if (field.isRowDestroyed)
            {
                auto send_data = sender.sendNewField(field);
                send_packet.clear();
                std::string msg = "RowDestroyed";
                send_packet << msg << send_data;
                if (socket.send(send_packet) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
            }
            if (field.isScoresChanged)
            {
                auto send_data = sender.sendScore(field);
                send_packet.clear();
                std::string msg = "ScoresChanged";
                send_packet << msg << send_data;
                if (socket.send(send_packet) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
            }
        }
        if (game_left.isGameOver() && !gameOver_player)
        {
            send_packet.clear();
            std::string msg = "GameOver";
            send_packet << msg;
            if (socket.send(send_packet) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }

            gameOver_player = true;
            player1.setString("PLAYER1 \n Game Over");
        }



        window.draw(backgroundSprite); // фон
        window.draw(player1); // текст в левом углy
        window.draw(player2); // текст в правом углу
        window.draw(ping_text); // пинг
        window.draw(centerLine); // центральная линия
        if (is_youReady && is_opponentReady)
        {
            // поле игрока
            game_left.draw();
            // поле соперника
            field_opponent.drawGrid();
            field_opponent.drawBlocks();
            field_opponent.drawFigure();
            field_opponent.drawScore();
        }
        else
        {
            game_left.getField().drawGrid();
            field_opponent.drawGrid();
        }

    }

}

void GamePvPOnline::handleEvents(sf::Event& event)
{
    if (!game_left.isGameOver() && is_youReady && is_opponentReady)
    {
        game_left.handleEvents(event);
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (controls.button_escape(event))
        {
            audio.playPauseEffect();
            isActive = false;
        }

        if (controls.button_enter(event) && is_opponent_found && !is_youReady)
        {
            player1.setString("YOU \n Ready");
            is_youReady = true;

            send_packet.clear();
            std::string msg = "Ready";
            send_packet << msg;
            if (socket.send(send_packet) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }

        }
    }

}

void GamePvPOnline::set_Active()
{
    isActive = true;
}

void GamePvPOnline::restart()
{
    game_left.setSeed(seed);
    game_left.restart();
    field_opponent.restart();
    gameOver_player = false;
    gameOver_opponent = false;
    is_youReady = false;
    is_opponentReady = false;
    is_error = false;
    player1.setString("     YOU \n Press enter \n to get ready");
    player2.setString("OPPONENT \n Unready");
    //audio.stopMusic();
}

void GamePvPOnline::receiveMsg()
{
    sf::Packet packet_receive;
    std::string msg;
    std::string data;

    while (true)
    {
        packet_receive.clear();
        msg.clear();
        data.clear();

        // сначала получаем весь пакет
        if (socket.receive(packet_receive) != sf::Socket::Done)
        {
            is_error = true;
            text.setString("Disconnected from server");
            is_textChanged = true;
            disconnect();
            return;
        }

        // считываем сообщение
        if (!(packet_receive >> msg))
        {
            is_error = true;
            text.setString("Failed to extract msg from packet");
            is_textChanged = true;
            disconnect();
            return;
        }

        // определяем тип сообщения
        if (msg == "Searhing for opponent...")
        {
            text.setString(msg);
            is_textChanged = true;
        }
        else if (msg == "Opponent found!")
        {
            text.setString(msg);
            is_textChanged = true;
            is_opponent_found = true;
            ping_thread = std::thread(&GamePvPOnline::checkPing, this);
        }
        else if (msg == "Your partner has disconnected")
        {
            text.setString(msg);
            is_textChanged = true;
            is_opponent_found = false;
            audio.stopMusic();
        }
        else if (msg == "Seed")
        {
            // раскаковываем data (в этом случае число - сид)
            if (!(packet_receive >> seed))
            {
                //std::cout << "Failed to extract data from packet" << std::endl;
                //continue;
                is_error = true;
                text.setString("Failed to extract seed from packet");
                is_textChanged = true;
                disconnect();
                return;
            }
            // вызываем restart чтобы применить сид
            restart();
        }
        else if (msg == "GameOver")
        {
            player2.setString("OPPONENT \n Game Over");
            gameOver_opponent = true;
        }
        else if (msg == "Ready")
        {
            player2.setString("OPPONENT \n Ready");
            is_opponentReady = true;
        }
        // обработка типов изменений поля
        else
        {
            // раскаковываем data 
            if (!(packet_receive >> data))
            {
                //std::cout << "Failed to extract data from packet" << std::endl;
                //continue;
                is_error = true;
                text.setString("Failed to extract data from packet");
                is_textChanged = true;
                disconnect();
                return;
            }
            // отправляем обрабатывать data
            receiveData(msg, data);

        }

    }

}

void GamePvPOnline::disconnect()
{
    if (socket.getRemoteAddress() != sf::IpAddress::None)
    {
        socket.disconnect();
        
        receiver_thread.detach();

        is_connected_to_server = false;
        is_opponent_found = false;
    }
    if (is_binded)
    {
        is_binded = false;
        ping_socket.unbind();

        //ping_thread.detach();

    }
}

void GamePvPOnline::receiveData(std::string type, std::string data)
{
    if (type == "SwapFigureChanged")
    {
        sender.receiveSwapFigure(field_opponent, data);
    }
    else if (type == "NextFigureChanged")
    {
        sender.receiveNextFigure(field_opponent, data);
    }
    else if (type == "FigureChanged")
    {
        sender.receiveCurFigure(field_opponent, data);
    }
    else if (type == "FigurePosChanged")
    {
        sender.receiveFigurePosition(field_opponent, data);
    }
    else if (type == "NewBlocks")
    {
        sender.receiveNewBlocks(field_opponent, data);
    }
    else if (type == "RowDestroyed")
    {
        sender.receiveNewField(field_opponent, data);
    }
    else if (type == "ScoresChanged")
    {
        sender.receiveScore(field_opponent, data);
    }

}

void GamePvPOnline::drawText()
{
    if (is_textChanged)
    {
        // положение в центре экранa
        auto screen_size = window.getSize();
        sf::FloatRect text_bounds = text.getLocalBounds();
        text.setPosition(screen_size.x / 2.f - text_bounds.width / 2.f, screen_size.y / 4.f);
        is_textChanged = false;
    }
    window.draw(text);
}

bool GamePvPOnline::connectToServer()
{
    // tcp socket
    sf::Socket::Status status = socket.connect(serverIP, port);
    if (status != sf::Socket::Done) 
    {
        socket.disconnect();
        return false;
    }
    // upd socket
    if (ping_socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
    {
        socket.disconnect();
        ping_socket.unbind();
        return false;
    }
    is_binded = true;

    // отправляем ip,port игрока серверу
    sf::Packet packet;
    //packet << sf::IpAddress::getLocalAddress().toString() << ping_socket.getLocalPort();
    packet << sf::IpAddress::LocalHost.toString() << ping_socket.getLocalPort();
    if (socket.send(packet) != sf::Socket::Done) 
    {
        socket.disconnect();
        ping_socket.unbind();
        text.setString("Server connection lost \n Press Esc to back to menu");
        is_error = true;
        return false;
    }

    return true;
}

void GamePvPOnline::checkPing()
{

    ping_socket.setBlocking(false);

    sf::IpAddress senderIP;
    uint16_t senderPort;
    std::string msg;

    sf::Clock clock_local;
    float time_local;

    // сразу проверяем пинг
    ping_packet.clear();
    ping_packet << "PING";
    ping_clock.restart();
    ping_socket.send(ping_packet, serverIP, upd_port);
    clock_local.restart();
    ///////////////////////
    while (is_connected_to_server)
    //while (true)
    {
        // проверка пинга каждые 5 секунд
        time_local = clock_local.getElapsedTime().asSeconds();
        if (time_local > 5.f)
        {
            ping_packet.clear();
            ping_packet << "PING";
            ping_clock.restart();
            ping_socket.send(ping_packet, serverIP, upd_port);
            clock_local.restart();
        }

        // получаем сообщение
        ping_packet.clear();
        msg.clear();
        ping_socket.receive(ping_packet, senderIP, senderPort);

        ping_packet >> msg;
        if (msg == "PING")
        {
            // посылаем сообщение обратно
            ping_packet.clear();
            ping_packet << "PONG";
            ping_socket.send(ping_packet, serverIP, upd_port);
        }
        else if (msg == "PONG")
        {
            // считаем время за которое сообщение вернулось назад
            ping_time = ping_clock.getElapsedTime().asMilliseconds();
            ping_text.setString("PING: " + std::to_string(static_cast<int>(ping_time)));
            ping_clock.restart();
        }
        
    }


}

