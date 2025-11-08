#include "../../header/Event/EventPollingManager.h"
#include "../../header/GameWindow/GameWindowManager.h"

using namespace sf;

namespace Events
{
    using namespace GameWindow;

    EventPollingManager::EventPollingManager(RenderWindow* window) 
    { 
        initializeVariables(window); 
    }

    EventPollingManager::~EventPollingManager() = default;

    void EventPollingManager::initializeVariables(RenderWindow* window)
    {
        game_window = window;
        left_mouse_button_state = MouseButtonState::RELEASED;
        right_mouse_button_state = MouseButtonState::RELEASED;
    }

    void EventPollingManager::processEvents()
    {
        if (isGameWindowOpen())
        {
            while (game_window->pollEvent(game_event))
            {
                if (gameWindowWasClosed() || hasQuitGame())
                    game_window->close();
            }
        }
    }

    void EventPollingManager::update()
    {
        updateMouseButtonState(left_mouse_button_state, Mouse::Left);
        updateMouseButtonState(right_mouse_button_state, Mouse::Right);
    }

    void EventPollingManager::updateMouseButtonState(MouseButtonState& button_state, Mouse::Button button_type)
    {
        if (Mouse::isButtonPressed(button_type))
        {
            switch (button_state)
            {
                case MouseButtonState::RELEASED:
                    button_state = MouseButtonState::PRESSED;
                    break;

                case MouseButtonState::PRESSED:
                    button_state = MouseButtonState::HELD;
                    break;
            }
        }

        else
            button_state = MouseButtonState::RELEASED;
    }

    bool EventPollingManager::isGameWindowOpen() 
    { 
        return game_window != nullptr; 
    }

    bool EventPollingManager::gameWindowWasClosed() 
    { 
        return game_event.type == Event::Closed; 
    }

    bool EventPollingManager::hasQuitGame() 
    { 
        return (isKeyboardEvent() && pressedEscapeKey()); 
    }

    bool EventPollingManager::isKeyboardEvent() 
    { 
        return game_event.type == Event::KeyPressed; 
    }

    bool EventPollingManager::pressedEscapeKey() 
    { 
        return game_event.key.code == Keyboard::Escape; 
    }

    bool EventPollingManager::pressedLeftMouseButton() 
    { 
        return left_mouse_button_state == MouseButtonState::PRESSED; 
    }

    bool EventPollingManager::pressedRightMouseButton() 
    { 
        return right_mouse_button_state == MouseButtonState::PRESSED; 
    }

    Vector2i EventPollingManager::getMousePosition() 
    { 
        return Mouse::getPosition(*game_window); 
    }
}