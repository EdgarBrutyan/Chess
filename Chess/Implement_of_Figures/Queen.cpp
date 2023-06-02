#include"../Figures/Queen.h"
#include "../Figures/Board.h"


bool Queen::ValidOrNot(const std::pair<int, int>& current, const std::pair<int, int>& new_pos, Board& b)
{

    if(new_pos.first < 0 || new_pos.first > 7 || new_pos.second < 0 || new_pos.second > 7)
    {
        return false;
    }
    
     // self check 
     if(new_pos == current){return false;}

     // is busy by the figure of the same color 
     if(b.CheckBusyOrNot(new_pos) == color) {return false;}


    if(abs(current.first - new_pos.first) != abs(current.second - new_pos.second) && (current.first != new_pos.first) && (current.second != new_pos.second))
    {
        return false;
    }


     // is the valid path
     if(current.first < new_pos.first && current.second < new_pos.second)
     {
         for(int i = current.first + 1, j = current.second + 1; i < new_pos.first && j < new_pos.second; i++, j++)
         {
            if(b.CheckBusyOrNot(std::make_pair(i,j)))
            {
               return false;
            }
         }
     }

     else if(current.first < new_pos.first && current.second > new_pos.second)
     {
         for(int i = current.first + 1, j = current.second - 1; i < new_pos.first && j > new_pos.second; i++, j--)
         {
            if(b.CheckBusyOrNot(std::make_pair(i,j)))
            {
               return false;
            }
         }
     }

     else if(current.first > new_pos.first && current.second < new_pos.second)
     {
         for(int i = current.first - 1, j = current.second + 1; i > new_pos.first && j < new_pos.second; i--, j++)
         {
            if(b.CheckBusyOrNot(std::make_pair(i,j)))
            {
               return false;
            }
         }
     }


     else if(current.first > new_pos.first && current.second > new_pos.second)
     {
         for(int i = current.first - 1, j = current.second - 1; i > new_pos.first && j > new_pos.second; i--, j--)
         {
            if(b.CheckBusyOrNot(std::make_pair(i,j)))
            {
               return false;
            }
         }
     }


     else if (current.first == new_pos.first){

         for(int j = current.second; j != new_pos.second;)
         {
             if(j > new_pos.second)
             {
                 j--;
                 if(b.CheckBusyOrNot(std::make_pair(current.first,j)) && j != new_pos.second)
                 {
                   return false;
                 }
             }

             if(j < new_pos.second)
             {
                j++;
                 if(b.CheckBusyOrNot(std::make_pair(current.first,j)) && j != new_pos.second)
                 {
                   return false;
                 }
             }
         }   
     }


     else if (current.second == new_pos.second){

         for(int i = current.first; i != new_pos.first;)
         {
             if(i > new_pos.first)
             {
                 i--;
                 if(b.CheckBusyOrNot(std::make_pair(i,current.second)) && i != new_pos.first)
                 {
                   return false;
                 }
             }

             if(i < new_pos.first)
             {
                 i++;
                 if(b.CheckBusyOrNot(std::make_pair(i,current.second)) && i != new_pos.first)
                 {
                   return false;
                 }
             }
         }   
     }

     return true;
}

Queen::Queen(const FigureColor& color)
{
     this->color = color;
}
