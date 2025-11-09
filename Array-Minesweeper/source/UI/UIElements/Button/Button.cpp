#include "../../header/UI/UIElements/Button/Button.h"
#include <iostream>

namespace UIElements 
{
    Button::Button(const string& texturePath, const Vector2f& position, float width, float height) 
    {
        initialize(texturePath, position, width, height);
    }

    void Button::initialize(const string& texturePath, const Vector2f& position, float width, float height) 
    {
        if (!button_texture.loadFromFile(texturePath)) 
        {
            cerr << "Failed to load button texture: " << texturePath << endl;
            return;
        }

        buttonSprite.setTexture(button_texture);
        buttonSprite.setPosition(position);
        buttonSprite.setScale(width / button_texture.getSize().x, height / button_texture.getSize().y);
    }

    void Button::render(RenderWindow& window) const 
    {
        window.draw(buttonSprite);
    }

    void Button::setTextureRect(const IntRect& rect) 
    {
        buttonSprite.setTextureRect(rect);
    }

    bool Button::isMouseOnSprite(EventPollingManager& event_manager, const RenderWindow& window)
    {
        Vector2i mouse_position = event_manager.getMousePosition();

        return buttonSprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));
    }

    void Button::handleButtonInteractions(EventPollingManager& event_manager, const RenderWindow& window) 
    {
        if (event_manager.pressedLeftMouseButton() && isMouseOnSprite(event_manager, window))
            cout << "Left Click Detected" << endl;

        else if (event_manager.pressedRightMouseButton() && isMouseOnSprite(event_manager, window))
            cout << "Right Click Detected" << endl;
    }

    void Button::registerCallbackFunction(CallbackFunction button_callback) 
    {
        callback_function = button_callback;
    }

    void Button::handleButtonInteractions(EventPollingManager& event_manager, const sf::RenderWindow& window) 
    {
        if (event_manager.pressedLeftMouseButton() && isMouseOnSprite(event_manager, window)) 
        {
            callback_function(MouseButtonType::LEFT_MOUSE_BUTTON);
        }

        else if (event_manager.pressedRightMouseButton() && isMouseOnSprite(event_manager, window)) 
        {
            callback_function(MouseButtonType::RIGHT_MOUSE_BUTTON);
        }
    }
}