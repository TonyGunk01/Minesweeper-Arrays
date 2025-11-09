#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Time/TimeManager.h"
#include <SFML/Graphics.hpp>

using namespace UIElements;
using namespace Events;
using namespace sf;
using namespace std;

namespace Gameplay
{
    using namespace Events;
    using namespace Time;

    enum class GameResult
    {
        NONE,
        WON,
        LOST
    };

    class GameplayManager
    {
        private:
            const float background_alpha = 85.f;
            const float max_level_duration = 150.0f;
            const float game_over_time = 11.0f;
            float remaining_time;

            Texture background_texture;
            Sprite background_sprite;
            string background_texture_path = "assets/textures/minesweeper_bg.png";

            Board* board;
            GameResult game_result;

            void initialize();
            void initializeBackgroundImage();
            void initializeVariables();

            void updateRemainingTime();
            void processTimeOver();
            void handleGameplay(EventPollingManager& eventManager, RenderWindow& window);
            bool hasGameEnded();


        public:
            GameplayManager();
            ~GameplayManager() = default;

            void render(RenderWindow& window);
            void update(EventPollingManager& eventManager, RenderWindow& window);
            void setGameResult(GameResult gameResult);
    };
}