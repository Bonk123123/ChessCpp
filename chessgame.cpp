#include "chessgame.h"

ChessGame::ChessGame()
{
    this->_turn = TEAM::WHITE;
    this->_board = new Board();
}

ChessGame::ChessGame(const ChessGame *game)
{
    this->_board = game->_board;
    this->_turn = game->_turn;
}

ChessGame::~ChessGame()
{
    if (!this->_board) delete this->_board;
}


// start and restart all figures
void ChessGame::start()
{
    this->restartAll();
}
//


// default placement of fugures
void ChessGame::defaultPlacementOfFigures()
{
    this->_board->placeFigure(Point<int>(0, 0), new FIGURES::Rook(TEAM::BLACK));
    this->_board->placeFigure(Point<int>(1, 0), new FIGURES::Knight(TEAM::BLACK));
    this->_board->placeFigure(Point<int>(2, 0), new FIGURES::Bishop(TEAM::BLACK));
    this->_board->placeFigure(Point<int>(4, 0), new FIGURES::Queen(TEAM::BLACK));
    this->_board->placeFigure(Point<int>(3, 0), new FIGURES::King(TEAM::BLACK));
    this->_board->placeFigure(Point<int>(5, 0), new FIGURES::Bishop(TEAM::BLACK));
    this->_board->placeFigure(Point<int>(6, 0), new FIGURES::Knight(TEAM::BLACK));
    this->_board->placeFigure(Point<int>(7, 0), new FIGURES::Rook(TEAM::BLACK));
    this->_board->placeFigure(Point<int>(0, 1), new FIGURES::Pawn(TEAM::BLACK, 1));
    this->_board->placeFigure(Point<int>(1, 1), new FIGURES::Pawn(TEAM::BLACK, 1));
    this->_board->placeFigure(Point<int>(2, 1), new FIGURES::Pawn(TEAM::BLACK, 1));
    this->_board->placeFigure(Point<int>(3, 1), new FIGURES::Pawn(TEAM::BLACK, 1));
    this->_board->placeFigure(Point<int>(4, 1), new FIGURES::Pawn(TEAM::BLACK, 1));
    this->_board->placeFigure(Point<int>(5, 1), new FIGURES::Pawn(TEAM::BLACK, 1));
    this->_board->placeFigure(Point<int>(6, 1), new FIGURES::Pawn(TEAM::BLACK, 1));
    this->_board->placeFigure(Point<int>(7, 1), new FIGURES::Pawn(TEAM::BLACK, 1));

    this->_board->placeFigure(Point<int>(0, 7), new FIGURES::Rook(TEAM::WHITE));
    this->_board->placeFigure(Point<int>(1, 7), new FIGURES::Knight(TEAM::WHITE));
    this->_board->placeFigure(Point<int>(2, 7), new FIGURES::Bishop(TEAM::WHITE));
    this->_board->placeFigure(Point<int>(4, 7), new FIGURES::Queen(TEAM::WHITE));
    this->_board->placeFigure(Point<int>(3, 7), new FIGURES::King(TEAM::WHITE));
    this->_board->placeFigure(Point<int>(5, 7), new FIGURES::Bishop(TEAM::WHITE));
    this->_board->placeFigure(Point<int>(6, 7), new FIGURES::Knight(TEAM::WHITE));
    this->_board->placeFigure(Point<int>(7, 7), new FIGURES::Rook(TEAM::WHITE));
    this->_board->placeFigure(Point<int>(0, 6), new FIGURES::Pawn(TEAM::WHITE, -1));
    this->_board->placeFigure(Point<int>(1, 6), new FIGURES::Pawn(TEAM::WHITE, -1));
    this->_board->placeFigure(Point<int>(2, 6), new FIGURES::Pawn(TEAM::WHITE, -1));
    this->_board->placeFigure(Point<int>(3, 6), new FIGURES::Pawn(TEAM::WHITE, -1));
    this->_board->placeFigure(Point<int>(4, 6), new FIGURES::Pawn(TEAM::WHITE, -1));
    this->_board->placeFigure(Point<int>(5, 6), new FIGURES::Pawn(TEAM::WHITE, -1));
    this->_board->placeFigure(Point<int>(6, 6), new FIGURES::Pawn(TEAM::WHITE, -1));
    this->_board->placeFigure(Point<int>(7, 6), new FIGURES::Pawn(TEAM::WHITE, -1));
}
//


// place figure on board
void ChessGame::placeFigure(const Point<int> &pos, Figure *figure)
{
    this->_board->placeFigure(pos, figure);
}
//

// remove figure
void ChessGame::removeFigure(const Point<int> &pos)
{
    this->_board->removeFigure(pos);
}
//

// move figure and check on action type
void ChessGame::move(const Point<int> &pos1, const Point<int> &pos2)
{

    if (!this->_board->isPointOnBoard(pos1) || !this->_board->isPointOnBoard(pos2)) return;

    // checking whose move it is
    if (this->_board->getFigure(pos1)->getTeam() != this->_turn) return;

    MOVE_TYPE move_type = this->getPossibleMoves(pos1)[pos2.x][pos2.y];

    // change turn
    this->_turn = this->_turn == TEAM::BLACK ? TEAM::WHITE : TEAM::BLACK;

    // move
    switch (move_type)
    {
    // simple move
    case MOVE_TYPE::AVAILABLE_MOVE:
    {
        this->moveFigure(pos1, pos2);
        break;
    }

    // kill move
    case MOVE_TYPE::KILL_MOVE:
    {
        this->moveFigure(pos1, pos2);
        break;
    }

    // castling move
    case MOVE_TYPE::CASTLING_MOVE:
    {
        int rookNewX = pos1.x - pos2.x > 0 ? pos1.x - pos2.x - 1 : pos1.x - pos2.x + 1;
        int kingNewX = pos1.x - pos2.x > 0 ? pos1.x - 1 : pos1.x + 1;
        Point<int> RookNewPoint(pos2.x + rookNewX, pos2.y);
        Point<int> KingNewPoint(pos1.x + kingNewX, pos1.y);

        this->moveFigure(pos2, RookNewPoint);
        this->moveFigure(pos1, KingNewPoint);
        break;
    }
    default:
        break;
    }


    this->restartAll();
}
//


// get possible moves of this figure
std::vector<std::vector<MOVE_TYPE>> ChessGame::getPossibleMoves(const Point<int> &pos)
{
    if (this->_board->isPointOnBoard(pos) && this->_board->isPointOnFigure(pos))
    {
        return this->_board->getFigure(pos)->getPossibleMoves();
    }
    return std::vector<std::vector<MOVE_TYPE>>(BOARD_SIZE, std::vector<MOVE_TYPE>(BOARD_SIZE, MOVE_TYPE::OUT_OF_REACH));
}
//

// set board
void ChessGame::setBoard(Board *board)
{
    this->_board = board;
}
//

// get figure from board
Figure* ChessGame::getFigure(const Point<int> &pos)
{
    return this->_board->getFigure(pos);
}
//

// is point on figure
bool ChessGame::isPointOnFigure(const Point<int> &pos)
{
    return this->_board->isPointOnFigure(pos);
}
//

// get figures quantity
int ChessGame::getFiguresQuantity()
{
    return this->_board->getFiguresQuantity();
}
//


// move figure
void ChessGame::moveFigure(const Point<int> &current_pos, const Point<int> &next_pos)
{
    this->_board->placeFigure(next_pos, this->_board->getFigure(current_pos));
    this->_board->removeFigure(current_pos);
}
//


// calculate possible moves of this figure
void ChessGame::restartFigure(const Point<int> &pos)
{
    this->_board->getFigure(pos)->restartMoves(pos, this->_board);
}
//

// calculate possible moves of all figures
void ChessGame::restartAll()
{
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE; j++)
        {
            if (this->_board->isPointOnFigure(Point<int>(i, j)))
                this->_board->getFigure(Point<int>(i, j))->restartMoves(Point<int>(i, j), this->_board);
        }
    }
}
//



