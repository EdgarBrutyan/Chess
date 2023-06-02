#include "Figure.h"
#include"Board.h"

#ifndef Knight_h
#define Knight_h
class Knight : public Figure {
public:
    bool ValidOrNot(const std::pair<int, int>& current, const std::pair<int, int>& new_pos, Board& b) override;
    Knight(const FigureColor& color);
};

#endif
