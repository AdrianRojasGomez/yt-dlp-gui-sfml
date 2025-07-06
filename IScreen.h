#pragma once

#include <SFML/Graphics.hpp>

class IScreen
{
public:
    virtual ~IScreen() {}

    virtual void HandleEvent(const sf::Event& event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;
};
