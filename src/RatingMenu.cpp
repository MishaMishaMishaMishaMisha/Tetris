#include "RatingMenu.h"

RatingMenu::RatingMenu(sf::RenderWindow& win, sf::Font& font, Audio& a, sf::Sprite& backgroundSprite) :
	BaseWindow(a, backgroundSprite, win),
	font(font),
    input_name(font),
    input_password(font),
    input_confirm_password(font),
    is_main(true),
    is_register(false),
    is_login(false),
    num_buttons_main(3),
    num_buttons_login(3),
    num_buttons_register(4),
    num_buttons_rating(3),
    buttons_main(num_buttons_main, sf::Text()),
    buttons_login(num_buttons_login, sf::Text()),
    buttons_register(num_buttons_register, sf::Text()),
    buttons_rating(num_buttons_rating, sf::Text()),
    players(max_size_rating_list, sf::Text()),
    is_logged_in(false),
    is_connected(false),
    is_error_connetion(false)
{

    db_IP = serverInfo.ip;
    db_port = serverInfo.port_db;

    auto screen_size = window.getSize();

    createPlayersTable();



    // title text
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setCharacterSize(60);
    setTitle("LOG IN TO YOUR ACCOUNT");
    // error text
    error.setFont(font);
    error.setFillColor(sf::Color::Red);
    error.setCharacterSize(30);
    error.setString("");
    // username
    username.setFont(font);
    username.setFillColor(sf::Color::Green);
    username.setCharacterSize(50);
    username.setString("");
    username.setPosition(0, 0);


    file_user.setPath("Files/");
    file_user.setFileName("user.bin"); // файл содержит: "*username* *isLoggeIn*
    file_record.setPath("Files/");
    file_record.setFileName("record.bin"); // файл содержит: "*score* *lines* *level* *gamesPVPcount* *winsPVPcount* *is_new_record*

    // проверяем, есть ли файл с данными игрока и зашел ли он в аккаунт
    std::string user = file_user.readLine();
    if (user.length() > 0)
    {
        std::string str_name, str_is_loggedin;
        size_t spacePos = user.find(' ');

        if (spacePos != std::string::npos) 
        {
            str_name = user.substr(0, spacePos);
            str_is_loggedin = user.substr(spacePos + 1);
        }
        
        if (std::stoi(str_is_loggedin))
        {
            is_logged_in = true;
            is_main = false;
            setTitle("RATING LIST");
            username.setString(str_name);
        }
        else
        {
            is_logged_in = false;
        }
    }
    else
    {
        is_logged_in = false;
    }


    // кнопки главного меню
    names_main = { "REGISTER", "LOG IN", "BACK" };
    for (size_t i = 0; i < num_buttons_main; i++)
    {
        buttons_main[i].setFont(font);
        buttons_main[i].setFillColor(sf::Color::White);
        buttons_main[i].setCharacterSize(50);
        buttons_main[i].setString(names_main[i]);
        sf::FloatRect text_bounds = buttons_main[i].getLocalBounds();
        buttons_main[i].setPosition(screen_size.x / 2.f - text_bounds.width / 2.f, screen_size.y / 2.f - num_buttons_main * 45 + i * 90);
    }

    // кнопки в меню rating list
    names_rating = { "SHOW YOUR PLACE", "LOG OUT", "BACK" };
    for (size_t i = 0; i < num_buttons_rating; i++)
    {
        buttons_rating[i].setFont(font);
        buttons_rating[i].setFillColor(sf::Color::White);
        buttons_rating[i].setCharacterSize(50);
        buttons_rating[i].setString(names_rating[i]);
        sf::FloatRect text_bounds = buttons_rating[i].getLocalBounds();
        buttons_rating[i].setPosition(screen_size.x / 2.f - text_bounds.width / 2.f, screen_size.y / 1.15 - num_buttons_rating * 45 + i * 90);
    }


    // распологаем надписи с полями для ввода
    sf::Vector2f center(screen_size.x / 2.f, screen_size.y / 2.f);
    float text_offset = 100.f; // Смещение текста от центра вправо
    float input_offset = 300.f; // Смещение полей ввода влево от текста
    float vertical_spacing = 90.f; // Расстояние между строками
    // Определяем правый край для всех текстов
    float right_edge = center.x + text_offset;
    // register
    names_register = { "NAME", "PASSSWORD", "CONFIRM PASSWORD", "OK"};
    for (size_t i = 0; i < num_buttons_register; i++) 
    {
        buttons_register[i].setFont(font);
        buttons_register[i].setFillColor(sf::Color::White);
        buttons_register[i].setCharacterSize(50);
        buttons_register[i].setString(names_register[i]);
        sf::FloatRect text_bounds = buttons_register[i].getLocalBounds();

        float text_x = right_edge - text_bounds.width;
        float text_y = center.y - num_buttons_register * vertical_spacing / 2 + i * vertical_spacing;
        buttons_register[i].setPosition(text_x, text_y);

        float input_x = buttons_register[i].getPosition().x + buttons_register[i].getLocalBounds().width + 10;
        float input_y = text_y + text_bounds.height / 4;

        switch (i) 
        {
        case 0:
            input_name.setPosition(input_x, input_y);
            break;
        case 1:
            input_password.setPosition(input_x, input_y);
            break;
        case 2:
            input_confirm_password.setPosition(input_x, input_y);
            break;
        }
    }
    // login
    names_login = { "NAME", "PASSSWORD", "OK"};
    for (size_t i = 0; i < num_buttons_login; i++)
    {
        buttons_login[i].setFont(font);
        buttons_login[i].setFillColor(sf::Color::White);
        buttons_login[i].setCharacterSize(50);
        buttons_login[i].setString(names_login[i]);

        auto pos = buttons_register[i].getPosition();
        buttons_login[i].setPosition(pos.x, pos.y);
    }
    // отдельно надпись OK
    buttons_login[num_buttons_login - 1].setPosition(
        buttons_register[num_buttons_login].getPosition().x,
        buttons_register[num_buttons_login - 1].getPosition().y);

    // расположим текст ошибки наверху:
    error.setPosition(
        buttons_register[0].getPosition().x,
        buttons_register[0].getPosition().y - buttons_register[0].getLocalBounds().height);


    // поля для пароля заменяем на *
    input_password.setInvisible(true);
    input_confirm_password.setInvisible(true);

    // подсвечиваем первый пункт меню
    highlightButton();

}

void RatingMenu::draw()
{
    window.draw(backgroundSprite);

    // подключаемся к серверу
    if (is_error_connetion)
    {
        window.draw(title);
    }
    else if (!is_connected)
    {
        setTitle("Connection to server...");
        window.draw(title);
        window.display();
        connect();
    }
    // если подключились
    else
    {
        // когда зашли в аккаунт, показываем рейтинг
        if (is_logged_in)
        {

            showRatingList();

        }
        // вход/регистрация
        else
        {
            window.draw(title);
            window.draw(error);

            if (is_main)
            {
                for (size_t i = 0; i < num_buttons_main; i++)
                {
                    window.draw(buttons_main[i]);
                }
            }
            else if (is_register)
            {
                input_name.draw(window);
                input_password.draw(window);
                input_confirm_password.draw(window);
                for (size_t i = 0; i < num_buttons_register; i++)
                {
                    window.draw(buttons_register[i]);
                }
            }
            else if (is_login)
            {
                input_name.draw(window);
                input_password.draw(window);
                for (size_t i = 0; i < num_buttons_login; i++)
                {
                    window.draw(buttons_login[i]);
                }
            }
        }

    }

}

void RatingMenu::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Escape button
        if (event.key.code == sf::Keyboard::Escape)
        {
            isActive = false;
            // если в главном меню нажат Esc, возвращаемся в меню Highscores
            if (is_main)
            {
                selected_button = 2;
            }
            // если в меню регистрации или входа нажат Esc, возвращаемся в главное меню
            else if (is_register || is_login)
            {
                is_register = false;
                is_login = false;
                is_main = true;
                selected_button = -1;
            }
            // из rating list возвращаемся в Highscore
            else if (is_logged_in)
            {
                selected_button = 2;
            }
        }
        // Enter button
        else if (event.key.code == sf::Keyboard::Enter)
        {
            // после нажатия Enter из меню или ratingList просто переходим в выбранное меню
            if (is_main || is_logged_in)
            {
                isActive = false;
            }
            // если Enter нажата в меню register/login на пункт ОК
            else if ((is_register && selected_button == 3) || (is_login && selected_button == 2))
            {
                if (checkInput())
                {
                    // если is_register->добавляем в базу его данные (username,pass_hash) и рекорд из файла
                    if (is_register)
                    {
                        uploadRecordToDB();
                    }
                    // если is_login->скачиваем его рекорд и записываем в файл
                    if (is_login)
                    {
                        downloadRecordFromDB();
                    }

                    isActive = false;
                }
            }
        }
        // переключение меню вверх/вниз
        else if (controls.button_up(event))
        {
            moveUp();
        }
        else if (controls.button_down(event))
        {
            moveDown();
        }

    }

    // ввод текста
    if (is_register)
    {
        if (selected_button == 0)
        {
            input_name.inputButton(event);
        }
        if (selected_button == 1)
        {
            input_password.inputButton(event);
        }
        if (selected_button == 2)
        {
            input_confirm_password.inputButton(event);
        }
    }
    if (is_login)
    {
        if (selected_button == 0)
        {
            input_name.inputButton(event);
        }
        if (selected_button == 1)
        {
            input_password.inputButton(event);
        }
    }
}

GameState RatingMenu::getNextState()
{
    
    if (is_main)
    {
        // вход в главное меню из меню регистрации/входа после нажатия Esc
        if (selected_button == -1)
        {
            setTitle("LOG IN TO YOUR ACCOUNT");
            error.setString("");
            controls.setMode(ControlsMode::BOTH);
            return GameState::RatingMenu;
        }
        // меню регистрации
        else if (selected_button == 0)
        {
            setTitle("        REGISTRATION\n(USE ARROWS TO CHANGE FIELD)");
            error.setString("");
            controls.setMode(ControlsMode::ARROWS);
            is_register = true;
            is_main = false;
            return GameState::RatingMenu;
        }
        // меню входа
        else if (selected_button == 1)
        {
            setTitle("           LOG IN\n(USE ARROWS TO CHANGE FIELD)");
            error.setString("");
            controls.setMode(ControlsMode::ARROWS);
            is_login = true;
            is_main = false;
            return GameState::RatingMenu;
        }
        // вернутся назад в меню Highscores
        //else if (selected_button == 2)
        else
        {
            disconnect();
            return GameState::HighscoreMenu;
        }
    }
    // после регистрации либо входа, открывам rating list
    else if (is_register || is_login)
    {
        resetListColor();
        setTitle("RATING LIST");
        controls.setMode(ControlsMode::BOTH);
        error.setString("");
        is_register = false;
        is_login = false;
        return GameState::RatingMenu;
    }
    else if (is_logged_in)
    {
        // кнопка show rating
        if (selected_button == 0)
        {
            // смена топ5 на свое место и наоборот

            if (buttons_rating[0].getString() == "SHOW TOP 10")
            {
                buttons_rating[0].setString("SHOW YOUR PLACE");
                downloadRating();
            }
            else
            {
                buttons_rating[0].setString("SHOW TOP 10");
                downloadRating(false); // рейтинг игрока
            }
            sf::FloatRect text_bounds = buttons_rating[0].getLocalBounds();
            float x = window.getSize().x / 2 - text_bounds.width / 2;
            float y = buttons_rating[0].getPosition().y;
            buttons_rating[0].setPosition(x, y);
            return GameState::RatingMenu;
            // ...
        }
        // кнопка log out
        else if (selected_button == 1)
        {
            // выходим из аккаунта    
            std::string line = username.getString() + " 0"; // 0 означает что выполнен выход из аккаунта
            file_user.writeLine(line);
            // обнуляем файл
            resetRecordFile();

            is_logged_in = false;
            is_main = true;
            return GameState::RatingMenu;
        }
        // кнопка back
        //if (selected_button == 2)
        else
        {
            disconnect();
            return GameState::HighscoreMenu;
        }
    }
    else
    {
        disconnect();
        return GameState::HighscoreMenu;
    }

}

void RatingMenu::set_Active()
{
	isActive = true;
    
    resetButtonsColor();
    input_name.reset();
    input_password.reset();
    input_confirm_password.reset();

}

void RatingMenu::moveUp()
{
    audio.playSelectEffect();

    if (is_main)
    {
        buttons_main[selected_button--].setFillColor(sf::Color::White);
        if (selected_button < 0)
        {
            selected_button = num_buttons_main - 1;
        }
    }
    else if (is_register)
    {
        buttons_register[selected_button--].setFillColor(sf::Color::White);
        if (selected_button < 0)
        {
            selected_button = num_buttons_register - 1;
        }
    }
    else if (is_login)
    {
        buttons_login[selected_button--].setFillColor(sf::Color::White);
        if (selected_button < 0)
        {
            selected_button = num_buttons_login - 1;
        }
    }
    else if (is_logged_in)
    {
        buttons_rating[selected_button--].setFillColor(sf::Color::White);
        if (selected_button < 0)
        {
            selected_button = num_buttons_rating - 1;
        }
    }

    highlightButton();
}

void RatingMenu::moveDown()
{
    audio.playSelectEffect();

    if (is_main)
    {
        buttons_main[selected_button++].setFillColor(sf::Color::White);
        if (selected_button >= num_buttons_main)
        {
            selected_button = 0;
        }
    }
    else if (is_register)
    {
        buttons_register[selected_button++].setFillColor(sf::Color::White);
        if (selected_button >= num_buttons_register)
        {
            selected_button = 0;
        }
    }
    else if (is_login)
    {
        buttons_login[selected_button++].setFillColor(sf::Color::White);
        if (selected_button >= num_buttons_login)
        {
            selected_button = 0;
        }
    }
    else if (is_logged_in)
    {
        buttons_rating[selected_button++].setFillColor(sf::Color::White);
        if (selected_button >= num_buttons_rating)
        {
            selected_button = 0;
        }
    }

    highlightButton();
}

void RatingMenu::resetButtonsColor()
{
    for (size_t i = 0; i < num_buttons_main; i++)
    {
        buttons_main[i].setFillColor(sf::Color::White);
    }
    for (size_t i = 0; i < num_buttons_register; i++)
    {
        buttons_register[i].setFillColor(sf::Color::White);
    }
    for (size_t i = 0; i < num_buttons_login; i++)
    {
        buttons_login[i].setFillColor(sf::Color::White);
    }
    for (size_t i = 0; i < num_buttons_rating; i++)
    {
        buttons_rating[i].setFillColor(sf::Color::White);
    }
    selected_button = 0;
    highlightButton();
}

void RatingMenu::highlightButton()
{
    if (is_main)
    {
        buttons_main[selected_button].setFillColor(sf::Color(170, 70, 70));
    }
    else if (is_register)
    {
        buttons_register[selected_button].setFillColor(sf::Color(170, 70, 70));
    }
    else if (is_login)
    {
        buttons_login[selected_button].setFillColor(sf::Color(170, 70, 70));
    }
    else if (is_logged_in)
    {
        buttons_rating[selected_button].setFillColor(sf::Color(170, 70, 70));
    }

}

void RatingMenu::setTitle(std::string text)
{
    title.setString(text);
    sf::FloatRect text_bounds = title.getLocalBounds();
    title.setPosition(window.getSize().x / 2 - text_bounds.width / 2, 40);
}

bool RatingMenu::checkInput()
{
    if (is_register)
    {
        std::string name = input_name.getStr();
        std::string pass = input_password.getStr();
        std::string pass_confirm = input_confirm_password.getStr();

        // проверка на заполненные поля
        if (name.empty() || pass.empty() || pass_confirm.empty())
        {
            error.setString("fill all fields");
            return false;
        }

        // проверка на слишком короткое имя
        if (name.size() <= 4)
        {
            error.setString("too short name");
            return false;
        }
        // проверка на слишком короткий пароль
        if (pass.size() <= 4)
        {
            error.setString("too short password");
            return false;
        }

        // проверка на одинаковые пароли
        if (pass != pass_confirm)
        {
            error.setString("passwords don't match");
            return false;
        }

        // проверить, что такого имени нету в базе
        if (!addNewUserToDB(name, std::to_string(hash_fn(pass))))
        {
            error.setString("this name is unavailable");
            return false;
        }
    }
    else if (is_login)
    {
        std::string name = input_name.getStr();
        std::string pass = input_password.getStr();
        
        // проверка на заполненные поля
        if (name.empty() || pass.empty())
        {
            error.setString("fill all fields");
            return false;
        }

        // проверка, существует ли такой пользователь в базе
        if (!isUserInDB(name, std::to_string(hash_fn(pass))))
        {
            error.setString("wrong name or password");
            return false;
        }

    }

    is_logged_in = true;
    username.setString(input_name.getStr());
    password_hash = std::to_string(hash_fn(input_password.getStr()));
    
    std::string line = input_name.getStr() + " 1"; // 1 означает что вход выполнен
    file_user.writeLine(line);

    return true;
}

void RatingMenu::showRatingList()
{

    window.draw(title);
    window.draw(username);

    // отображаем названия колонок и разделительные линии между строками
    window.draw(players_table[1]);
    for (size_t i = 0; i < max_size_table; ++i)
    {
        if (i % 2 == 0)
        {
            window.draw(players_table[i]);
        }
    }
    // отображаем игроков
    for (size_t i = 0; i < current_size_rating_list; i++)
    {
        window.draw(players[i]);
    }
    // кнопки снизу
    for (size_t i = 0; i < num_buttons_rating; i++)
    {
        window.draw(buttons_rating[i]);
    }

}

void RatingMenu::resetRecordFile()
{
    std::string line = "0 0 1 0 0 0";
    file_record.writeLine(line);
}

bool RatingMenu::checkIsNewRecord()
{
    std::string line = file_record.readLine();
    // если файла нету, скачиваем из бд
    if (line.empty())
    {
        downloadRecordFromDB();
        return false;
    }

    if (line[line.size() - 1] == '1')
    {
        return true;
    }
    return false;
}

void RatingMenu::setRecordOld()
{
    std::string line = file_record.readLine();
    line[line.size() - 1] = '0';
    file_record.writeLine(line);
}

bool RatingMenu::isUserInDB(std::string name, std::string pass)
{
    packet.clear();
    packet << "IsUserInDB" << name << pass;


    if (!sendPacket())
    {
        return false;
    }

    if (!receivePacket())
    {
        return false;
    }

    // считываем сообщение
    std::string msg;
    if (!(packet >> msg))
    {
        socket.disconnect();
        is_error_connetion = true;
        setTitle("Failed to extract packet\nPress Esc to back to menu");
        return true;
    }

    if (msg == "Yes")
    {
        return true;
    }
    return false;
}

bool RatingMenu::addNewUserToDB(std::string name, std::string password)
{
    packet.clear();
    packet << "AddNewUser" << name << password;
    if (!sendPacket())
    {
        return false;
    }

    if (!receivePacket())
    {
        return false;
    }

    // считываем сообщение
    std::string msg;
    if (!(packet >> msg))
    {
        socket.disconnect();
        is_error_connetion = true;
        setTitle("Failed to extract packet\nPress Esc to back to menu");
        return false;
    }

    if (msg == "UserAdded")
    {
        return true;
    }
    else if (msg == "ThisNameIsAlreadyInDB")
    {
        return false;
    }

    return false;
}

void RatingMenu::uploadRecordToDB()
{
    packet.clear();
    std::string name = username.getString();
    packet << "UploadRecord" << name;

    // читаем рекорд
    std::vector<unsigned int> numbers = file_record.splitIntoNumbers(file_record.readLine());
    if (numbers.size() >= 5)
    {
        packet << numbers[0] << numbers[1] << numbers[2] << numbers[3] << numbers[4];
    }
    else
    {
        packet << 0 << 0 << 1 << 0 << 0;
    }

    if (!sendPacket())
    {
        // ...
        return;
    }
    if (!receivePacket())
    {
        // ...
        return;
    }

}

void RatingMenu::downloadRecordFromDB()
{
    packet.clear();
    std::string name = username.getString();
    packet << "DownloadRecord" << name;

    if (!sendPacket())
    {
        return;
    }

    if (!receivePacket())
    {
        return;
    }

    std::string line = "";
    unsigned int value;
    for (int i = 0; i < 5; i++)
    {
        if (!(packet >> value))
        {
            socket.disconnect();
            is_error_connetion = true;
            setTitle("Failed to extract packet\nPress Esc to back to menu");
            return;
        }
        line += std::to_string(value) + " ";
    }
    line += "0"; // в конце 0 - то есть рекорд пока не обновлен
    file_record.writeLine(line);
}

void RatingMenu::downloadRating(bool isTop)
{
    packet.clear();
    std::string name = username.getString();
    if (isTop)
    {
        packet << "DownloadTop5";
    }
    else
    {
        packet << "DownloadMyRating" << name;
    }

    if (!sendPacket())
    {
        return;
    }

    // ... receive rating
    if (!receivePacket())
    {
        return;
    }

    if (!(packet >> current_size_rating_list))
    {
        socket.disconnect();
        is_error_connetion = true;
        setTitle("Failed to extract packet\nPress Esc to back to menu");
        return;
    }

    resetListColor();
    for (int i = 0; i < current_size_rating_list; i++)
    {
        std::string player;
        std::string name;
        if (!(packet >> name))
        {
            socket.disconnect();
            is_error_connetion = true;
            setTitle("Failed to extract packet\nPress Esc to back to menu");
            return;
        }
        if (!(packet >> player))
        {
            socket.disconnect();
            is_error_connetion = true;
            setTitle("Failed to extract packet\nPress Esc to back to menu");
            return;
        }

        players[i].setString(player);

        if (name == username.getString())
        {
            players[i].setFillColor(sf::Color::Green);
        }
        else
        {
            players[i].setFillColor(sf::Color::White);
        }

    }
}


void RatingMenu::connect()
{
    sf::Socket::Status status = socket.connect(db_IP, db_port);
    if (status != sf::Socket::Done)
    {
        socket.disconnect();
        is_error_connetion = true;
        setTitle("  Server is unavailable\nPress Esc to back to menu");
        return;
    }

    // при каждом заходе в это меню
    // проверяем файл record.bin и если is_new_record=true,обновляем рекорд в базе и меняем на false
    if (is_logged_in)
    {
        if (checkIsNewRecord())
        {
            uploadRecordToDB();
            setRecordOld();
            // после обновления можно перекачать рейтинг
            downloadRating();
        }

        // при первом заходе (когда еще эти строки одинаковые), скачиваем рейтинг
        if (players[0].getString() == players[1].getString())
        {
            downloadRating();
        }

    }

    setTitle("RATING LIST");
    is_error_connetion = false;
    is_connected = true;
}

void RatingMenu::disconnect()
{
    is_connected = false;
    is_error_connetion = false;
    socket.disconnect();
}

bool RatingMenu::sendPacket()
{
    if (socket.send(packet) != sf::Socket::Done)
    {
        disconnect();
        setTitle("Server connection lost \n Press Esc to back to menu");
        is_error_connetion = true;
        return false;
    }
    return true;
}

bool RatingMenu::receivePacket()
{
    packet.clear();
    if (socket.receive(packet) != sf::Socket::Done)
    {
        disconnect();
        setTitle("Server connection lost \n Press Esc to back to menu");
        is_error_connetion = true;
        return false;
    }

    std::string error_msg;
    if (!(packet >> error_msg))
    {
        socket.disconnect();
        is_error_connetion = true;
        setTitle("Failed to extract packet\nPress Esc to back to menu");
        return false;
    }
    if (error_msg == "error")
    {
        socket.disconnect();
        is_error_connetion = true;
        setTitle("error from data base\nPress Esc to back to menu");
        return false;
    }

    return true;
}


void RatingMenu::createPlayersTable()
{
    max_size_table = (max_size_rating_list + 1) * 2 + 1;
    players_table.resize(max_size_table, sf::Text());

    for (size_t i = 0; i < max_size_table; ++i)
    {
        players_table[i].setFont(font);
        players_table[i].setFillColor(sf::Color::White);
        players_table[i].setCharacterSize(20);
        
        if (i % 2 == 0)
        {
            players_table[i].setString("--------------------------------------------------------------------------------------------");
        }
        else
        {
            players_table[i].setString("|   #   |     Player Name      |  score  | lines | level | pvp_games | pvp_wins | win_rate |");
        }
     

        sf::FloatRect text_bounds = players_table[i].getLocalBounds();
        players_table[i].setPosition(window.getSize().x / 2 - text_bounds.width / 2, 100 + i * 30);
    }

    float x_pos = players_table[0].getPosition().x;

    //players rating list
    for (size_t i = 0; i < max_size_rating_list; ++i)
    {
        players[i].setFont(font);
        players[i].setFillColor(sf::Color::White);
        players[i].setCharacterSize(20);
        players[i].setString("");

        players[i].setPosition(x_pos, 190 + i * 60);
    }


}

void RatingMenu::resetListColor()
{
    for (size_t i = 0; i < current_size_rating_list; i++)
    {
        players[i].setFillColor(sf::Color::White);
    }
}