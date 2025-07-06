#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "ScreenManager.h"

class MainScreen : public IScreen
{
private:
	ScreenManager* _manager = nullptr;

	sf::Color _backgroundColor; // Color de fondo
	sf::Font _font; // Fuente para el texto
	sf::Text _titleText; // Título

public:
    MainScreen(const sf::Vector2u& windowSize, ScreenManager* manager);
    ~MainScreen() override {}

    void HandleEvent(const sf::Event& e) override;
    void Update(float dt)                override;
    void Draw(sf::RenderWindow& window) const override;

	sf::Color getBackgroundColor() const { return _backgroundColor; }
};
