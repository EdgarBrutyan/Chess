#include "../Figures/Rook.h"
#include "../Figures/Board.h"


bool Rook::ValidOrNot(const std::pair<int, int>& current, const std::pair<int, int>& new_pos, Board& b)
{

    if(new_pos == current){return false;}

    if(new_pos.first < 0 || new_pos.first > 7 || new_pos.second < 0 || new_pos.second > 7)
    {
        return false;
    }

     if(b.CheckBusyOrNot(new_pos) == color){
        return false;
      }

     if(current.first != new_pos.first && current.second != new_pos.second){return false;}


     if (current.first == new_pos.first){

         for(int j = current.second; j != new_pos.second;)
         {
             if(j > new_pos.second)
             {
                 j--;
                 if(b.CheckBusyOrNot({current.first,j}) && j != new_pos.second)
                 {
                   return false;
                 }
             }

             else if(j < new_pos.second)
             {
                 j++;
                 if(b.CheckBusyOrNot({current.first,j}) && j != new_pos.second)
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
                 if(b.CheckBusyOrNot({i,current.second}) && i != new_pos.first)
                 {
                   return false;
                 }
             }

             else if(i < new_pos.first)
             {
                 i++;
                 if(b.CheckBusyOrNot({i,current.second}) && i != new_pos.first)
                 {
                   return false;
                 }
             }
         }   
     }

     count++;   
     return true;
}

Rook::Rook(const FigureColor& color)
{
     this->color = color;
     this->count = 0;
}

int Rook::GetCount() const
{
     return count;
}

void Rook::SetCount(int count)
{
    this->count = count;
}

