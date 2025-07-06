#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ScreenManager.h"
#include "MainScreen.h"
#include "DownloadScreen.h"



class Application
{
private:
	const unsigned int _width = 800;
	const unsigned int _height = 400;
	sf::RenderWindow _window;

	ScreenManager _states;
	MainScreen _mainScreen;
	DownloadScreen _downloadScreen;





public:
	Application();

	void Run();
};

