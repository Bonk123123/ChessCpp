#include "figures.h"

// initialization type, img path and directions for all figures
FIGURES::Pawn::Pawn(TEAM team, int8_t direction) : Figure(team)
{
    this->_type = FIGURE_TYPE::PAWN;

    this->_img_path = this->_team == TEAM::WHITE ? "Figures/Pawn.png" : "Figures/Dark_Pawn.png";

    this->_directions.push_back(Point<int>(0, 1 * direction));
}

FIGURES::Rook::Rook(TEAM team) : Figure(team)
{
    this->_type = FIGURE_TYPE::ROOK;

    this->_img_path = this->_team == TEAM::WHITE ? "Figures/Rook.png" : "Figures/Dark_Rook.png";

    this->_directions = std::vector<Point<int>>(4);

    this->_directions[0] = Point<int>(1, 0);
    this->_directions[1] = Point<int>(0, 1);
    this->_directions[2] = Point<int>(-1, 0);
    this->_directions[3] = Point<int>(0, -1);
}

FIGURES::Knight::Knight(TEAM team) : Figure(team)
{
    this->_type = FIGURE_TYPE::KNIGHT;

    this->_img_path = this->_team == TEAM::WHITE ? "Figures/Knight.png" : "Figures/Dark_Knight.png";
}

FIGURES::Bishop::Bishop(TEAM team) : Figure(team)
{
    this->_type = FIGURE_TYPE::BISHOP;

    this->_img_path = this->_team == TEAM::WHITE ? "Figures/Bishop.png" : "Figures/Dark_Bishop.png";

    this->_directions = std::vector<Point<int>>(4);

    this->_directions[0] = Point<int>(1, 1);
    this->_directions[1] = Point<int>(-1, 1);
    this->_directions[2] = Point<int>(1, -1);
    this->_directions[3] = Point<int>(-1, -1);
}

FIGURES::Queen::Queen(TEAM team) : Figure(team)
{
    this->_type = FIGURE_TYPE::QUEEN;

    this->_img_path = this->_team == TEAM::WHITE ? "Figures/Queen.png" : "Figures/Dark_Queen.png";

    this->_directions = std::vector<Point<int>>(8);

    this->_directions[0] = Point<int>(1, 0);
    this->_directions[1] = Point<int>(0, 1);
    this->_directions[2] = Point<int>(-1, 0);
    this->_directions[3] = Point<int>(0, -1);
    this->_directions[4] = Point<int>(1, 1);
    this->_directions[5] = Point<int>(-1, 1);
    this->_directions[6] = Point<int>(1, -1);
    this->_directions[7] = Point<int>(-1, -1);
}

FIGURES::King::King(TEAM team) : Figure(team)
{
    this->_type = FIGURE_TYPE::KING;

    this->_img_path = this->_team == TEAM::WHITE ? "Figures/King.png" : "Figures/Dark_King.png";
}
//



// calculate Pawn possible moves
void FIGURES::Pawn::restartMoves(const Point<int> &pos, Board *board)
{
    // if pos y = 7 or 0 need change figure

    this->_possible_moves = std::vector<std::vector<MOVE_TYPE>>(BOARD_SIZE, std::vector<MOVE_TYPE>(BOARD_SIZE, MOVE_TYPE::OUT_OF_REACH));

    Point<int> possible_pos(pos);

    // kill moves
    possible_pos.y += this->_directions[0].y;
    possible_pos.x += 1;

    if (board->isPointOnBoard(possible_pos) && board->isPointOnFigure(possible_pos) && this->isOppositeFigure(board->getFigure(possible_pos)->getTeam()))
    {
        this->_possible_moves[possible_pos.x][possible_pos.y] = MOVE_TYPE::KILL_MOVE;
    }

    possible_pos.x -= 2;

    if (board->isPointOnBoard(possible_pos) && board->isPointOnFigure(possible_pos) && this->isOppositeFigure(board->getFigure(possible_pos)->getTeam()))
    {
        this->_possible_moves[possible_pos.x][possible_pos.y] = MOVE_TYPE::KILL_MOVE;
    }
    possible_pos.x += 1;
    //

    // simple moves check
    if (board->isPointOnBoard(possible_pos) && !board->isPointOnFigure(possible_pos))
    {
        this->_possible_moves[possible_pos.x][possible_pos.y] = MOVE_TYPE::AVAILABLE_MOVE;

        possible_pos.y += this->_directions[0].y;
        if (board->isPointOnBoard(possible_pos) && !board->isPointOnFigure(possible_pos))
        {
            this->_possible_moves[possible_pos.x][possible_pos.y] = MOVE_TYPE::AVAILABLE_MOVE;
        }
    }
    //
}
//

// calculate Knight possible moves
void FIGURES::Knight::restartMoves(const Point<int> &pos, Board *board)
{
    this->_possible_moves = std::vector<std::vector<MOVE_TYPE>>(BOARD_SIZE, std::vector<MOVE_TYPE>(BOARD_SIZE, MOVE_TYPE::OUT_OF_REACH));

    Point<int> possible_pos(pos);

    // vectors for find positions of Knight
    Point<int> vec1(2, 1);
    Point<int> vec2(2, -1);
    //

    for (size_t i = 0; i < 4; i++)
    {
        possible_pos = pos + vec1;

        if (board->isPointOnBoard(possible_pos))
            this->_possible_moves[possible_pos.x][possible_pos.y] = this->isPossibleMove(possible_pos, board);

        possible_pos = pos + vec2;

        if (board->isPointOnBoard(possible_pos))
            this->_possible_moves[possible_pos.x][possible_pos.y] = this->isPossibleMove(possible_pos, board);

        // turn on 90 degrees vectors
        vec1.turnOn90deg();
        vec2.turnOn90deg();
        //
    }
}
//

// calculate King possible moves
void FIGURES::King::restartMoves(const Point<int> &pos, Board *board)
{
    this->_possible_moves = std::vector<std::vector<MOVE_TYPE>>(BOARD_SIZE, std::vector<MOVE_TYPE>(BOARD_SIZE, MOVE_TYPE::OUT_OF_REACH));

    // check square of possible moves
    for (int i = pos.x - 1; i < pos.x + 2; i++)
    {
        for (int j = pos.y - 1; j < pos.y + 2; j++)
        {
            Point<int> possible_pos(i, j);
            if (board->isPointOnBoard(possible_pos) && possible_pos != pos)
                this->_possible_moves[possible_pos.x][possible_pos.y] = this->isPossibleMove(possible_pos, board);
        }
    }
    //

    // check on castling on both X directions < and >
    this->checkOnCastling(board, pos, 1);
    this->checkOnCastling(board, pos, -1); // if kill king position check need
}
//



// check on castling in one direction rook and King
void FIGURES::King::checkOnCastling(Board *board, const Point<int> &pos, int directX)
{
    Point<int> castling_pos(pos);

    for (size_t i = 0; i < 4; i++)
    {
        castling_pos.x += directX;

        // if point on board
        if (!board->isPointOnBoard(castling_pos))
            break;
        //

        // if on 2 or 3 cell (from 0) Rook
        if ((i == 2 || i == 3) && board->isPointOnFigure(castling_pos) && !this->isOppositeFigure(board->getFigure(castling_pos)->getTeam()) && board->getFigure(castling_pos)->getType() == FIGURE_TYPE::ROOK)
        {
            this->_possible_moves[castling_pos.x][castling_pos.y] = MOVE_TYPE::CASTLING_MOVE;
            break;
        }
        //

        // check on 0-2 or 0-3 is free
        if (!board->isFreePoint(castling_pos))
            break;
        //
    }
}
//
