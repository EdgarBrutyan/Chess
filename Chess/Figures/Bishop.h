#include "Figure.h"
#include"Board.h"

#ifndef Bishop_h
#define Bishop_h
class Bishop : public Figure {
public:
    bool ValidOrNot(const std::pair<int, int>& current, const std::pair<int, int>& new_pos, Board& b) override;
    Bishop(const FigureColor& color);
};
#endif


