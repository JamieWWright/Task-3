/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "iostream"
#include "string"
struct Ball 
{
    float x, y;
    float speedX, speedY;
    float radius;
};
struct Paddle
{
    float x, y;
    float speed;
    float width, height;

    Rectangle GetRect()
    {
        return Rectangle{ x, y, width, height };
    }
};
struct Game {
    std::string roundEndTxt;
    bool roundEnd;
    bool gameEnd;
    int p1Score;
    int p2Score;
};
int Draw(Paddle P1, Paddle P2, Ball Ball, Game Game)
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawRectangle(P1.x, P1.y, P1.width, P1.height, BLUE);
    DrawRectangle(P2.x, P2.y, P2.width, P2.height, RED);
    DrawCircle(Ball.x, Ball.y, Ball.radius, WHITE);

    if (Game.roundEnd) 
    {
        DrawText(Game.roundEndTxt.c_str(), 350, GetScreenHeight() / 2 - 100, 100, WHITE);

        DrawText(std::to_string(Game.p1Score).c_str(), 800, GetScreenHeight() / 2 + 100, 100, BLUE);
        DrawText("-", 900, GetScreenHeight() / 2 + 100, 100, WHITE);
        DrawText(std::to_string(Game.p2Score).c_str(), 1000, GetScreenHeight() / 2 + 100, 100, RED);
    }

    EndDrawing();
    return 0;
}

int main()
{
    int screenWidth = 1920;
    int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(144);

    bool RoundEnd = false;
    Ball Ball {960, 500, 500, 500, 5};
    Paddle Player1{ 20, screenHeight /2 - 50, 500, 10, 150};
    Paddle Player2{ screenWidth - 30, screenHeight / 2 - 50, 500, 10, 150};
    Game Game {"", false, false, 0, 0};

    Draw(Player1, Player2, Ball, Game);
    while (!WindowShouldClose())
    {
        Ball.x += Ball.speedX * GetFrameTime();
        Ball.y += Ball.speedY * GetFrameTime();

        if (Ball.y > GetScreenHeight())
        {
            Ball.y = GetScreenHeight();
            Ball.speedY *= -1;
        }
        if (Ball.y < 0)
        {
            Ball.y = 0;
            Ball.speedY *= -1;
        }
        if (IsKeyDown(KEY_W)) {
            if(Player1.y >= 0) Player1.y -= Player1.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_S)) {
            if (Player1.y <= screenHeight - 150)Player1.y += Player1.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_UP)) {
            if (Player2.y >= 0)Player2.y -= Player2.speed * GetFrameTime();
        }
        if (IsKeyDown(KEY_DOWN)) {
            if (Player2.y <= screenHeight - 150)Player2.y += Player2.speed * GetFrameTime();
        }
        
        if (CheckCollisionCircleRec(Vector2{ Ball.x,Ball.y }, Ball.radius, Player1.GetRect())) 
        {
            if(Ball.speedX < 0)
            {
                Ball.speedX *= -1.1f;
                Ball.speedY = (Ball.y - Player1.y) / (Player1.height / 2) * Ball.speedX;
            }
        }
        if (CheckCollisionCircleRec(Vector2{ Ball.x,Ball.y }, Ball.radius, Player2.GetRect())) 
        {
            if (Ball.speedX > 0)
            {
                Ball.speedX *= -1.1f;
                Ball.speedY = (Ball.y - Player2.y) / (Player2.height / 2) * Ball.speedX;
            }
        }
        Draw(Player1, Player2, Ball, Game);

        if (Ball.x < Player1.x - 10) {
            Game.roundEnd = true;
            Game.p2Score += 1;
            Game.roundEndTxt = "Player 2 Wins The Round";
            Ball.x = screenHeight / 2;
            Ball.speedX = 0;
            Ball.radius = 0;
        }
        if (Ball.x > Player2.x + 10) {
            Game.roundEnd = true;
            Game.p1Score += 1;
            Game.roundEndTxt = "Player 1 Wins The Round";
            Ball.x = screenHeight/2;
            Ball.speedX = 0;
            Ball.radius = 0;
        }
        if(Game.roundEnd) 
        {
            if (IsKeyPressed(KEY_SPACE)) 
            {
                Game.roundEnd = false;
                Game.roundEndTxt = "";
                Ball = { 900, Ball.y, 500, 500, 5 };
            }
        }
    }
    CloseWindow();

    return 0;
}

