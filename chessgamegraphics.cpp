#include "chessgamegraphics.h"

ChessGameGraphics::ChessGameGraphics(ChessGame *chess, float board_width) : ChessGame(chess)
{
    this->_chess = chess;
    this->_board_pos = Point<float>();
    this->_boardWidth = board_width;

    this->restartFiguresPos();
}


// override move from chess class and add restart positions
void ChessGameGraphics::move(const Point<int> &pos1, const Point<int> &pos2)
{
    this->_chess->move(pos1, pos2);

    // for 1 figure function need

    this->restartFiguresPos();
}
//

// get board begin positions from layout bounding
Point<float> ChessGameGraphics::getBoardBeginPos(float layoutWidth, float layoutHeight)
{
    this->_board_pos.x = (layoutWidth / 2) - (this->_boardWidth / 2);
    this->_board_pos.y = (layoutHeight / 2) - (this->_boardWidth / 2);
    return Point<float>(this->_board_pos);
}
//

// get indexes on board from postion on widget
Point<int> ChessGameGraphics::getFigureIndexFromPos(Point<int> pos)
{
    int x = (pos.x - this->_board_pos.x) / this->getBoardCellWidth();
    int y = (pos.y - this->_board_pos.y) / this->getBoardCellWidth();
    return Point<int>(x, y);
}
//

// get and set board width
void ChessGameGraphics::setBoardWidth(float width)
{
    this->_boardWidth = width;
}
float ChessGameGraphics::getBoardWidth()
{
    return this->_boardWidth;
}
//

// get cell width
float ChessGameGraphics::getBoardCellWidth()
{
    return this->_boardWidth / BOARD_SIZE;
}
//

// get sprites scale
float ChessGameGraphics::getSpritesScale()
{
    return this->getBoardCellWidth() / SPRITE_WIDTH;
}
//

// calculate figures positions on widget
void ChessGameGraphics::restartFiguresPos()
{
    this->_figures_pos = std::vector<std::pair<Point<float>*, std::string>>(this->_chess->getFiguresQuantity(), std::pair<Point<float>*, std::string>(nullptr, ""));

    int t = 0;

    float cell_width = this->getBoardCellWidth();

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            if (!this->_chess->isPointOnFigure(Point<int>(i, j))) continue;
            this->_figures_pos[t] = std::pair<Point<float>*, std::string>(new Point<float>(i * cell_width, j * cell_width), this->_chess->getFigure(Point<int>(i, j))->getImgPath());
            t++;
        }
    }
}
//

// get figures positions
std::vector<std::pair<Point<float>*, std::string>>& ChessGameGraphics::getFiguresPos()
{
    return this->_figures_pos;
}
//

// get possible moves positions on widget
std::list<std::pair<Point<float>, MOVE_TYPE>> ChessGameGraphics::getPossibleMovesPos(const Point<int> &pos)
{
    std::vector<std::vector<MOVE_TYPE>> possible_moves(this->getPossibleMoves(pos));

    std::list<std::pair<Point<float>, MOVE_TYPE>> possible_moves_pos;

    float cell_width = this->getBoardCellWidth();

    for(size_t i = 0; i < BOARD_SIZE; i++)
    {
        for(size_t j = 0; j < BOARD_SIZE; j++)
        {
            if ((int)possible_moves[i][j] > 0)
            {
                possible_moves_pos.push_back(std::pair<Point<float>, MOVE_TYPE>(Point<float>(i * cell_width, j * cell_width), possible_moves[i][j]));
            }
        }
    }

    return possible_moves_pos;
}
//
