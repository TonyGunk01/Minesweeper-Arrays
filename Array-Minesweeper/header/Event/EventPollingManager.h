#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

using namespace sf;

namespace Events
{
    enum class MouseButtonState
    {
        PRESSED,
        HELD,
        RELEASED,
    };

    class EventPollingManager
    {
        private:
            Event game_event;
            RenderWindow* game_window;

            MouseButtonState left_mouse_button_state;
            MouseButtonState right_mouse_button_state;

            void initializeVariables(RenderWindow* window);
            void updateMouseButtonState(MouseButtonState& button_state, Mouse::Button button_type);

            bool hasQuitGame();
            bool isKeyboardEvent();
            bool isGameWindowOpen();
            bool gameWindowWasClosed();

        public:
            EventPollingManager(RenderWindow* window);
            ~EventPollingManager();

            void processEvents();
            void update();

            bool pressedEscapeKey();
            bool pressedLeftMouseButton();
            bool pressedRightMouseButton();

            Vector2i getMousePosition();
    };
}