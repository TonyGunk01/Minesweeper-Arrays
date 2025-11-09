#pragma once

#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElements/Button/Button.h"
#include "../../header/Event/EventPollingManager.h"

using namespace UIElements;
using namespace sf;
using namespace std;

namespace Gameplay
{
    enum class CellState
    {
        HIDDEN,
        OPEN,
        FLAGGED,
    };

    enum class CellType
    {
        EMPTY,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        MINE,
    };

    class Board;

    class Cell
    {
        private:
            CellState current_cell_state;
            CellType cell_type;
            Vector2i position;
            int mines_around;

            const float cell_top_offset = 274.f;
            const float cell_left_offset = 583.f;
            const int tile_size = 128;
            const int slice_count = 12;
            const string cell_texture_path = "assets/textures/cells.jpeg";

            Button* cell_button;
            Board* board;

            void initialize(float width, float height, Vector2i position, Board* board);
            Vector2f getCellScreenPosition(float width, float height) const;
            void setCellTexture();

            void registerCellButtonCallback();
			void cellButtonCallback(MouseButtonType button_type);

        public:
            Cell(float width, float height, Vector2i position, Board* board);
            ~Cell() = default;

            void render(RenderWindow& window);

            //Getters, Setters
            CellState getCellState() const;
            void setCellState(CellState state);

            CellType getCellType() const;
            void setCellType(CellType type);

            Vector2i getCellPosition();
            void update(EventPollingManager& eventManager, RenderWindow& window);

            bool canOpenCell() const;
            void open();
    };
}