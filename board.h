#ifndef BOARD_H
#define BOARD_H

// #include "figure.h"
#include "point.h"
#include <vector>

const __UINT8_TYPE__ BOARD_SIZE = 8;

class Figure;

class Board
{
public:
    Board();

    Board(const Board *board);

    ~Board();

public:
    // actions for figures
    Figure *getFigure(const Point<int> &pos);
    Board placeFigure(const Point<int> &pos, Figure *figure);
    Board removeFigure(const Point<int> &pos);
    //

    // check
    bool isPointOnBoard(const Point<int> &pos);
    bool isPointOnFigure(const Point<int> &pos);
    bool isFreePoint(const Point<int> &pos);
    //

    // get figures quantity
    int getFiguresQuantity();

private:
    int _figures_counter = 0;
    std::vector<std::vector<Figure *>> _board;
};

#endif // BOARD_H
