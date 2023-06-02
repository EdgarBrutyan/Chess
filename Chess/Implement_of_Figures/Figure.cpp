#include<iostream> 
#include "../Figures/Figure.h"
#include "../Figures/Board.h"

FigureColor Figure::GetColor() const
{
    return color;
}

void Figure::SetColor(const FigureColor& color)
{
    this->color = color;
}

Figure::Figure(const FigureColor& color)
{
     this->color = color;
}

Figure::Figure()
{
    
}

Figure::~Figure()
{

}