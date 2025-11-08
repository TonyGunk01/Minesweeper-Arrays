#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace Gameplay
{
    class GameplayManager
    {
        private:
            Board* board;

            void initialize();
            void initializeVariables();
			void initializeBackgroundImage();

            const float background_alpha = 85.0f;

			Texture background_texture;
			Sprite background_sprite;
			string background_texture_path = "assets/textures/minesweeper_bg.png";


        public:
            GameplayManager();
            void render(RenderWindow& window);
    };
}
