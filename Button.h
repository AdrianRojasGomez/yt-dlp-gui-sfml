#pragma once
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape shape;

public:
	Button();
	void Configure(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);

	void Draw(sf::RenderWindow& window);
	bool isClicked(const sf::Vector2f& mousePos);
	void setColor(const sf::Color& color) { shape.setFillColor(color); }
};

