#include "snake.h"
#include "record.h"
#include "emoji.h"

void draw_board() {
    printf("\033[H");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                printf("##");
            else if (i == food.y && j == food.x)
                printf(RED("Q "));
            else {
                int is_snake = 0;
                for (int k = 0; k < snake_length; k++) {
                    if (snake[k].x == j && snake[k].y == i) {
                        printf(GREEN("@ "));
                        is_snake = 1;
                        break;
                    }
                }
                if (!is_snake) printf(". ");
            }
        }
        printf("\n");
    }
}
void generate_food() {
    for (int a = 1; a;) {
        food.x = (rand() % (WIDTH - 2)) + 1;
        food.y = (rand() % (HEIGHT - 2)) + 1;
        for (int i = 0; i < snake_length; i++) {a = (snake[i].x == food.x && snake[i].y == food.y) ? 1 : 0; break;}
    }
}

void update_snake() {
    for (int i = snake_length; i > 0; --i) snake[i] = snake[i - 1];
    
    switch (direction) {
        case UP:    snake[0].y--; break;
        case DOWN:  snake[0].y++; break;
        case LEFT:  snake[0].x--; break;
        case RIGHT: snake[0].x++; break;
    }
    if (snake[0].x == 0 || snake[0].x == WIDTH - 1 || snake[0].y == 0 || snake[0].y == HEIGHT - 1) {
        game_state &= ~1;
        return;
    }    
    for (int i = 1; i < snake_length; ++i) {
        if (snake[i].x == snake[0].x && snake[i].y == snake[0].y) {
            game_state &= ~1;
            return;
        }
    }    
    if (snake[0].x == food.x && snake[0].y == food.y) {
        ++snake_length;
        //show_emotion(EMOJI_DELICIOUS);
        generate_food();
    }
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == UP && direction != DOWN) direction = UP;
        else if (key == DOWN && direction != UP) direction = DOWN;
        else if (key == LEFT && direction != RIGHT) direction = LEFT;
        else if (key == RIGHT && direction != LEFT) direction = RIGHT;
        else if (key == 'p') game_state |= 2;
    }
}

int main() {

    srand(1);
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    generate_food();
    load_record();
    gotoxy(0, HEIGHT+2);
    printf("\033[?25l\033[0J");
    PRINT_RECORD;   
    while (game_state & 1) {
        draw_board();
        printf("Score:\t%d\n", snake_length);
        if (game_state & 2) {
            PAUSE;
            game_state &= ~2;
        };
        input();
        update_snake();
        Sleep(100);
    }
    //show_emotion(EMOJI_HIT);
    printf("\033[?25h");
    NEW_RECORD(snake_length);
    gotoxy(WIDTH-4, HEIGHT / 2);
    printf(BLINKING("GAME OVER"));
    gotoxy(0, HEIGHT+3);
    printf("\033[0J");
    return 0;
}
