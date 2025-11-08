#include "../../../../header/UI/UIElements/Button/Button.h"
#include <iostream>

namespace UIElements
{
	Button::Button(const string& texturePath, const Vector2f& position, float width, float height)
	{
		initialize(texturePath, position, width, height);
	}

	void Button::initialize(const string& texturePath, const Vector2f& position, float width, float height)
	{
		if (!buttonTexture.loadFromFile(texturePath))
		{
			cerr << "Failed to load button texture: " << texturePath << endl;
			return;
		}

		buttonSprite.setTexture(buttonTexture);
		buttonSprite.setPosition(position);

		buttonSprite.setScale(
			width / buttonTexture.getSize().x,
			height / buttonTexture.getSize().y
		);
	}

	void Button::render(RenderWindow& window) const
	{
		window.draw(buttonSprite);
	}
}