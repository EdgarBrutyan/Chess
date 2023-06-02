#include "../Figures/King.h"
#include "../Figures/Board.h"


bool King::ValidOrNot(const std::pair<int, int>& current, const std::pair<int, int>& new_pos, Board& b)
{
    if(new_pos == current){return false;}

    if(new_pos.first < 0 || new_pos.first > 7 || new_pos.second < 0 || new_pos.second > 7)
    {
        return false;
    }

    if(abs(current.first - new_pos.first) > 1 || abs(current.second - new_pos.second) > 1)
    {
        return false;
    }

    if(b.CheckBusyOrNot(new_pos) == color)
    {
        return false;
    }

    return true;
}

King::King(const FigureColor& color)
{
    this->color = color;
    count = 0;
}

void King::SetCount(int count)
{
    this->count = count;
}

int King::GetCount() const 
{
    return count;
}