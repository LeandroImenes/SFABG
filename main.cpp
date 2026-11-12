#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

int main() {
    _putenv_s("GALLIUM_DRIVER", "llvmpipe");

    const int width = 1920;
    const int height = 1010;
    char* raio = "Gama";
    int magnetField = 150;
    int cont = 0;
    Vector2 magPos = {700, 700};
    Vector2 circlePos = {300, 300};
    Vector2 speed = {0, 0};
    Color circleColor = BLUE;
    const int radius = 20;
    const int magRadius = 20;
    Rectangle rec = {820, 0, 300, 150};
    Rectangle mag = {500, 300, 300, 400};
    Color reColor = GREEN;
    int color = 1;
    bool holding = false;
    bool holdingM = false;
    Vector2 posCor = {0, 0};
    Vector2 posCorMag = {0, 0};
    double w = 0;
    cont = 0;

    double m = 0;
    int q = 0;
    double B = 4;
    double v = 1;


    InitWindow(width, height, "Simulação de onda");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        int tecla = GetKeyPressed();
        if(tecla == 32){
            if(color == 1){
                reColor = RED;
                color = 2;
                raio = "Alfa";
                m = 40;
                q = 2;
            }else if(color == 2){
                color = 3;
                reColor = BLUE;
                raio = "Beta";
                m = 4;
                q = -1;
                }else if(color == 3){
                    reColor = GREEN;
                    color = 1;
                    raio = "Gama";
                    m = 0;
                    q = 0;
            }
        }
        Vector2 mousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointCircle(mousePos, circlePos, radius)) {
                holding = true;
                posCor.y = mousePos.y - circlePos.y;
                posCor.x = mousePos.x - circlePos.x;
            }
            if (CheckCollisionPointCircle(mousePos, magPos, magRadius)) {
                holdingM = true;
                posCorMag.y = mousePos.y - magPos.y;
                posCorMag.x = mousePos.x - magPos.x;
            }
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            holding = false;
            holdingM = false;
        }
        else if (CheckCollisionPointCircle(mousePos, circlePos, radius)) {
            circleColor = PURPLE;
        }
        else {
            circleColor = BLUE;
        }
        if (holding == true){
            circleColor = RED;
            circlePos.x = mousePos.x - posCor.x;
            circlePos.y = mousePos.y - posCor.y;
        }
        if (holdingM == true){
            magPos.x = mousePos.x - posCorMag.x;
            magPos.y = mousePos.y - posCorMag.y;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleRec(mag, DARKGREEN);
        Vector2 position = circlePos;
        Vector2 v = {180, 0};
        if(color == 1){
        for(int i = circlePos.x; i <= (width); i++){
            DrawRectangle(i, circlePos.y, 4, 4, reColor);
        }
        }else{
            for(float x = circlePos.x; x <= 2000; x++){
                if (CheckCollisionPointRec(position, mag)){

                    w = (q * B / m);
                    double angle = w / 60;

                    double oldX = v.x;
                    double oldY = v.y;

                    v.x = oldX * cos(angle) - oldY * sin(angle);

                    v.y = oldX * sin(angle) + oldY * cos(angle);
                }
            position.x += v.x / 60;
            position.y += v.y / 60;

            DrawRectangle((int)position.x, (int)position.y, 4, 4, reColor);

            if (position.y < 0 || position.y > height) break;
            }
        }
        DrawCircleV(circlePos, radius, circleColor);
        DrawRectangleRec(rec, reColor);
        DrawText(TextFormat("%s", raio), 880, 20, 80, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}