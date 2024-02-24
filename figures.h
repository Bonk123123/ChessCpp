#ifndef FIGURES_H
#define FIGURES_H

#include "figure.h"


// override restartMoves only for special moves or can be describe from direction, for example Knight
namespace FIGURES
{
    // Pawn
    class Pawn : public Figure
    {
    public:
        Pawn(TEAM team, int8_t direction);

    public:
        virtual void restartMoves(const Point<int> &pos, Board *board) override;
    };
    //

    // Rook
    class Rook : public Figure
    {
    public:
        Rook(TEAM team);
    };
    //

    // Knight
    class Knight : public Figure
    {
    public:
        Knight(TEAM team);

    public:
        virtual void restartMoves(const Point<int> &pos, Board *board) override;
    };
    //

    // Bishop
    class Bishop : public Figure
    {
    public:
        Bishop(TEAM team);
    };
    //

    // Queen
    class Queen : public Figure
    {
    public:
        Queen(TEAM team);
    };
    //

    // King
    class King : public Figure
    {
    public:
        King(TEAM team);

    public:
        virtual void restartMoves(const Point<int> &pos, Board *board) override;

        // only for king
        // and only in one direction X
        void checkOnCastling(Board *board, const Point<int> &pos, int directX);
    };
    //
}
//

#endif // FIGURES_H
