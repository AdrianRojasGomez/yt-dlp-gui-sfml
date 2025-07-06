#pragma once
#include <SFML/Graphics.hpp>
#include "IScreen.h"
#include "ScreenManager.h"

class DownloadScreen : public IScreen
{
private:
	ScreenManager* _manager = nullptr; // Gestor de pantallas

    sf::Color _backgroundColor; // Color de fondo
    sf::Font _font; // Fuente para el texto
    sf::Text _titleText; // Título



public:
    explicit DownloadScreen(const sf::Vector2u& windowSize, ScreenManager* manager);
    ~DownloadScreen() override {}

    void HandleEvent(const sf::Event& e) override;
    void Update(float dt)                override;
    void Draw(sf::RenderWindow& window) const override;

};