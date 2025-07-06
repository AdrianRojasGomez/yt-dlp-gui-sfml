#include <SFML/Graphics.hpp>
#include "DownloadScreen.h"
#include "ScreenManager.h"

DownloadScreen::DownloadScreen(const sf::Vector2u& windowSize, ScreenManager* manager) : _manager(manager)
{
	_backgroundColor = sf::Color(220, 185, 138);
	_font.loadFromFile("res/fonts/monogram.ttf");
	_titleText.setFont(_font);
	_titleText.setString("URL Screen");
	_titleText.setCharacterSize(60);
	_titleText.setFillColor(sf::Color::Black);
	sf::FloatRect tBounds = _titleText.getLocalBounds();
	_titleText.setOrigin(0, tBounds.height / 2.f);
	_titleText.setPosition(10.0f, 5.f);
}

void DownloadScreen::HandleEvent(const sf::Event& e)
{

}

void DownloadScreen::Update(float dt)
{

}

void DownloadScreen::Draw(sf::RenderWindow& window) const
{
	window.draw(_titleText);
}
