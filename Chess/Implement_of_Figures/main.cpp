#include <iostream> 
#include "raylib.h"
#include <map>
#include "../Figures/King.h"
#include "../Figures/Queen.h"
#include "../Figures/Pawn.h"
#include "../Figures/Knight.h"
#include "../Figures/Rook.h"
#include "../Figures/Bishop.h"
#include "../Figures/Figure.h"
#include "../Figures/Board.h"

const int screenWidth = 800;
const int screenHeight = 800;
const int boardSize = 8;
const int cellSize = 80;

Board board;
std::vector<std::map<std::pair<int, int>, Figure*>> positions;

Figure* figure;
std::pair<int, int> current{-1, -1};
std::pair<int, int> new_pos{-1, -1};
int count = 0;

int temp1 = 0;
int temp2 = 0;

int main()
{

    InitWindow(800, 800, "Menu");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

        DrawText("Menu", 250, 100, 100, BLACK);


        Rectangle rect = {200.0, 300.0, 400, cellSize};
        DrawRectangleRec(rect, BLACK);
        DrawText("Play 1 vs 1", 250, 320, 50, GOLD);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int x = GetMouseX();
            int y = GetMouseY();

            if(x >= 200 && x <= 600 && y > 300 && y < 360)
            {
                break;
            }
        }

        EndDrawing();
    }

    CloseWindow();



    positions.push_back(board.Copy_of_position());

    InitWindow(screenWidth, screenHeight, "Chess Board");
    SetTargetFPS(60);

    Texture bPawn = LoadTexture("./Images/Black_pawn.png");
    Texture2D bRook = LoadTexture("./Images/Black_rook.png");
    Texture2D bKnight = LoadTexture("./Images/Black_knight.png");
    Texture2D bBishop = LoadTexture("./Images/Black_bishop.png");
    Texture2D bQueen = LoadTexture("./Images/Black_queen.png");
    Texture2D bKing = LoadTexture("./Images/Black_king.png");

    Texture2D wPawn = LoadTexture("./Images/White_pawn.png");
    Texture2D wRook = LoadTexture("./Images/White_rook.png");
    Texture2D wKnight = LoadTexture("./Images/White_knight.png");
    Texture2D wBishop = LoadTexture("./Images/White_bishop.png");
    Texture2D wQueen = LoadTexture("./Images/White_queen.png");
    Texture2D wKing = LoadTexture("./Images/White_king.png");

    while (!WindowShouldClose())
    {
        if(IsKeyPressed(KEY_BACKSPACE) && positions.size() > 1)
        {
            positions.pop_back();
            board.SetPosition(positions.back());

            if(count == 1)
            {
                count = 0;
            } else {
                count = 1;
            }
        }

        BeginDrawing();
        ClearBackground(GRAY);

        int boardWidth = boardSize * cellSize;
        int x = (screenWidth - boardWidth) / 2;
        int y = (screenHeight - boardWidth) / 2;

        // Отрисовываем шахматную доску
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if(board.isKingUnderCheck(FigureColor::White))
                {
                    std::pair<int, int> temp = board.KingPosition(FigureColor::White);
                    Color color = RED;
                    int x = (screenWidth - boardWidth) / 2;
                    int y = (screenHeight - boardWidth) / 2;

                    int xPos = x + temp.second * cellSize;
                    int yPos = y + (7 - temp.first) * cellSize;
                    Rectangle rect = {(float)xPos, (float)yPos, cellSize, cellSize };
                    DrawRectangleRec(rect, color);
                }


                if(board.isKingUnderCheck(FigureColor::Black))
                {
                    std::pair<int, int> temp = board.KingPosition(FigureColor::Black);
                    Color color = RED;
                    int x = (screenWidth - boardWidth) / 2;
                    int y = (screenHeight - boardWidth) / 2;

                    int xPos = x + temp.second * cellSize;
                    int yPos = y + (7 - temp.first) * cellSize;
                    Rectangle rect = {(float)xPos, (float)yPos, cellSize, cellSize };
                    DrawRectangleRec(rect, color);
                }


                int tileColor = ((i + j) % 2 == 0) ? 0 : 1;
                Color color = (tileColor == 0) ? WHITE : DARKBROWN;
                int xPos = x + j * cellSize;
                int yPos = y + i * cellSize;
                Rectangle rect = {(float)xPos, (float)yPos, cellSize, cellSize };
                DrawRectangleRec(rect, color);
            }
        }

        // Отрисовываем буквы координат
        for (int i = 0; i < boardSize; i++)
        {
            int xPos = x - 3 + cellSize / 2 + i * cellSize;
            int yPosBot = y + 10 + boardWidth;

            char letter = (char)('a' + i);
            DrawText(&letter, xPos, yPosBot, cellSize/2 - 10, BLACK);
        }
 
        // Отрисовываем цифры координат
        for (int j = 0; j < boardSize; j++)
        {
            int xPosLeft = x - cellSize + cellSize / 2;
            int yPos = y + j * cellSize + cellSize / 2;

            char number = (char)('1' + (boardSize - 1) - j);
            DrawText(&number, xPosLeft, yPos, cellSize/2 - 10, BLACK);
        }

        for(auto it : positions[positions.size() - 1])
        {
            if(typeid(*it.second) == typeid(King))
            {
                if(it.second->GetColor() == 1)
                {
                    DrawTexture(wKing,  (it.first.second + 1) * cellSize + 5, abs(8 - it.first.first) * cellSize + 5, RAYWHITE);
                }

                else {
                    DrawTexture(bKing, (it.first.second + 1) * cellSize + 5, abs(8 - it.first.first) * cellSize + 5, RAYWHITE);                
                }
            }

            else if(typeid(*it.second) == typeid(Rook))
            {
                if(it.second->GetColor() == 1)
                {
                    DrawTexture(wRook, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);    
                }            

                else{
                    DrawTexture(bRook, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);       
                }
            }

            else if(typeid(*it.second) == typeid(Bishop))
            {
                if(it.second->GetColor() == 1)
                {
                    DrawTexture(wBishop, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);       
                }

                else{
                    DrawTexture(bBishop, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);       
                }
            }
            
            else if(typeid(*it.second) == typeid(Queen))
            {
                if(it.second->GetColor() == 1)
                {
                    DrawTexture(wQueen, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);                       
                }

                else{
                    DrawTexture(bQueen, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);
                }
            }

            if(typeid(*it.second) == typeid(Pawn))
            {
                if(it.second->GetColor() == 1)
                {
                     DrawTexture(wPawn, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);
                }

                else{
                     DrawTexture(bPawn, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);
                }
            }

            else if(typeid(*it.second) == typeid(Knight))
            {
                if(it.second->GetColor() == 1)
                {
                     DrawTexture(wKnight, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);
                }

                else{
                    DrawTexture(bKnight, (it.first.second + 1) * cellSize + 5, ((8 - it.first.first)) * cellSize + 5, RAYWHITE);
                }
            }
        }


        if(board.isKingAreMated(FigureColor::White))
        {
            DrawText("Check Mate !", 190, 360, 60, BLACK);
            DrawText("Black Wins !", 190, 420, 60, BLACK);
            EndDrawing();
        }


        if(board.isKingAreMated(FigureColor::Black))
        {
            DrawText("Check Mate!", 250, 360, 60, PURPLE);
            DrawText("White Wins!", 250, 420, 60, PURPLE);
            EndDrawing();
        }


        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           if(current.first == -1 && current.second == -1)
           {

                int current_j = (GetMouseX() / cellSize) - 1;
                int current_i = 7 - abs((GetMouseY() / cellSize) -1);


               figure = board.GetFigure({current_i, current_j});

               if(figure != nullptr)
                {

                    if(count == 1 && figure->GetColor() == -1 || count == 0 && figure->GetColor() == 1)
                    {
                        current.second = current_j;
                        current.first = current_i; 
                    }
                } 
            }
    

           else if(new_pos.first == -1 && new_pos.second == -1)
            {
                int new_pos_j = (GetMouseX() / cellSize) - 1;
                int new_pos_i = 7 - abs((GetMouseY() / cellSize) -1);

                if(new_pos_j >= 8 || new_pos_j < 0 || new_pos_i >= 8 || new_pos_i < 0)
                {
                    continue;
                }

                new_pos.first = new_pos_i;
                new_pos.second = new_pos_j;

                if(board.MoveFigure(figure, figure->GetColor(), current, new_pos))
                {
                    positions.push_back(board.Copy_of_position());

                    if(count == 1)
                    {   
                        count = 0;
                    }

                    else 
                    {
                        count = 1;
                    }
                }

                current = {-1,-1};
                new_pos = {-1,-1};               
            } 
        }

        EndDrawing();
    }
    	
    CloseWindow();
    return 0;
}




