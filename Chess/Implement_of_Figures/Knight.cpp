#include "../Figures/Knight.h"
#include "../Figures/Board.h"

bool Knight::ValidOrNot(const std::pair<int, int>& current, const std::pair<int, int>& new_pos, Board& b)
{
     if(new_pos == current){return false;}

    if(new_pos.first < 0 || new_pos.first > 7 || new_pos.second < 0 || new_pos.second > 7)
    {
        return false;
    }

    if(color == b.CheckBusyOrNot(new_pos)){return false;}

    if(abs(current.first - new_pos.first) == 1 && abs(current.second - new_pos.second) == 2)
    {
       return true;
    }

    if(abs(current.first - new_pos.first) == 2  && abs(current.second - new_pos.second) == 1)
    {
        return true;
    }

    return false;
}

Knight::Knight(const FigureColor& color)
{
     this->color = color;
}