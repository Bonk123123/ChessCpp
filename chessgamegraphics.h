#ifndef CHESSGAMEGRAPHICS_H
#define CHESSGAMEGRAPHICS_H

#include "chessgame.h"
#include <list>

const int SPRITE_WIDTH = 255;

// decorator pattern

// class for calculate graphics numbers(positions or bounding and etc.)
class ChessGameGraphics : public ChessGame
{
public:
    ChessGameGraphics(ChessGame *chess, float board_width = 0);

public:
    // override move for calculate postions of figures
    virtual void move(const Point<int> &pos1, const Point<int> &pos2) override;

    // get board begin position
    Point<float> getBoardBeginPos(float layoutWidth, float layoutHeight);

    // get indexes (i, j) on board from position from widget (x, y)
    Point<int> getFigureIndexFromPos(Point<int> pos);

    // get and set BoardWidth
    void setBoardWidth(float width);
    float getBoardWidth();
    //

    // get Cell widht
    float getBoardCellWidth();

    // get positions for figures
    std::vector<std::pair<Point<float>*, std::string>>& getFiguresPos();

    // get positions for possible moves
    std::list<std::pair<Point<float>, MOVE_TYPE>> getPossibleMovesPos(const Point<int> &pos);

    // get sprite scale
    float getSpritesScale();

    // calculate all figures positions on widget
    void restartFiguresPos();

private:
    Point<float> _board_pos;
    std::vector<std::pair<Point<float>*, std::string>> _figures_pos;

    ChessGame *_chess;

    float _boardCellWidth = 0;
    float _boardWidth = 0;

};

#endif // CHESSGAMEGRAPHICS_H
