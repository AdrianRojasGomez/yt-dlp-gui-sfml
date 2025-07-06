#include "Button.h"
#include <SFML/Graphics.hpp>

Button::Button()
{
	// Default constructor is empty
}

void Button::Configure(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
{
	
	shape.setPosition(position);
	shape.setSize(size);
	shape.setOrigin(size * 0.5f);
	shape.setFillColor(color);
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

bool Button::isClicked(const sf::Vector2f& mousePos)
{
	return shape.getGlobalBounds().contains(mousePos);
}
