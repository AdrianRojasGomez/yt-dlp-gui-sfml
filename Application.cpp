#include <SFML/System.hpp> 
#include "Application.h"
#include "Button.h"
#include "Downloader.h"

Application::Application()
{
	wasDownloading = false;
	_window.create(sf::VideoMode(_width, _height), "YT GUI Downloader", sf::Style::Titlebar | sf::Style::Close);
	_videoURL = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
	_downloadButton.Configure(sf::Vector2f(_width * 0.5f, _height * 0.5f), sf::Vector2f(200, 60), sf::Color(100, 149, 237));

}

void Application::Run()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                _window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) 
            {
                sf::Vector2f mousePos((float)event.mouseButton.x, (float)event.mouseButton.y);
                if (_downloadButton.isClicked(mousePos) && !Downloader::IsBusy())
                {
                  Downloader::DownloadAudio(_videoURL);
                }
            }
        }

        bool isDownloading = Downloader::IsBusy();

        if (isDownloading && !wasDownloading)
            _downloadButton.setColor(sf::Color::Red);
        else
			_downloadButton.setColor(sf::Color(100, 149, 237));

        _window.clear(sf::Color::White);
        _downloadButton.Draw(_window);
        _window.display();
    }
}

