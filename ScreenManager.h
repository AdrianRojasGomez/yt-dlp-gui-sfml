#pragma once
#include "IScreen.h"
#include "ScreenID.h"


class ScreenManager
{
public:
    ScreenManager()
    {
        // Inicia el array con nullptr
        for (int i = 0; i < static_cast<int>(ScreenID::Count); ++i)
            _screens[i] = nullptr;
    }

    // Registra una pantalla bajo un ID
    void registerScreen(ScreenID id, IScreen* scr)
    {
        _screens[static_cast<int>(id)] = scr;
    }

    // Activa por ID
    void set(ScreenID id)
    {
        IScreen* next = _screens[static_cast<int>(id)];
        if (next) _current = next;
    }

    // Delegados
    void HandleEvent(const sf::Event& e) { if (_current) _current->HandleEvent(e); }
    void Update(float dt) { if (_current) _current->Update(dt); }
    void Draw(sf::RenderWindow& w) const { if (_current) _current->Draw(w); }

    IScreen* current() const { return _current; }

private:
    IScreen* _screens[static_cast<int>(ScreenID::Count)];
    IScreen* _current = nullptr;
};

