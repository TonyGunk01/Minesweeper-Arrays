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
}