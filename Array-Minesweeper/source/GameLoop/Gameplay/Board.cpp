#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

namespace Gameplay
{
    Board::Board()
    {
        initialize();
    }

    Board::~Board()
    {
        deleteBoard();
    }

    void Board::initialize()
    {
        initializeBoardImage();
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


    void Board::createBoard()
    {
        float cell_width = getCellWidthInBoard();
        float cell_height = getCellHeightInBoard();
		
        for (int col = 0; col < numberOfColumns; ++col)
            cell[col] = new Cell(cell_width, cell_height, Vector2i(col, 0));
    }

    void Board::deleteBoard()
    {
        delete cell;
    }

    void Board::render(RenderWindow& window)
    {
        window.draw(boardSprite);
		
        for (int col = 0; col < numberOfColumns; ++col)
            cell[col]->render(window);

    }

    float Board::getCellWidthInBoard() const
    {
        return (boardWidth - horizontalCellPadding) / numberOfColumns;
    }

    float Board::getCellHeightInBoard() const
    {
        return (boardHeight - verticalCellPadding) / numberOfRows;
    }
}