#include "../../header/GameLoop/Gameplay/Cell.h"

namespace Gameplay
{
	Cell::Cell(float width, float height, Vector2i position)
	{
		initialize(width, height, position);
	}

	void Cell::initialize(float width, float height, Vector2i position)
	{
		this->position = position;

		Vector2f float_position(
			static_cast<float>(position.x),
			static_cast<float>(position.y)
		);

		cell_button = new Button(cell_texture_path, float_position, width * slice_count, height);
	}

	void Cell::render(RenderWindow& window)
	{
		if(cell_button)
			cell_button->render(window);
	}
}