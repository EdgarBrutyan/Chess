#include<iostream> 
#include"Board.h"

#ifndef Figure_h
#define Figure_h

class Board;

enum FigureColor {
    Black = -1,
    White = 1
};

class Figure {
protected:
     Figure(Figure& q);
     Figure& operator= (const Figure& q);

public:
     Figure();
     
     Figure(const FigureColor& color);

     void SetColor(const FigureColor& color);

     FigureColor GetColor() const;


     /**
      * @brief Проверят может ли фигура сделать ход  
      * 
      * Изначально проверяет может ли фигура пойти в новую координату если бы на доске не было больше фигур 
      * А потом еще учитывается фактор других фигур. Кстати эта функция используется в функции MoveFigure класса Board 
      * в качестве проверки
      * 
      * @param Board& доска 
      * 
      * @param current_coordinate текущяя координата 
      * 
      * @param new_pos новая координата
      * 
      * @return true если может туда пойти, false в противном случае 
     */
     virtual bool ValidOrNot(const std::pair<int, int>& current, const std::pair<int, int>& new_pos, Board& b) = 0;

     virtual ~Figure();

protected:
    FigureColor color;
};

#endif