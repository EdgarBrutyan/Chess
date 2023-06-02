#include "Figure.h"
#include "Board.h"


#ifndef King_h
#define King_h

class King : public Figure {
public:
    bool ValidOrNot(const std::pair<int, int>& current, const std::pair<int, int>& new_pos, Board& b) override;
    King(const FigureColor& color);
    int GetCount() const;
    void SetCount(int count);

private:
    int count;
};

#endif