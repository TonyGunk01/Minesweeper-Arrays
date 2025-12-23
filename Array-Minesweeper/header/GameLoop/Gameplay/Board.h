#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"

namespace Gameplay
{
    class GameplayManager;

    enum class BoardState
    {
        FIRST_CELL,
        PLAYING,
        COMPLETED,
    };

    class Board
    {
        private:
            GameplayManager *gameplay_manager;

            static const int numberOfRows = 9;
            static const int numberOfColumns = 9;
            static const int minesCount = 9;

            BoardState boardState;
            Cell* cell[numberOfRows][numberOfColumns];
            int flaggedCells;
        
            const float horizontalCellPadding = 115.f;
            const float verticalCellPadding = 329.f;

            const float boardWidth = 866.f;
            const float boardHeight = 1080.f;
            const float boardPosition = 530.f;
            const std::string boardTexturePath = "assets/textures/board.png";
            sf::Texture boardTexture;
            sf::Sprite boardSprite;

            std::default_random_engine randomEngine;
            std::random_device randomDevice;

            void initialize(GameplayManager* gameplay_manager);
            void initializeVariables(GameplayManager* gameplay_manager);
            void initializeBoardImage();

            void createBoard();
            float getCellWidthInBoard() const;
            float getCellHeightInBoard() const;
            void deleteBoard();

            void openCell(sf::Vector2i cell_position);
            void toggleFlag(sf::Vector2i cell_position);
        
            void populateBoard(sf::Vector2i first_cell_position);
            void populateMines(sf::Vector2i first_cell_position);
            bool isInvalidMinePosition(sf::Vector2i first_cell_position, int x, int y);
            int countMinesAround(sf::Vector2i cell_position);
            void populateCells();
        
            void processCellType(sf::Vector2i cell_position);
            void processEmptyCell(sf::Vector2i cell_position);
            void processMineCell(sf::Vector2i cell_position);


        public:
            Board(GameplayManager* gameplayManager);
            ~Board();

            void update(Event::EventPollingManager& eventManager, sf::RenderWindow& window);
            void render(sf::RenderWindow& window);

            void reset();
            void onCellButtonClicked(sf::Vector2i cell_position, MouseButtonType mouse_button_type);

            bool isValidCellPosition(sf::Vector2i cell_position);

            BoardState getBoardState() const;
            void setBoardState(BoardState state);
            int getMinesCount() const;
        
            bool areAllCellsOpen();
            void flagAllMines();
            void revealAllMines();
    };
}