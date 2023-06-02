#include "../Figures/Board.h"
#include "raylib.h"
#include<vector>
#include<map>

Board::Board()
:board(8, std::vector<int>(8,0))
{
    SetInitialPositions();
    InitialBusyCages();
}


void Board::SetInitialPositions()
{
     for(int i = 1; i < 2; i++)
     {
        for(int j = 0; j < 8; j++)
        {

            positions_of_figures.insert({{i,j}, new Pawn(FigureColor::White)});
            positions_of_figures.insert({{i+5, j}, new Pawn(FigureColor::Black)});
        }
     }

     // Rook
     positions_of_figures.insert({{0,0}, new Rook(FigureColor::White)});
     positions_of_figures.insert({{0,7}, new Rook(FigureColor::White)});
     positions_of_figures.insert({{7,0}, new Rook(FigureColor::Black)});
     positions_of_figures.insert({{7,7}, new Rook(FigureColor::Black)});

     // Knight
     positions_of_figures.insert({{0,1}, new Knight(FigureColor::White)});
     positions_of_figures.insert({{7,1}, new Knight(FigureColor::Black)});
     positions_of_figures.insert({{0,6}, new Knight(FigureColor::White)});
     positions_of_figures.insert({{7,6}, new Knight(FigureColor::Black)});

     // Bishop
     positions_of_figures.insert({{0,2}, new Bishop(FigureColor::White)});
     positions_of_figures.insert({{7,2}, new Bishop(FigureColor::Black)});
     positions_of_figures.insert({{0,5}, new Bishop(FigureColor::White)});
     positions_of_figures.insert({{7,5}, new Bishop(FigureColor::Black)});

     // Queen 
     positions_of_figures.insert({{0,3}, new Queen(FigureColor::White)});
     positions_of_figures.insert({{7,3}, new Queen(FigureColor::Black)});

    // King 
     positions_of_figures.insert({{0,4}, new King(FigureColor::White)});
     positions_of_figures.insert({{7,4}, new King(FigureColor::Black)});  
}




void Board::InitialBusyCages()
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = 1;
            board[i+6][j] = -1;
        }   
    }
}


int Board::CheckBusyOrNot(const std::pair<int, int>& coord)
{
    return board[coord.first][coord.second];
}


Figure* Board::GetFigure(const std::pair<int, int>& coord)
{
    auto it = positions_of_figures.find(coord);

    if(it == positions_of_figures.end())
    {
        return nullptr;
    }

    else {
        return it->second;
    }
}


bool Board::MoveFigure(Figure* f, const FigureColor& color, const std::pair<int, int>& current, const std::pair<int, int>& new_pos)
{
    if(typeid(*f) == typeid(King) && color == 1 && current == std::make_pair(0, 4) && new_pos == std::make_pair(0, 6)) 
    {
        return Castling(FigureColor::White, 2);
    }

    if(typeid(*f) == typeid(King) && color == 1 && current == std::make_pair(0, 4) && new_pos == std::make_pair(0, 2))
    {
        return Castling(FigureColor::White, 3);
    }

    if(typeid(*f) == typeid(King) && color == -1 && current == std::make_pair(7, 4) && new_pos == std::make_pair(7, 6))
    {
        return Castling(FigureColor::Black, 2);
    }

    if(typeid(*f) == typeid(King) && color == -1 && current == std::make_pair(7, 4) && new_pos == std::make_pair(7, 2))
    {
         return Castling(FigureColor::Black, 3);
    }

    if(GetFigure({current}) == nullptr || typeid(*f) != typeid(*GetFigure({current})))
    {
        return false ;
    }

    if(!Check(f, color, current, new_pos)){return false;}

    bool temp = false; 
    Figure* temp2 = positions_of_figures.find(new_pos)->second;

     if(board[new_pos.first][new_pos.second] != 0)
     {
            positions_of_figures.erase(new_pos);
            temp = true;
     } 

    if(typeid(*f) == typeid(Pawn))
    {
        return SpecialCasesPawn(f, color, current, new_pos);  
    }

    if(typeid(*f) == typeid(Rook) || typeid(*f) == typeid(King))
    {
        SpecialCasesRookAndKing(f, color, current, new_pos);
    }

    auto it = positions_of_figures.find(current);

    board[current.first][current.second] = 0;
    board[new_pos.first][new_pos.second] = f->GetColor();
    positions_of_figures.insert({new_pos, f});
    positions_of_figures.erase(it->first); 

    if(isKingUnderCheck(color) == true) {

        positions_of_figures.erase(new_pos);
        positions_of_figures.insert({current, f});
        board[current.first][current.second] = color;

        if(temp == true)
        {
            positions_of_figures.insert({new_pos, temp2});

            if(color == 1)
            {
                board[new_pos.first][new_pos.second] = -1;
            } else  {
                board[new_pos.first][new_pos.second] = 1;
            }
        }

        board[new_pos.first][new_pos.second] = 0;
        return false;
    }


    return true;
}


std::map<std::pair<int, int>, Figure*> Board::Copy_of_position()
{
    return positions_of_figures;
}


inline bool Board::Check(Figure* f, const FigureColor& color, const std::pair<int, int>& current, const std::pair<int, int>& new_pos)
{
    auto it = positions_of_figures.find(current);

    if(it == positions_of_figures.end()){return false;}
    if(it->second->GetColor() != color) {return false;}
    if(!f->ValidOrNot(current, new_pos, *this)) {return false;}

    return true;
}


bool Board::SpecialCasesPawn(Figure* f, const FigureColor& color, const std::pair<int, int>& current, const std::pair<int, int>& new_pos)
{
    bool IsSpecialCase = false;
    bool Is_Figure_In_New_Pos = false;    
    Figure* figure_in_new_pos = positions_of_figures.find(new_pos)->second;

    if(board[new_pos.first][new_pos.second] != 0)
    {
        positions_of_figures.erase(new_pos);
        board[new_pos.first][new_pos.second] = color;
        Is_Figure_In_New_Pos = true;
    } 


    if(new_pos.first == 0 || new_pos.first == 7)
    {
        if(color == 1)
        {
            positions_of_figures.erase(current);
            board[current.first][current.second] = 0;

            if(isKingUnderCheck(FigureColor::White))
            {
                positions_of_figures.insert({current, new Pawn(FigureColor::White)});
                board[current.first][current.second] = 1;
                board[new_pos.first][new_pos.second] = 0;

                if(Is_Figure_In_New_Pos == true)
                {
                    positions_of_figures.insert({new_pos, figure_in_new_pos});
                    board[new_pos.first][new_pos.second] = -1;
                }   

                return false;
            }

            positions_of_figures.insert({new_pos, new Queen(FigureColor::White)});
            return true;
        }
    }



    if(typeid(*f) == typeid(Pawn))
    {
        if(board[new_pos.first][new_pos.second] == 0 && abs(new_pos.first - current.first) == abs(new_pos.second - current.second))
        {
            IsSpecialCase = true;

            if(f->GetColor() == 1)
            {
                positions_of_figures.erase({new_pos.first - 1, new_pos.second});
                board[new_pos.first-1][new_pos.second] = 0;
            } 

            else if(f->GetColor() == -1) 
            {
                positions_of_figures.erase({new_pos.first + 1, new_pos.second});
                board[new_pos.first + 1][new_pos.second] = 0;
            }
        }
    }

        board[current.first][current.second] = 0;
        board[new_pos.first][new_pos.second] = f->GetColor();

        auto it = positions_of_figures.find(current);
        Pawn* temp2 = dynamic_cast<Pawn*>(it->second); 
        Pawn* ptr = new Pawn(it->second->GetColor());
        ptr->SetCount(temp2->GetCount()+1);
        positions_of_figures.insert({new_pos, ptr});
        positions_of_figures.erase(it->first);


        if(isKingUnderCheck(color) == true) 
        {
            positions_of_figures.insert({current, new Pawn(color)});
            positions_of_figures.erase(new_pos);
            board[current.first][current.second] = color;
            board[new_pos.first][new_pos.second] = 0; 

            if(IsSpecialCase == true)
            {
                if(f->GetColor() == 1)
                {
                    positions_of_figures.insert({{new_pos.first - 1, new_pos.second}, new Pawn(FigureColor::Black)});
                    board[new_pos.first - 1][new_pos.second] = -1;
                }

                if(f->GetColor() == -1)
                {
                    positions_of_figures.insert({{new_pos.first + 1, new_pos.second}, new Pawn(FigureColor::White)});
                    board[new_pos.first + 1][new_pos.second] = 1;
                }
            } 

            if(Is_Figure_In_New_Pos == true) 
            {
                if(color == 1)
                {
                    figure_in_new_pos = new Pawn(FigureColor::Black);
                    positions_of_figures.insert({new_pos, figure_in_new_pos});
                    board[new_pos.first][new_pos.second] = -1;

                } else  {
                    figure_in_new_pos = new Pawn(FigureColor::White);
                    positions_of_figures.insert({new_pos, figure_in_new_pos});
                    board[new_pos.first][new_pos.second] = 1;
                }
            }

            return false;
        }
    
    return true;
}


bool Board::isKingUnderCheck(const FigureColor& color, const std::pair<int, int>& pos_of_king) {

    std::pair<int, int> king_pos = pos_of_king;

    if(king_pos.first == -1 && king_pos.second == -1)
    {
        for(auto it : positions_of_figures)
        {
            if(it.second->GetColor() == color && typeid(*it.second) == typeid(King))
            {
                king_pos = it.first;
                break;
            }
        } 
    }

    for(auto it : positions_of_figures)
    {       
        if(it.second->GetColor() != color)
        {
            if(it.second->ValidOrNot(it.first, king_pos, *this) == true)
            {
                return true;
            }
        }
    }

    return false;
}


void Board::SpecialCasesRookAndKing(Figure* f, const FigureColor& color, const std::pair<int, int>& current, const std::pair<int, int>& new_pos)
{
    if(typeid(*f) == typeid(Rook))
    {
        bool temp2 = false;

        if(board[new_pos.first][new_pos.second] != 0)
        {
            positions_of_figures.erase(new_pos);
            temp2 = true;
        } 

        board[current.first][current.second] = 0;
        board[new_pos.first][new_pos.second] = f->GetColor();

        auto it = positions_of_figures.find(current);
        Rook* temp = dynamic_cast<Rook*>(it->second); 
        Rook* ptr = new Rook(it->second->GetColor());
        ptr->SetCount(temp->GetCount()+1);

        positions_of_figures.insert({new_pos, ptr});
        positions_of_figures.erase(it->first);

    }

    if(typeid(*f) == typeid(King))
    {
        bool temp2 = false;

         if(board[new_pos.first][new_pos.second] != 0)
        {
            positions_of_figures.erase(new_pos);
            temp2 = true;
        } 

        board[current.first][current.second] = 0;
        board[new_pos.first][new_pos.second] = f->GetColor();

        auto it = positions_of_figures.find(current);
        King* temp = dynamic_cast<King*>(it->second); 
        King* ptr = new King(it->second->GetColor());
        ptr->SetCount(temp->GetCount()+1);

        positions_of_figures.insert({new_pos, ptr});
        positions_of_figures.erase(it->first);
    }
}


bool Board::isKingAreMated(const FigureColor& color)
{
    std::pair<int, int> king_pos = {0,0};

     for(auto it : positions_of_figures)
     {
        if(it.second->GetColor() == color && typeid(*it.second) == typeid(King))
        {
            king_pos = it.first;
            break;
        }
     }

     int i = king_pos.first;
     int j = king_pos.second;
     Figure* ptr = positions_of_figures.find({i,j})->second;

    if(ptr->ValidOrNot({i,j}, {i-1, j-1}, *this))
    {
         int temp = board[i-1][j-1];
         board[i][j] = 0;
         board[i-1][j-1] = color;

        if(!isKingUnderCheck(color, std::make_pair(i-1, j-1)))
        {
            board[i-1][j-1] = temp;
            board[i][j] = color;
            return false;
        }  

        board[i-1][j-1] = temp;
        board[i][j] = color;
    }

    if(ptr->ValidOrNot({i,j}, {i-1, j}, *this))
    {
       int temp = board[i-1][j];
       board[i][j] = 0;
       board[i-1][j] = color;

        if(!isKingUnderCheck(color, std::make_pair(i-1, j)))
        {
            board[i-1][j] = temp;
            board[i][j] = color;
            return false;
        }

        board[i][j] = color;
        board[i-1][j] = temp;
    }

    if(ptr->ValidOrNot({i,j}, {i-1, j+1}, *this))
    {
      int temp = board[i-1][j+1];
      board[i][j] = 0;
      board[i-1][j+1] = color;

        if(!isKingUnderCheck(color, std::make_pair(i-1, j+1)))
        {
            board[i-1][j+1] = temp;
            return false;
        }

        board[i][j] = color;
        board[i-1][j+1] = temp;
    }  

    if(ptr->ValidOrNot({i,j}, {i, j-1}, *this))
    {
        int temp = board[i][j-1];
        board[i][j] = 0;
        board[i][j-1] = color;

        if(!isKingUnderCheck(color, std::make_pair(i, j-1)))
        {
            board[i][j-1] = temp;
            board[i][j] = color;
            return false;
        }

        board[i][j-1] = temp;
        board[i][j] = color;
    } 

    if(ptr->ValidOrNot({i,j}, {i, j+1}, *this))
    {       
       int temp = board[i][j+1];
       board[i][j] = 0;
        board[i][j+1] = color;

        if(!isKingUnderCheck(color, std::make_pair(i, j+1)))
        {
            board[i][j+1] = temp;
            board[i][j] = color;
            return false;
        }

        board[i][j+1] = temp;
        board[i][j] = color;
    }

    if(ptr->ValidOrNot({i,j}, {i+1, j-1}, *this))
    {
        int temp = board[i+1][j-1];
        board[i][j] = 0;
        board[i+1][j-1] = color;

        if(!isKingUnderCheck(color, std::make_pair(i+1, j-1)))
        {
            board[i+1][j-1] = temp;
            board[i][j] = color;
            return false;
        }

        board[i+1][j-1] = temp;
        board[i][j] = color;
    }

    if(ptr->ValidOrNot({i,j}, {i+1, j}, *this))
    {
        int temp = board[i+1][j];
        board[i][j] = 0;
        board[i+1][j] = color;

        if(!isKingUnderCheck(color, std::make_pair(i+1, j)))
        {
            board[i+1][j] = temp;
            board[i][j] = color;
            return false;
        }

        board[i+1][j] = temp;
        board[i][j] = color;
    }

    if(ptr->ValidOrNot({i,j}, {i+1, j+1}, *this))
    {
       int temp = board[i+1][j+1];
       board[i][j] = 0;
       board[i+1][j+1] = color;

        if(!isKingUnderCheck(color, std::make_pair(i+1, j+1)))
        {
            board[i+1][j+1] = temp;
            board[i][j] = color;
            return false;
        }

        board[i+1][j+1] = temp;
        board[i][j] = color;
    }


    for(auto figures : positions_of_figures)
    {
        if(color == figures.second->GetColor() && typeid(*figures.second) != typeid(King))
        {
            for(int i1 = 0; i1 < 8; i1++)
            {
                for(int j1 = 0; j1 < 8; j1++)
                {
                    if(figures.second->ValidOrNot(figures.first, {i1,j1}, *this))
                    {
                        Figure* figure_from_other_team = nullptr;
                        int temp = board[i1][j1];

                        if(positions_of_figures.find({i1,j1}) != positions_of_figures.end())
                        {   
                           if(positions_of_figures.find({i1,j1})->second->GetColor() != color)
                           {
                                figure_from_other_team = GetFigure({i1,j1});
                                positions_of_figures.erase({i1,j1});
                           }
                        }
                            
                        positions_of_figures.insert({{i1,j1}, figures.second});
                        board[i1][j1] = color;

                        if(!isKingUnderCheck(color, {i,j}))
                        {
                            board[i1][j1] = temp;
                            positions_of_figures.erase({i1,j1});

                            if(figure_from_other_team != nullptr)
                            {
                                positions_of_figures.insert({{i1,j1}, figure_from_other_team});      
                            }

                            return false;
                        }

                        board[i1][j1] = temp;         
                        positions_of_figures.erase({i1,j1});

                        if(figure_from_other_team != nullptr)
                        {
                            positions_of_figures.insert({{i1,j1}, figure_from_other_team});
                        }
                    }
                }
            }
        }
    }

    return true;
}  


bool Board::Castling(const FigureColor& color, int long_or_short_castling)
{
    if(color == 1)
    {
        Figure* king = GetFigure({0,4});

        if(king == nullptr || typeid(*king) != typeid(King)){return false;}

        King* ptr_king = dynamic_cast<King*>(king);

        if(ptr_king->GetCount() != 0 || ptr_king->GetColor() != color)
        {
            return false;
        }

        if(long_or_short_castling == 2)
        {   
           Figure* rook = GetFigure({0,7});

           if(board[0][5] != 0 || board[0][6] != 0)
           {
                return false; 
           }

           if(rook == nullptr || typeid(*rook) != typeid(Rook))
           {
                return false;
           }

           Rook* ptr_rook = dynamic_cast<Rook*>(rook);

           if(ptr_rook->GetCount() != 0 || ptr_rook->GetColor() != color)
           {
                return false; 
           }

           if(isKingUnderCheck(FigureColor::White, {0,5}) || isKingUnderCheck(FigureColor::White, {0,6}) || isKingUnderCheck(FigureColor::White, {0,4}))
           {
                return false;
           } 

            positions_of_figures.erase({0,4});
            positions_of_figures.insert({{0,6}, ptr_king});


            positions_of_figures.erase({0,7}); 
            positions_of_figures.insert({{0,5}, ptr_rook});

            board[0][5] = 1;
            board[0][6] = 1;
            board[0][7] = 0;
            board[0][4] = 0;

            return true;
        }

        else if(long_or_short_castling == 3)
        {
            Figure* rook = GetFigure({0,0});

           if(board[0][3] != 0 || board[0][2] != 0)
           {
                return false; 
           }

           if(rook == nullptr || typeid(*rook) != typeid(Rook))
           {
                return false;
           }

           Rook* ptr_rook = dynamic_cast<Rook*>(rook);

           if(ptr_rook->GetCount() != 0 || ptr_rook->GetColor() != color)
           {
                return false; 
           }

          if(isKingUnderCheck(FigureColor::White, {0,2}) || isKingUnderCheck(FigureColor::White, {0,3}) || isKingUnderCheck(FigureColor::White, {0,4}))
           {
                return false;
           } 

           positions_of_figures.erase({0,4});
           positions_of_figures.insert({{0,2}, ptr_king});

           positions_of_figures.erase({0,0}); 
           positions_of_figures.insert({{0,3}, ptr_rook});

           board[0][2] = 1;
           board[0][3] = 1;
           board[0][0] = 0;
           board[0][4] = 0;

           return true;
        }
    }

    else 
    {
        Figure* king = GetFigure({7,4});

        if(king == nullptr || typeid(*king) != typeid(King)){return false;}

        King* ptr_king = dynamic_cast<King*>(king);

        if(ptr_king->GetCount() != 0 || ptr_king->GetColor() != color)
        {
            return false;
        }

        if(long_or_short_castling == 2)
        {   
           Figure* rook = GetFigure({7,7});

           if(board[7][5] != 0 || board[7][6] != 0)
           {
                return false; 
           }

           if(rook == nullptr || typeid(*rook) != typeid(Rook))
           {
                return false;
           }

           Rook* ptr_rook = dynamic_cast<Rook*>(rook);

           if(ptr_rook->GetCount() != 0 || ptr_rook->GetColor() != color)
           {
                return false; 
           }

           if(isKingUnderCheck(FigureColor::Black, {7,5}) || isKingUnderCheck(FigureColor::Black, {7,6}) || isKingUnderCheck(FigureColor::Black, {7,4}))
           {
                return false;
           } 

            positions_of_figures.erase({7,4});
            positions_of_figures.insert({{7,6}, ptr_king});

            positions_of_figures.erase({7,7}); 
            positions_of_figures.insert({{7,5}, ptr_rook});

            board[7][5] = -1;
            board[7][6] = -1;
            board[7][7] = 0;
            board[7][4] = 0;

            return true;
        }

        else if(long_or_short_castling == 3)
        {
           Figure* rook = GetFigure({7,0});

           if(board[7][3] != 0 || board[7][2] != 0)
           {
                return false; 
           }

           if(rook == nullptr || typeid(*rook) != typeid(Rook))
           {
                return false;
           }

           Rook* ptr_rook = dynamic_cast<Rook*>(rook);

           if(ptr_rook->GetCount() != 0 || ptr_rook->GetColor() != color)
           {
                return false; 
           } 

          if(isKingUnderCheck(FigureColor::Black, {7,2}) || isKingUnderCheck(FigureColor::Black, {7,3}) || isKingUnderCheck(FigureColor::Black, {7,4}))
           {
                return false;
           } 

           positions_of_figures.erase({7,4});
           positions_of_figures.insert({{7,2}, ptr_king});

           positions_of_figures.erase({7,0}); 
           positions_of_figures.insert({{7,3}, ptr_rook});

           board[7][2] = -1;
           board[7][3] = -1;
           board[7][0] = 0;
           board[7][4] = 0;

           return true;
        }
    }
    return false;
}

void Board::SetPosition(const std::map<std::pair<int, int>, Figure*>& pos)
{
    positions_of_figures = pos;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            auto it = GetFigure({i,j});

            if(it != nullptr)
            {
                board[i][j] = it->GetColor();
            }
            else {
                board[i][j] = 0;
            }
        }
    }
}

std::pair<int, int> Board::KingPosition(const FigureColor &color)
{
    if(color == 1)
    {
        for(auto it : positions_of_figures)
        {
            if(typeid(*it.second) == typeid(King) && color == it.second->GetColor())
            {
                return it.first;
            }
        }
    }


    for(auto it : positions_of_figures)
    {
        if(typeid(*it.second) == typeid(King) && color == it.second->GetColor())
        {
            return it.first;
        }    
    }
    
    
    return {-1, -1};
}