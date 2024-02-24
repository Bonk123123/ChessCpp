
#include "figure.h"

Figure::Figure(TEAM team)
{
    this->_possible_moves = std::vector<std::vector<MOVE_TYPE>>(BOARD_SIZE, std::vector<MOVE_TYPE>(BOARD_SIZE, MOVE_TYPE::OUT_OF_REACH));
    this->_team = team;
}

Figure::Figure(Figure *figure)
{
    // init
    this->_directions = figure->_directions;
    this->_img_path = figure->_img_path;
    this->_possible_moves = figure->_possible_moves;
    this->_team = figure->_team;
    this->_type = figure->_type;
}

Figure::~Figure() {}

// get possible moves
std::vector<std::vector<MOVE_TYPE>> Figure::getPossibleMoves()
{
    return this->_possible_moves;
}
//

// get and set team
void Figure::setTeam(TEAM team)
{
    this->_team = team;
}

TEAM Figure::getTeam()
{
    return this->_team;
}
//


// get type
FIGURE_TYPE Figure::getType()
{
    return this->_type;
}
//

// get img path for sprite
std::string Figure::getImgPath()
{
    return this->_img_path;
}
//

// calculate all possible moves
void Figure::restartMoves(const Point<int> &pos, Board *board)
{
    this->_possible_moves = std::vector<std::vector<MOVE_TYPE>>(BOARD_SIZE, std::vector<MOVE_TYPE>(BOARD_SIZE, MOVE_TYPE::OUT_OF_REACH));

    // check directions one by one
    for (Point<int> &direct : this->_directions)
    {
        Point<int> possible_pos(pos);
        possible_pos += direct;

        // get first move type
        MOVE_TYPE move_type = this->isPossibleMove(possible_pos, board);

        // and continue direct+ while move type can be reached
        while (move_type != MOVE_TYPE::OUT_OF_REACH)
        {
            this->_possible_moves[possible_pos.x][possible_pos.y] = move_type;
            if (move_type == MOVE_TYPE::KILL_MOVE)
                break;

            possible_pos += direct;
            move_type = this->isPossibleMove(possible_pos, board);
        }
    }
}
//

// check figure on opposite figure
bool Figure::isOppositeFigure(TEAM team)
{
    if (this->_team != team)
        return true;
    return false;
}
//


// check move type on this position
MOVE_TYPE Figure::isPossibleMove(const Point<int> &possible_pos, Board *board)
{
    if (board->isPointOnBoard(possible_pos))
    {
        if (board->isPointOnFigure(possible_pos) && this->isOppositeFigure(board->getFigure(possible_pos)->getTeam()))
        {
            return MOVE_TYPE::KILL_MOVE;
        }
        else if (board->isPointOnFigure(possible_pos) && !this->isOppositeFigure(board->getFigure(possible_pos)->getTeam()))
        {
            return MOVE_TYPE::OUT_OF_REACH;
        }
        return MOVE_TYPE::AVAILABLE_MOVE;
    }
    return MOVE_TYPE::OUT_OF_REACH;
}
//
