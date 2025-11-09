#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElements/Button/Button.h"
#include "../../header/Event/EventPollingManager.h"

namespace UI 
{
    using namespace UIElements;

    class MainMenuManager 
    {
        private:
            RenderWindow* game_window;
            Texture background_texture;
            Sprite background_sprite;

            Button* play_button;
            Button* quit_button;

            const string background_texture_path = "assets/textures/minesweeper_bg.png";
            const string play_button_texture_path = "assets/textures/play_button.png";
            const string quit_button_texture_path = "assets/textures/quit_button.png";

            const float button_width = 300.f;
            const float button_height = 100.f;
            const float play_button_y_position = 600.f;
            const float quit_button_y_position = 750.f;
            const float background_alpha = 85.f;

            void initialize();
            void initializeBackground();
            void initializeButtons();

            void playButtonCallback(MouseButtonType mouse_button_type);
            void quitButtonCallback(MouseButtonType mouse_button_type);
            void registerButtonCallbacks();

            Vector2f getButtonPosition(float offsetX, float offsetY);

        public:
            MainMenuManager(sf::RenderWindow* window);
            ~MainMenuManager();

            void update(EventPollingManager eventManager);
            void render();
            void show();

            void checkForButtonClicks(EventPollingManager& eventManager);
    };
}