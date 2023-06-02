#include "Figure.h"
#include"Board.h"


#ifndef Queen_h
#define Queen_h

class Queen : public Figure {
public:
    bool ValidOrNot(const std::pair<int, int>& current, const std::pair<int, int>& new_pos, Board& b) override;
    Queen(const FigureColor& color);
};

#endif