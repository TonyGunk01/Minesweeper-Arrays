#include <iostream>
#include "../../../../header/UI/UIElements/GameplayUI/GameplayUI.h"
#include "../../../../header/GameLoop/Gameplay/GameplayManager.h"

namespace UI 
{
    GameplayUI::GameplayUI(GameplayManager* gameplay_manager)
    {
        initialize(gameplay_manager);
    }

    void GameplayUI::initialize(GameplayManager* gameplay_manager)
    {
        this->gameplay_manager = gameplay_manager;
        loadFonts();
        initializeTexts();
        initializeButton();
        registerButtonCallback();
    }

    void GameplayUI::loadFonts()
    {
        if (!bubbleBobbleFont.loadFromFile("assets/fonts/bubbleBobble.ttf"))
            cerr << "Error loading bubbleBobble font!" << endl;

        if (!dsDigibFont.loadFromFile("assets/fonts/DS_DIGIB.ttf"))
            cerr << "Error loading DS_DIGIB font!" << endl;
    }

    void GameplayUI::initializeTexts()
    {
        mineText.setFont(dsDigibFont);
        mineText.setCharacterSize(fontSize);
        mineText.setFillColor(textColor);
        mineText.setPosition(mineTextLeftOffset, mineTextTopOffset);
        mineText.setString("000");

        timeText.setFont(dsDigibFont);
        timeText.setCharacterSize(fontSize);
        timeText.setFillColor(textColor);
        timeText.setPosition(timeTextLeftOffset, timeTextTopOffset);
        timeText.setString("000");
    }

    void GameplayUI::update(int remaining_mines, int remaining_time, EventPollingManager& eventManager, RenderWindow& window)
    {
        mineText.setString(std::to_string(remaining_mines));
        timeText.setString(std::to_string(remaining_time));
        restartButton->handleButtonInteractions(eventManager, window);
    }

    void GameplayUI::render(RenderWindow& window)
    {
        window.draw(mineText);
        window.draw(timeText);
        restartButton->render(window);
    }

    void GameplayUI::initializeButton() 
    {
        restartButton = new Button(restartButtonTexturePath, 
            Vector2f(restartButtonLeftOffset, restartButtonTopOffset), buttonWidth, buttonHeight);
    }

    void GameplayUI::registerButtonCallback() 
    {
        restartButton->registerCallbackFunction([this](UIElements::MouseButtonType buttonType) {
            RestartButtonCallback(buttonType);
            });
    }

    void GameplayUI::RestartButtonCallback(MouseButtonType mouse_button_type) 
    {
        if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON) 
        {
            SoundManager::PlaySound(SoundType::BUTTON_CLICK);
            gameplay_manager->restartGame();
        }
    }
}
