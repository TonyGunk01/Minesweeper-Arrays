#include "../../header/GameLoop/Gameplay/Board.h"
#include <iostream>

using namespace std;

namespace Gameplay
{
	Board::Board() 
	{ 
		initialize(); 
	}
	
	void Board::initialize()
	{
		initializeBoardImage();
	}
	
	void Board::initializeBoardImage()
	{
		if (!boardTexture.loadFromFile(boardTexturePath))
		{
			cerr << "Failed to load board texture!" << endl;
			return;
		}

		boardSprite.setTexture(boardTexture);
		boardSprite.setPosition(boardPosition, 0.0f);	
		boardSprite.setScale(
			boardWidth / boardTexture.getSize().x,
			boardHeight / boardTexture.getSize().y
		);
	}
	
	void Board::render(RenderWindow& window)
	{
		window.draw(boardSprite);
	}
}