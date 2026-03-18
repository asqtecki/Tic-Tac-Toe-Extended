#include <iostream>
#include <raylib.h>
using namespace std;

struct Screen {
    const int width = 800;
    const int height = 600;
};

class Button {
    Vector2 position;
    Texture2D texture; //to store the path
    int width, height; 
    float scale; //for resizing
    public:
        Button(const char* path, Vector2 pos, float s) : scale(s) {
            Image img = LoadImage(path);
            width = static_cast<int>(img.width * scale);
            height = static_cast<int>(img.height * scale);
            ImageResize(&img, width, height);
            texture = LoadTextureFromImage(img);
            position = pos;
        }
        void Draw() {
            DrawTextureV(texture, position, WHITE);
        }
        bool isClicked(Vector2 pos, bool isPressed) {
            Rectangle rect{position.x, position.y, (float)width, (float)height};
            return CheckCollisionPointRec(pos, rect) && isPressed;
        }
        ~Button() {
            UnloadTexture(texture);
        }
};

class Board {
    int posX, posY; //coordinates
    int size; //size of board sizeXsize
    char cell[3][3]; //input array
    float boldness; //thickness of lines
    int cellSize; //per cell size
    int turn; //odd = X, even = O
    public:
        static int counter;
        Board() : turn(1) {
            size = 450;
            posX = (GetScreenWidth() - size)/2;
            posY = (GetScreenHeight() - size)/2;
            for (int i=0;i<3;i++) {
                for (int j=0;j<3;j++) cell[i][j] = ' ';
            }
            boldness = 5;
            cellSize = size/3;
        }
        void Draw() {
            DrawRectangle(posX + cellSize, posY, boldness, size, RAYWHITE);
            DrawRectangle(posX + 2*cellSize, posY, boldness, size, RAYWHITE);
            DrawRectangle(posX, posY + cellSize, size, boldness, RAYWHITE);
            DrawRectangle(posX, posY + 2*cellSize, size, boldness, RAYWHITE);
            for (int i=0;i<3;i++) {
                for (int j=0;j<3;j++) {
                    if (cell[i][j] != ' ')
                        DrawText(TextFormat("%c", cell[i][j]), posX + j*cellSize + cellSize/2 - 10, posY + i*cellSize + cellSize/2 - 10, 40, RAYWHITE);
                }
            }
            if (win() == 'N' && counter < 9)
                DrawText(TextFormat("Turn: %c", (turn % 2 != 0) ? 'X' : 'O'), 10, 10, 20, RAYWHITE);
        }
        void Play(Vector2 pos) {
            int row = (pos.y - posY) / cellSize;
            int col = (pos.x - posX) / cellSize;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && cell[row][col] == ' ') {
                cell[row][col] = (turn % 2 != 0) ? 'X' : 'O';
                turn++;
                counter++;
            }
        }
        char win() {
            for (int i=0;i<3;i++) {
                if (cell[i][0] != ' ' && cell[i][0] == cell[i][1] && cell[i][1] == cell[i][2]) return cell[i][0];
                if (cell[0][i] != ' ' && cell[0][i] == cell[1][i] && cell[1][i] == cell[2][i]) return cell[0][i];
            }
            if (cell[0][0] != ' ' && cell[0][0] == cell[1][1] && cell[1][1] == cell[2][2]) return cell[0][0];
            if (cell[0][2] != ' ' && cell[0][2] == cell[1][1] && cell[1][1] == cell[2][0]) return cell[0][2];
            return 'N';
        }
        void Reset() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) cell[i][j] = ' ';
            }
            turn = 1;
            counter = 0;
        }
};
int Board::counter = 0;

int main () {
    Screen s;
    bool game = false;
    float timer = 0.0f;

    //start
    InitWindow(s.width, s.height, "Tic Tac Toe");
    SetTargetFPS(60);
    Texture2D bg = LoadTexture("Graphics/bg.jpg");
    Button start_b{"Graphics/start.png", {(float)s.width/2-100, (float)s.height/2-100}, 0.2f};
    Board b;

    //game loop
    while (!WindowShouldClose()) {
        Vector2 position = GetMousePosition();
        bool isPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (!game) {
            if (start_b.isClicked(position, isPressed)) {
                game = true;
                b.Reset();
                cout << "Starting game...\n";
            }
        }
        else {
            if (isPressed && b.win() == 'N' && Board::counter < 9) b.Play(position);
        }

        if (game && (b.win() != 'N' || Board::counter >= 9)) {
            timer += GetFrameTime();
            if (timer > 2.5f) {
                game = false;
                timer = 0.0f;
            }
        }

        BeginDrawing();
        ClearBackground(GREEN);
        DrawTexture(bg, 0, 0, WHITE);
        DrawRectangle(0, 0, s.width, s.height, Fade(BLACK, 0.5f));
        if (!game) start_b.Draw();
        else { //game definition
            b.Draw();
            if (b.win() != 'N')
                DrawText(TextFormat("Player %c wins!", b.win()), s.width/2 - 60, s.height/2 + 250, 20, RAYWHITE);
            else if (Board::counter >= 9)
                DrawText(TextFormat("It's a draw!"), s.width/2 - 60, s.height/2 + 250, 20, RAYWHITE);
        }
        EndDrawing();
    }

    //terminate
    UnloadTexture(bg);
    CloseWindow();
}