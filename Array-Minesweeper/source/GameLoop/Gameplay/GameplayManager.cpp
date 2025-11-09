#include <iostream>
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include "../../../header/Time/TimeManager.h"

namespace Gameplay
{
    GameplayManager::GameplayManager() 
    { 
        initialize(); 
    }

    void GameplayManager::initialize()
    {
        initializeBackgroundImage();
        initializeVariables();
    }

    void GameplayManager::initializeBackgroundImage()
    {
        if (!background_texture.loadFromFile(background_texture_path))
        {
            cerr << "Failed to load background texture!" << endl;
            return;
        }

        background_sprite.setTexture(background_texture);
        background_sprite.setColor(Color(255, 255, 255, background_alpha));
    }

    void GameplayManager::initializeVariables()
    {
        board = new Board();
    }

    void GameplayManager::render(RenderWindow& window)
    {
        window.draw(background_sprite);
        board->render(window);
    }

    void GameplayManager::update(EventPollingManager& eventManager, RenderWindow& window)
    {
        board->update(eventManager, window);
    }
}