#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

namespace Gameplay
{
    Board::Board(GameplayManager* gameplayManager)
    {
        initialize(gameplayManager);
    }

    Board::~Board()
    {
        deleteBoard();
    }

    void Board::initialize(GameplayManager* gameplayManager)
    {
        initializeBoardImage();
        initializeVariables(gameplayManager);
        createBoard();
    }

    void Board::initializeBoardImage()
    {
        if (!boardTexture.loadFromFile(boardTexturePath))
        {
            cerr << "Failed to load board texture!" << endl;
            return;
        }

        boardSprite.setTexture(boardTexture);
        boardSprite.setPosition(boardPosition, 0);
        boardSprite.setScale(boardWidth / boardTexture.getSize().x, boardHeight / boardTexture.getSize().y);
    }

    void Board::initializeVariables(GameplayManager* gameplay_manager)
    {
        this->gameplay_manager = gameplay_manager;
        randomEngine.seed(randomDevice());
        boardState = BoardState::FIRST_CELL;
    }

    void Board::createBoard()
    {
        float cell_width = getCellWidthInBoard();
        float cell_height = getCellHeightInBoard();

        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                cell[row][col] = new Cell(cell_width, cell_height, Vector2i(row, col), this);
    }

    void Board::deleteBoard()
    {
        delete cell;
    }

    void Board::render(RenderWindow& window)
    {
        window.draw(boardSprite);

        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                cell[row][col]->render(window);
    }

    float Board::getCellWidthInBoard() const
    {
        return (boardWidth - horizontalCellPadding) / numberOfColumns;
    }

    float Board::getCellHeightInBoard() const
    {
        return (boardHeight - verticalCellPadding) / numberOfRows;
    }

    void Board::populateMines(Vector2i first_cell_position)
    {
        uniform_int_distribution<int> x_dist(0, numberOfColumns - 1);
        uniform_int_distribution<int> y_dist(0, numberOfRows - 1);

        int mines_placed = 0;

        while (mines_placed < minesCount)
        {
            int x = x_dist(randomEngine);
            int y = y_dist(randomEngine);

            if (isInvalidMinePosition(first_cell_position, x, y))
                continue;

            cell[x][y]->setCellType(CellType::MINE);
            ++mines_placed;
        }
    }

    void Board::populateBoard(Vector2i cell_position)
    {
        populateMines(first_cell_position);
        populateCells();
    }

    int Board::countMinesAround(Vector2i cell_position)
    {
        int mines_around = 0;

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0 || !isValidCellPosition(Vector2i(cell_position.x + dx, cell_position.y + dy)))
                    continue;

                if (cell[cell_position.x + dx][cell_position.y + dy]->getCellType() == CellType::MINE)
                    mines_around++;
            }
        }
        return mines_around;
    }

    bool Board::isValidCellPosition(Vector2i cell_position)
    {
        return (cell_position.x >= 0 && cell_position.x < numberOfColumns &&
            cell_position.y >= 0 && cell_position.y < numberOfRows);
    }

    void Board::populateCells()
    {
        for (int row = 0; row < numberOfRows; ++row)
        {
            for (int col = 0; col < numberOfColumns; ++col)
            {
                if (cell[row][col]->getCellType() != CellType::MINE)
                {
                    int mines_around = countMinesAround(Vector2i(row, col));
                    cell[row][col]->setCellType(static_cast<CellType>(mines_around));
                }
            }
        }
    }

    void Board::update(EventPollingManager& eventManager, RenderWindow& window)
    {
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                cell[row][col]->update(eventManager, window);
    }

    void Board::onCellButtonClicked(Vector2i cell_position, MouseButtonType mouse_button_type)
    {
        if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON)
        {
            SoundManager::PlaySound(SoundType::BUTTON_CLICK);
            openCell(cell_position);
        }

        else if (mouse_button_type == MouseButtonType::RIGHT_MOUSE_BUTTON)
        {
            SoundManager::PlaySound(SoundType::FLAG);
            toggleFlag(cell_position);
        }
    }

    void Board::openCell(Vector2i cell_position)
    {
        if (!cell[cell_position.x][cell_position.y]->canOpenCell())
            return;

        if (boardState == BoardState::FIRST_CELL)
        {
            populateBoard(cell_position);
            boardState = BoardState::PLAYING;
        }

        processCellType(cell_position);
    }

    void Cell::open()
    {
        setCellState(CellState::OPEN);
    }

    void Board::toggleFlag(Vector2i cell_position)
    {
        cell[cell_position.x][cell_position.y]->toggleFlag();
        flaggedCells += (cell[cell_position.x][cell_position.y]->getCellState() == CellState::FLAGGED) ? 1 : -1;
    }

    void Board::processCellType(Vector2i cell_position)
    {
        switch (cell[cell_position.x][cell_position.y]->getCellType())
        {
            case CellType::EMPTY:
                processEmptyCell(cell_position);
                break;

            case CellType::MINE:
                processMineCell(cell_position);
                break;

            default:
                cell[cell_position.x][cell_position.y]->open();
                break;
        }
    }

    void Board::processEmptyCell(Vector2i cell_position)
    {
        CellState cell_state = cell[cell_position.x][cell_position.y]->getCellState();

        switch (cell_state)
        {
            case::Gameplay::CellState::OPEN:
                return;

            default:
                cell[cell_position.x][cell_position.y]->open();
        }

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                Vector2i next_cell_position = Vector2i(dx + cell_position.x, dy + cell_position.y);

                if ((dx == 0 && dy == 0) || !isValidCellPosition(next_cell_position))
                    continue;

                CellState next_cell_state = cell[next_cell_position.x][next_cell_position.y]->getCellState();

                if (next_cell_state == CellState::FLAGGED)
                    toggleFlag(next_cell_position);

                openCell(next_cell_position);
            }
        }
    }

    void Board::processMineCell(Vector2i cell_position)
    {
        gameplay_manager->setGameResult(GameResult::LOST);
    }

    void Board::revealAllMines()
    {
        for (int row = 0; row < numberOfRows; row++)
            for (int col = 0; col < numberOfColumns; col++)
                if (cell[row][col]->getCellType() == CellType::MINE)
                    cell[row][col]->setCellState(CellState::OPEN);
    }

    bool Board::isInvalidMinePosition(Vector2i first_cell_position, int x, int y) 
    {
        return (x == first_cell_position.x && y == first_cell_position.y) ||
            cell[x][y]->getCellType() == CellType::MINE;
    }

    BoardState Board::getBoardState() const
    {
        return boardState;
    }

    void Board::setBoardState(BoardState state)
    {
        boardState = state;
    }

    bool Board::areAllCellsOpen()
    {
        int total_cells = numberOfRows * numberOfColumns;
        int open_cells = 0;

        for (int row = 0; row < numberOfRows; ++row) 
            for (int col = 0; col < numberOfColumns; ++col) 
                if (cell[row][col]->getCellState() == CellState::OPEN &&
                    cell[row][col]->getCellType() != CellType::MINE) 
                    open_cells++;
               
        return open_cells == (total_cells - minesCount);
    }

    void Board::flagAllMines()
    {
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col)
                if (cell[row][col]->getCellType() == CellType::MINE &&
                    cell[row][col]->getCellState() != CellState::FLAGGED)
                    cell[row][col]->setCellState(CellState::FLAGGED);
    }

    int Board::getRemainingMinesCount() const 
    {
        return minesCount - flaggedCells;
    }

    void Board::reset() 
    {
        for (int row = 0; row < numberOfRows; ++row)
            for (int col = 0; col < numberOfColumns; ++col) 
                cell[row][col]->reset();

        flaggedCells = 0;
        boardState = BoardState::FIRST_CELL;
    }
}

                