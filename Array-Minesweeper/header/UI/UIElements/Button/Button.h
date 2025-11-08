#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include <functional>

using namespace sf;
using namespace std;

namespace UIElements 
{
    enum class MouseButtonType
    {
        LEFT_MOUSE_BUTTON,
        RIGHT_MOUSE_BUTTON
    };

    enum class ButtonState
    {
        PRESSED,
        HELD,
        RELEASED
    };

    class Button 
    {
        private:
            Texture button_texture;
            Sprite buttonSprite;

            void initialize(const string& texture_path, const Vector2f& position, float width, float height);

        public:
            Button(const string& texture_path, const Vector2f& position, float width, float height);

            void render(RenderWindow& window) const;

            void setTextureRect(const IntRect& rect);
    };
}