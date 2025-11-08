#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

using namespace sf;

namespace Gameplay
{
    GameplayManager::GameplayManager()
    {
        initialize();
        initializeBackgroundImage();
        initializeVariables();
    }

    void GameplayManager::initialize()
    {
        initializeVariables();
    }

    void GameplayManager::initializeVariables()
    {
        board = new Board();
    }

    void GameplayManager::initializeBackgroundImage()
    {
        if (!background_texture.loadFromFile(background_texture_path))
        {
            cerr << "Failed to load gameplay background texture!" << endl;
            return;
        }

        background_sprite.setTexture(background_texture);
        background_sprite.setColor(Color(255, 255, 255, background_alpha));
    }

    void GameplayManager::render(RenderWindow& window)
    {
        board->render(window);
        window.draw(background_sprite);
	}
}