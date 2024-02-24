#include "board.h"

Board::Board()
{
    this->_board = std::vector<std::vector<Figure *>>(BOARD_SIZE, std::vector<Figure *>(BOARD_SIZE, nullptr));
}

Board::Board(const Board *board)
{
    this->_board = board->_board;
    this->_figures_counter = board->_figures_counter;
}

Board::~Board()
{
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            if (!this->_board[i][j]) delete this->_board[i][j];
        }
    }
}

// get figure
Figure *Board::getFigure(const Point<int> &pos)
{
    return this->_board[pos.x][pos.y];
}
//

// place figure on board
Board Board::placeFigure(const Point<int> &pos, Figure *figure)
{
    if (!this->isPointOnFigure(pos)) this->_figures_counter++;
    this->_board[pos.x][pos.y] = figure;
    return *this;
}
//


// remove figure
Board Board::removeFigure(const Point<int> &pos)
{
    if (this->isPointOnFigure(pos)) this->_figures_counter--;
    this->_board[pos.x][pos.y] = nullptr;
    return *this;

}
//


// check is point on board
bool Board::isPointOnBoard(const Point<int> &pos)
{
    if (pos.x < BOARD_SIZE && pos.y < BOARD_SIZE && pos.x >= 0 && pos.y >= 0)
        return true;
    return false;
}
//

// check is point on figure
bool Board::isPointOnFigure(const Point<int> &pos)
{
    return this->_board[pos.x][pos.y] != nullptr;
}

// check is empty point on board
bool Board::isFreePoint(const Point<int> &pos)
{
    if (!this->isPointOnBoard(pos))
        return false;

    return this->_board[pos.x][pos.y] == nullptr;
}
//

// get figures quantity
int Board::getFiguresQuantity()
{
    return this->_figures_counter;
}
//


