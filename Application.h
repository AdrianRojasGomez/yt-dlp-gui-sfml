#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>

class Application
{
private:
	unsigned int _width = 800;
	unsigned int _height = 400;
	bool wasDownloading;
	sf::RenderWindow _window;
	Button _downloadButton;
	std::string _videoURL;

public:
	Application();

	void Run();
};

