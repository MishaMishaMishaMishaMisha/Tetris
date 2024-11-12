#include "GameManager.h"

int main()
{

    // �����
    int height = sf::VideoMode::getDesktopMode().height;
    int width = sf::VideoMode::getDesktopMode().width;
    //int height = 600;
    //int width = 800;
    sf::RenderWindow window(sf::VideoMode(width, height), "TETRIS", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    // �������� ��������

    // �������� ������
    sf::Image icon;
    if (!icon.loadFromFile("Images/icon.png"))
    {
        return 10; // ��� ������ - �� ������� ��������� ����o�
    }
    window.setIcon(32, 32, icon.getPixelsPtr());

    // �������� ������ � ������
    Audio audio;
    try
    {
        audio.load();
    }
    catch (const std::exception& e)
    {
        // error
        return 11; // ��� ������ - �� ������� ������� ������
    }

    // �������� �������
    sf::Font font;
    if (!font.loadFromFile("Fonts/PrestigeEliteStd.otf"))
    {
        return 12; // ��� ������ - �� ������� ��������� �����
    }

    // �������� �������� ��� ����
    sf::Texture backgroundTexture;
    sf::Texture mainMenuTexture;
    sf::Texture controlsTexture;
    if (!backgroundTexture.loadFromFile("Images/backgound.jpg"))
    {
        return 13; // ��� ������ - �� ������� ��������� ��� ����
    }
    if (!mainMenuTexture.loadFromFile("Images/main_window.jpg"))
    {
        return 14; // ��� ������ - �� ������� ��������� ��� ����
    }
    if (!controlsTexture.loadFromFile("Images/controls.png"))
    {
        return 15; // ��� ������ - �� ������� ��������� �������� � �����������
    }
    // ������������� �������� �� ������
    sf::Sprite backgroundSprite;
    sf::Sprite mainMenuSprite;
    sf::Sprite controlsSprite;
    backgroundSprite.setTexture(backgroundTexture);
    mainMenuSprite.setTexture(mainMenuTexture);
    controlsSprite.setTexture(controlsTexture);


    // �������� ���� ����
    BaseWindow *game = new Game(height, width, window, audio, backgroundSprite, font);
    BaseWindow *pauseMenu = new PauseMenu(window, font, audio, backgroundSprite);
    BaseWindow *mainMenu = new MainMenu(window, font, audio, mainMenuSprite);
    BaseWindow* gameoverMenu = new GameOverMenu(window, font, audio, backgroundSprite);
    BaseWindow* gameoverPvPMenu = new GameOverPvPMenu(window, font, audio, backgroundSprite);
    BaseWindow *highscoreMenu = new HighscoreMenu(window, font, audio, backgroundSprite);
    BaseWindow *optionsMenu = new OptionsMenu(window, font, audio, backgroundSprite, controlsTexture);
    BaseWindow* gamePvPLocal = new GamePvPLocal(height, width, window, audio, backgroundSprite, font);

    // ��������� ��� ���� � ������
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
    GameState state = GameState::MainMenu; // ������ ���� ��� ����c��
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

        // ��������� ������� ������
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            windows[current_window]->handleEvents(event);

        }

        // ����������� �� ������
        window.clear();
        windows[current_window]->draw();
        window.display();

    }


    // ������������ ������
    for (auto win : windows)
    {
        delete win;
    }


    return 0;
}

