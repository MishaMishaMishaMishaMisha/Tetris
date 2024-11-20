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
    time(0)
{
    game_left.setControlsMode(ControlsMode::BOTH);
    field_opponent.initFigure();



    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(50);
    text.setString("connection to server...");

    // положение в центре экранa
    auto screen_size = window.getSize();
    sf::FloatRect text_bounds = text.getLocalBounds();
    text.setPosition(screen_size.x / 2.f - text_bounds.width / 2.f, screen_size.y / 4.f);


    player1.setFont(font);
    player1.setFillColor(sf::Color::White);
    player1.setCharacterSize(30);
    player1.setString("YOU \n Press enter \n to get ready");
    text_bounds = player1.getLocalBounds();
    player1.setPosition(0, 0);

    player2.setFont(font);
    player2.setFillColor(sf::Color::White);
    player2.setCharacterSize(30);
    player2.setString("OPPONENT \n Unready");
    text_bounds = player2.getLocalBounds();
    player2.setPosition(screen_size.x - text_bounds.width, 0);

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
        // если не подключен к серверу, то подключемся
        if (is_error)
        {
            window.draw(backgroundSprite);
            window.draw(text);
        }
        else if (!is_connected_to_server)
        {
            text.setString("connection to server...");
            window.clear();
            window.draw(backgroundSprite);
            window.draw(text);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            sf::Socket::Status status = socket.connect(sf::IpAddress::LocalHost, 53000);
            if (status != sf::Socket::Done)
            {
                text.setString("can't connect to server \n Press Esc to back to menu");
                is_error = true;
            }
            else
            {
                // receive message
                receiver_thread = std::thread(&GamePvPOnline::receiveMsg, this);
                is_connected_to_server = true;
            }
            
            window.clear();
            window.draw(backgroundSprite);
            window.draw(text);
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
                text.setString("Can't find opponent \n Press Esc to back to menu");
                is_error = true;
            }

            window.draw(backgroundSprite);
            window.draw(text);
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
                size_t data_size = send_data.size();

                std::string msg = "SwapFigureChanged";
                size_t msg_size = msg.size();

                if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(&data_size, sizeof(data_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(send_data.c_str(), data_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }

                //socket.send(&msg_size, sizeof(msg_size));
                //socket.send(msg.c_str(), msg_size);
                //socket.send(&data_size, sizeof(data_size));
                //socket.send(send_data.c_str(), data_size);
            }
            if (field.isNextFigureChanged)
            {
                auto send_data = sender.sendNextFigure(field);
                size_t data_size = send_data.size();

                std::string msg = "NextFigureChanged";
                size_t msg_size = msg.size();

                if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(&data_size, sizeof(data_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(send_data.c_str(), data_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }

                //socket.send(&msg_size, sizeof(msg_size));
                //socket.send(msg.c_str(), msg_size);
                //socket.send(&data_size, sizeof(data_size));
                //socket.send(send_data.c_str(), data_size);
            }
            if (field.isFigureChanged)
            {
                auto send_data = sender.sendCurFigure(field);
                size_t data_size = send_data.size();

                std::string msg = "FigureChanged";
                size_t msg_size = msg.size();

                if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(&data_size, sizeof(data_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(send_data.c_str(), data_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }

                //socket.send(&msg_size, sizeof(msg_size));
                //socket.send(msg.c_str(), msg_size);
                //socket.send(&data_size, sizeof(data_size));
                //socket.send(send_data.c_str(), data_size);
            }
            if (field.isFigurePosChanged)
            {
                auto send_data = sender.sendFigurePosition(field);
                size_t data_size = send_data.size();

                std::string msg = "FigurePosChanged";
                size_t msg_size = msg.size();

                if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(&data_size, sizeof(data_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(send_data.c_str(), data_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }

                //socket.send(&msg_size, sizeof(msg_size));
                //socket.send(msg.c_str(), msg_size);
                //socket.send(&data_size, sizeof(data_size));
                //socket.send(send_data.c_str(), data_size);
            }
            if (field.isNewBlocks)
            {
                auto send_data = sender.sendNewBlocks(field);
                size_t data_size = send_data.size();

                std::string msg = "NewBlocks";
                size_t msg_size = msg.size();

                if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(&data_size, sizeof(data_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(send_data.c_str(), data_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }

                //socket.send(&msg_size, sizeof(msg_size));
                //socket.send(msg.c_str(), msg_size);
                //socket.send(&data_size, sizeof(data_size));
                //socket.send(send_data.c_str(), data_size);
            }
            if (field.isRowDestroyed)
            {
                auto send_data = sender.sendNewField(field);
                size_t data_size = send_data.size();

                std::string msg = "RowDestroyed";
                size_t msg_size = msg.size();

                if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(&data_size, sizeof(data_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(send_data.c_str(), data_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }

                //socket.send(&msg_size, sizeof(msg_size));
                //socket.send(msg.c_str(), msg_size);
                //socket.send(&data_size, sizeof(data_size));
                //socket.send(send_data.c_str(), data_size);
            }
            if (field.isScoresChanged)
            {
                auto send_data = sender.sendScore(field);
                size_t data_size = send_data.size();

                std::string msg = "ScoresChanged";
                size_t msg_size = msg.size();

                if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(&data_size, sizeof(data_size)) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }
                if (socket.send(send_data.c_str(), data_size) != sf::Socket::Done)
                {
                    disconnect();
                    text.setString("Server connection lost \n Press Esc to back to menu");
                    is_error = true;
                }

                //socket.send(&msg_size, sizeof(msg_size));
                //socket.send(msg.c_str(), msg_size);
                //socket.send(&data_size, sizeof(data_size));
                //socket.send(send_data.c_str(), data_size);
            }
        }
        if (game_left.isGameOver() && !gameOver_player)
        {
            std::string msg = "GameOver";
            size_t msg_size = msg.size();

            if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }
            if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }
            if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }
            if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }

            //socket.send(&msg_size, sizeof(msg_size));
            //socket.send(msg.c_str(), msg_size);
            //socket.send(&msg_size, sizeof(msg_size));
            //socket.send(msg.c_str(), msg_size);

            gameOver_player = true;
            player1.setString("PLAYER1 \n Game Over");
        }



        window.draw(backgroundSprite); // фон
        window.draw(player1); // текст в левом углy
        window.draw(player2); // текст в правом углу
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

        if (controls.button_enter(event) && !is_youReady)
        {
            player1.setString("YOU \n Ready");
            is_youReady = true;

            std::string msg = "Ready";
            size_t msg_size = msg.size();

            if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }
            if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }
            if (socket.send(&msg_size, sizeof(msg_size)) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }
            if (socket.send(msg.c_str(), msg_size) != sf::Socket::Done)
            {
                disconnect();
                text.setString("Server connection lost \n Press Esc to back to menu");
                is_error = true;
            }

            //socket.send(&msg_size, sizeof(msg_size));
            //socket.send(msg.c_str(), msg_size);
            //socket.send(&msg_size, sizeof(msg_size));
            //socket.send(msg.c_str(), msg_size);
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
    player1.setString("YOU \n Press enter \n to get ready");
    player2.setString("OPPONENT \n Unready");
    //audio.stopMusic();
}

void GamePvPOnline::receiveMsg()
{
    // Переменная для хранения размера сообщения
    std::size_t msg_size;
    std::size_t received;

    while (true)
    {
        // Получение размера сообщения
        if (socket.receive(&msg_size, sizeof(msg_size), received) != sf::Socket::Done || received != sizeof(msg_size))
        {
            is_error = true;
            text.setString("Disconnected from server");
            disconnect();
            return;
        }

        // Получение сообщения
        char* msg = new char[msg_size + 1];
        msg[msg_size] = '\0';
        if (socket.receive(msg, msg_size, received) != sf::Socket::Done || received != msg_size)
        {
            delete[] msg;
            is_error = true;
            text.setString("Disconnected from server");
            disconnect();
            return;
        }

        std::string msg_str(msg);

        if (msg_str == "Searhing for opponent...")
        {
            text.setString(msg_str);
        }
        else if (msg_str == "Opponent found!")
        {
            text.setString(msg_str);
            is_opponent_found = true;
        }
        else if (msg_str == "Your partner has disconnected")
        {
            text.setString(msg_str);
            is_opponent_found = false;
            audio.stopMusic();
        }
        else if (msg_str == "Seed")
        {
            if (socket.receive(&seed, sizeof(seed), received) != sf::Socket::Done)
            {
                is_error = true;
                text.setString(msg_str);
                text.setString("Disconnected from server");
                disconnect();
                return;
            }
            restart();
        }
        // обработка типов изменений поля
        else
        {

            if (socket.receive(&msg_size, sizeof(msg_size), received) != sf::Socket::Done || received != sizeof(msg_size))
            {
                is_error = true;
                text.setString("Disconnected from server");
                disconnect();
                return;
            }

            char* type_ = new char[msg_size + 1];
            type_[msg_size] = '\0';
            if (socket.receive(type_, msg_size, received) != sf::Socket::Done || received != msg_size)
            {
                delete[] type_;
                is_error = true;
                text.setString("Disconnected from server");
                disconnect();
                return;
            }

            std::string type_str(type_);
            receiveData(msg_str, type_str);
        }
        

        delete[] msg;
    }
}

void GamePvPOnline::disconnect()
{
    if (socket.getRemoteAddress() != sf::IpAddress::None)
    {
        socket.disconnect();
        //if (receiver_thread.joinable())
        //{
        //    receiver_thread.join();
        //}
        receiver_thread.detach();
        is_connected_to_server = false;
        is_opponent_found = false;
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
    else if (type == "GameOver")
    {
        player2.setString("OPPONENT \n Game Over");
        gameOver_opponent = true;
    }
    else if (type == "Ready")
    {
        player2.setString("OPPONENT \n Ready");
        is_opponentReady = true;
    }
}



