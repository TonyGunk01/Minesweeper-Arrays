#pragma once

#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"
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

	class Button
	{
		private:
			Texture buttonTexture;
			Sprite buttonSprite;

			void initialize(const string& texturePath, const Vector2f& position, float width, float height);

		public:
			Button(const string& texturePath, const Vector2f& position, float width, float height);
			void render(RenderWindow& window) const;
	};
}