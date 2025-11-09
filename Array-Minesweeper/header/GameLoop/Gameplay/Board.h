#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"

using namespace sf;
using namespace std;

namespace Gameplay
{
    class Board
    {
        private:
			// Randomization
			default_random_engine randomEngine;
			random_device randomDevice;

			// Number of mines
			static const int minesCount = 9;

            // Board Constants
            static const int numberOfRows = 9;
            static const int numberOfColumns = 9;

            // State and View Members
            Cell* cell[numberOfRows][numberOfColumns];

            const float horizontalCellPadding = 115.f;
            const float verticalCellPadding = 329.f;

            // Board Rendering
            const float boardWidth = 866.f;
            const float boardHeight = 1080.f;
            const float boardPosition = 530.f;
            const string boardTexturePath = "assets/textures/board.png";
            Texture boardTexture;
            Sprite boardSprite;

            // Populating the board
            void populateBoard();
			void populateMines();
            void initializeVariables();
            
            // Private helper methods
            void initialize();
            void initializeBoardImage();

            void createBoard();
            float getCellWidthInBoard() const;
            float getCellHeightInBoard() const;
            void deleteBoard();

			int countMinesAround(Vector2i cell_position);
            void populateCells();
            bool isValidCellPosition(Vector2i cell_position);

        public:
            Board();
            ~Board();

            void render(RenderWindow& window);
            void update(EventPollingManager& eventManager, RenderWindow& window);

            void onCellButtonClicked(Vector2i cell_position, MouseButtonType mouse_button_type);
    };
}