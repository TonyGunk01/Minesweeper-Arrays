#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"

using namespace sf;
using namespace std;
using namespace Sounds;

namespace Gameplay
{
    enum class BoardState
    {
        FIRST_CELL,
        PLAYING,
        COMPLETED,
    };

    class GameplayManager;

    class Board
    {
        private:
			default_random_engine randomEngine;
			random_device randomDevice;

            int flaggedCells;
			static const int minesCount = 9;

            static const int numberOfRows = 9;
            static const int numberOfColumns = 9;

            Cell* cell[numberOfRows][numberOfColumns];
            GameplayManager* gameplay_manager;

            BoardState boardState;
            Vector2i first_cell_position;
            bool isInvalidMinePosition(Vector2i first_cell_position, int x, int y);

            const float horizontalCellPadding = 115.f;
            const float verticalCellPadding = 329.f;

            const float boardWidth = 866.f;
            const float boardHeight = 1080.f;
            const float boardPosition = 530.f;
            const string boardTexturePath = "assets/textures/board.png";
            Texture boardTexture;
            Sprite boardSprite;

            void populateBoard(Vector2i cell_position);
			void populateMines(Vector2i cell_position);
            
            void initialize(GameplayManager* gameplay_manager);
            void initializeVariables(GameplayManager* gameplay_manager);
            void initializeBoardImage();

            void createBoard();
            float getCellWidthInBoard() const;
            float getCellHeightInBoard() const;
            void deleteBoard();

			int countMinesAround(Vector2i cell_position);
            void populateCells();
            bool isValidCellPosition(Vector2i cell_position);

			void openCell(Vector2i cell_position);
            void toggleFlag(Vector2i cell_position);

            void processCellType(Vector2i cell_position);
            void processEmptyCell(Vector2i cell_position);

            void processMineCell(Vector2i cell_position);

        public:
            Board(GameplayManager* gameplayManager);
            ~Board();

            void render(RenderWindow& window);
            void update(EventPollingManager& eventManager, RenderWindow& window);

            void onCellButtonClicked(Vector2i cell_position, MouseButtonType mouse_button_type);

            void revealAllMines();

            BoardState getBoardState() const;
            void setBoardState(BoardState state);

            bool areAllCellsOpen();
            void flagAllMines();

            int getRemainingMinesCount() const;
    };
}