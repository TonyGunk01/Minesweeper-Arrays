#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace Gameplay
{
	class Board
	{
		private:
			const float boardWidth = 866.f;
			const float boardHeight = 1080.0f;
			const float boardPosition = 530.0f;

			const string boardTexturePath = "assets/textures/board.png";
			Texture boardTexture;
			Sprite boardSprite;

			void initializeBoardImage();
			void initialize();

		public:
			Board();
			void render(RenderWindow& window);
	};
}