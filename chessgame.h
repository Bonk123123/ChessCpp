#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "board.h"
#include "figure.h"
#include "figures.h"

class ChessGame
{
public:
    ChessGame();

    ChessGame(const ChessGame *game);

    ~ChessGame();

public:
    // start after place figures
    void start();

    // place or remove figures
    void defaultPlacementOfFigures();
    void placeFigure(const Point<int> &pos, Figure *figure);
    void removeFigure(const Point<int> &pos);
    //

    // actions of board
    virtual void move(const Point<int> &pos1, const Point<int> &pos2);
    std::vector<std::vector<MOVE_TYPE>> getPossibleMoves(const Point<int> &pos);
    //

    // set board
    void setBoard(Board *board);


    // help functions
    Figure *getFigure(const Point<int> &pos);
    bool isPointOnFigure(const Point<int> &pos);
    int getFiguresQuantity();
    //

private:
    // move figure
    void moveFigure(const Point<int> &current_pos, const Point<int> &next_pos);

    // calculate possible moves
    void restartFigure(const Point<int> &pos);
    void restartAll();

protected:
    Board *_board;
    TEAM _turn;
};

#endif // CHESSGAME_H
