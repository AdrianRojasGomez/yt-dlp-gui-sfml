#include "Application.h"

Application::Application()  :
        _window(sf::VideoMode(_width, _height), "YT GUI Downloader", sf::Style::Titlebar | sf::Style::Close),
        _mainScreen(_window.getSize(), &_states),
        _downloadScreen(_window.getSize(), &_states)
{
    _states.registerScreen(ScreenID::Main, &_mainScreen);
    _states.registerScreen(ScreenID::Download, &_downloadScreen);

    _states.set(ScreenID::Main);
}

void Application::Run()
{
    sf::Clock clock;

    while (_window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        // ----------- Eventos -----------
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();

            _states.HandleEvent(event);
        }

        // ----------- Lógica -----------
        _states.Update(dt);

        // ----------- Render -----------
		_window.clear(_mainScreen.getBackgroundColor());
        _states.Draw(_window);
        _window.display();
    }
}

