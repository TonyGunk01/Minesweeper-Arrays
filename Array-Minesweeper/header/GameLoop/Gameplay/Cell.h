#pragma once

#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElements/Button/Button.h"
#include "../../header/Event/EventPollingManager.h"
#include <string>

using namespace UIElements;
using namespace sf;
using namespace std;

namespace Gameplay
{ 
	class Cell
	{
		private:
			Vector2i position;
			const int tile_size = 128;
			const int slice_count = 12;
			const string cell_texture_path = "assets/textures/cells.png";

			Button* cell_button;

			void initialize(float width, float height, Vector2i position);

		public:
			Cell(float width, float height, Vector2i position);

			~Cell();

			void render(RenderWindow& window);

	};
}