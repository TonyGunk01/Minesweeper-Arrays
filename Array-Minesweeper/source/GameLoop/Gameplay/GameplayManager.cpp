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
    remaining_time = max_level_duration;
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

void GameplayManager::handleGameplay(EventPollingManager& eventManager, RenderWindow& window)
{
    updateRemainingTime();
    board->update(eventManager, window);
}

void GameplayManager::updateRemainingTime()
{
    remaining_time = TimeManager::getDeltaTime();
    processTimeOver();
}

void GameplayManager::processTimeOver()
{
    if (remaining_time <= 0)
    {
        remaining_time = 0;
        game_result = GameResult::LOST;
    }
}