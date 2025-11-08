#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace UI 
{
    class SplashScreenManager 
    {
        private:
            RenderWindow* game_window;
            Texture logo_texture;
            Sprite logo_sprite;

            const float logo_width = 600.f;
            const float logo_height = 134.f;
            const float logo_animation_duration = 2.0f;
            const string logo_texture_path = "assets/textures/outscal_logo.png";

            float elapsed_time = 0.0f;

            void initialize();
            Vector2f getLogoPosition();
            void drawLogo();

        public:
            SplashScreenManager(RenderWindow* window);
            ~SplashScreenManager();

            void update();
            void render();
    };
}