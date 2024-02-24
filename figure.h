#ifndef FIGURE_H
#define FIGURE_H

#include <string>
#include <vector>
#include "point.h"

enum class TEAM
{
    WHITE = 0,
    BLACK = 1,
};

enum class MOVE_TYPE
{
    OUT_OF_REACH = 0, // figure cant reach this cell
    AVAILABLE_MOVE = 1, // figure can move on this cell
    KILL_MOVE = 2, // figure can kill another figure
    CASTLING_MOVE = 3 // castling rook an king
};

// all classes in namespace FIGURES
enum class FIGURE_TYPE
{
    EMPTY = 0, // class Figure = nullptr is empty cell
    PAWN = 1, // class Pawn
    ROOK = 2, // class Rook
    KNIGHT = 3, // class Knight
    BISHOP = 4, // class Bishop
    QUEEN = 5, // class Queen
    KING = 6 // class King
};

class Figure;

#include "board.h"

class Figure
{
public:
    Figure(TEAM team);

    Figure(Figure *figure);

    ~Figure();

public:
    // get possible moves of figure
    std::vector<std::vector<MOVE_TYPE>> getPossibleMoves();

    // get and set team
    void setTeam(TEAM team);
    TEAM getTeam();
    //

    // get type of figure
    FIGURE_TYPE getType();

    // get img path for sprite
    std::string getImgPath();

    // calculate all possible moves
    virtual void restartMoves(const Point<int> &pos, Board *board);

    // check figure on opposite figure
    bool isOppositeFigure(TEAM team);

    // check position on possible move
    MOVE_TYPE isPossibleMove(const Point<int> &possible_pos, Board *board);


protected:
    TEAM _team;
    std::string _img_path = "";

    FIGURE_TYPE _type;

    std::vector<std::vector<MOVE_TYPE>> _possible_moves;

    std::vector<Point<int>> _directions; // directions of figures possible moves
};

#endif // FIGURE_H
