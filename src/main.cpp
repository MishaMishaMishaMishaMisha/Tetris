#include "GameManager.h"

int main()
{

    // экран
    int height = sf::VideoMode::getDesktopMode().height;
    int width = sf::VideoMode::getDesktopMode().width;
    //int height = 600;
    //int width = 800;
    sf::RenderWindow window(sf::VideoMode(width, height), "TETRIS", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    // загрузка контента

    // загрузка значка
    sf::Image icon;
    if (!icon.loadFromFile("Images/icon.png"))
    {
        return 10; // код ошибки - не удалось загрузить значoк
    }
    window.setIcon(32, 32, icon.getPixelsPtr());

    // загрузка звуков и музыки
    Audio audio;
    try
    {
        audio.load();
    }
    catch (const std::exception& e)
    {
        // error
        return 11; // код ошибки - не удалось открыть музыку
    }

    // загрузка шрифтов
    sf::Font font;
    if (!font.loadFromFile("Fonts/PrestigeEliteStd.otf"))
    {
        return 12; // код ошибки - не удалось загрузить шрифт
    }

    // загрузка картинок для фона
    sf::Texture backgroundTexture;
    sf::Texture mainMenuTexture;
    sf::Texture controlsTexture;
    if (!backgroundTexture.loadFromFile("Images/backgound.jpg"))
    {
        return 13; // код ошибки - не удалось загрузить фон игры
    }
    if (!mainMenuTexture.loadFromFile("Images/main_window.jpg"))
    {
        return 14; // код ошибки - не удалось загрузить фон меню
    }
    if (!controlsTexture.loadFromFile("Images/controls.png"))
    {
        return 15; // код ошибки - не удалось загрузить картинку с управлением
    }
    // Устанавливаем текстуру на спрайт
    sf::Sprite backgroundSprite;
    sf::Sprite mainMenuSprite;
    sf::Sprite controlsSprite;
    backgroundSprite.setTexture(backgroundTexture);
    mainMenuSprite.setTexture(mainMenuTexture);
    controlsSprite.setTexture(controlsTexture);


    // создание всех окон
    BaseWindow *game = new Game(height, width, window, audio, backgroundSprite, font);
    BaseWindow *pauseMenu = new PauseMenu(window, font, audio, backgroundSprite);
    BaseWindow *mainMenu = new MainMenu(window, font, audio, mainMenuSprite);
    BaseWindow* gameoverMenu = new GameOverMenu(window, font, audio, backgroundSprite);
    BaseWindow* gameoverPvPMenu = new GameOverPvPMenu(window, font, audio, backgroundSprite);
    BaseWindow *highscoreMenu = new HighscoreMenu(window, font, audio, backgroundSprite);
    BaseWindow *optionsMenu = new OptionsMenu(window, font, audio, backgroundSprite, controlsTexture);
    BaseWindow* gamePvPLocal = new GamePvPLocal(height, width, window, audio, backgroundSprite, font);

    // поместить все окна в вектор
    std::vector<BaseWindow*> windows;
    windows.push_back(mainMenu);
    windows.push_back(game);
    windows.push_back(gamePvPLocal);
    windows.push_back(pauseMenu);
    windows.push_back(highscoreMenu);
    windows.push_back(gameoverMenu);
    windows.push_back(gameoverPvPMenu);
    windows.push_back(optionsMenu);

    GameManager manager(windows);
    GameState state = GameState::MainMenu; // первое окно при запуcке
    manager.setState(state);

    int current_window;

    while (window.isOpen())
    {
        current_window = manager.get_state();

        if (current_window == -1)
        {
            window.close();
            break;
        }

        // Обработка нажатий клавиш
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            windows[current_window]->handleEvents(event);

        }

        // отображение на экране
        window.clear();
        windows[current_window]->draw();
        window.display();

    }


    // освобождение памяти
    for (auto win : windows)
    {
        delete win;
    }


    return 0;
}

