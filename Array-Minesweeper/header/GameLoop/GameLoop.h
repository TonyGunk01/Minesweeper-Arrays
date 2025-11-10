#pragma once
#include "../GameWindow/GameWindowManager.h"
#include "../Event/EventPollingManager.h"
#include "../UI/SplashScreen/SplashScreenManager.h"
#include "Gameplay/GameplayManager.h"
#include "../UI/MainMenu/MainMenuManager.h"

using namespace GameWindow;
using namespace Events;
using namespace Gameplay;
using namespace UIElements;
using namespace UI;
using namespace sf;

enum class GameState
{
    SPLASH_SCREEN,
    MAIN_MENU,
    GAMEPLAY,
    EXIT
};

class GameLoop 
{
    private:
        GameWindowManager* window_manager;
        EventPollingManager* event_manager;

        RenderWindow* game_window;
        SplashScreenManager* splash_screen_manager;
        GameplayManager* gameplay_manager;
        MainMenuManager* main_menu_manager;

        static GameState current_state;

        void initialize();
        void update();
        void render();

    public:
        GameLoop();
        ~GameLoop();

        void run();
        static void setGameState(GameState state_to_set);
};