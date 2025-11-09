#include <iostream>
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include "../../../header/Time/TimeManager.h"

using namespace Gameplay;

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
    board = new Board(this);
}

void GameplayManager::render(RenderWindow& window)
{
    window.draw(background_sprite);
    board->render(window);
}

void GameplayManager::update(EventPollingManager& eventManager, RenderWindow& window)
{
    if (!hasGameEnded())
        board->update(eventManager, window);
}

void GameplayManager::setGameResult(GameResult gameResult)
{
    this->game_result = gameResult;
}

bool GameplayManager::hasGameEnded()
{
    return game_result != GameResult::NONE;
}
