#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#ifndef _WIN32
#include <unistd.h>
#define Sleep(x) usleep(x * 1000)
#else
#include <windows.h>
#endif

#define WIDTH 20
#define HEIGHT 20
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define RED(t) "\033[31;1m" t "\033[0m"
#define GREEN(t) "\033[32;1m" t "\033[0m"
#define BLINKING(t) "\033[5;1m" t "\033[0m"
#define RESETFLAG(f) &= ~f
#define SETFLAG(f) |= f
#define CHECKFLAG(f) &f
#define TOGGLEFLAG(f) ^= f
#define clear_down "\033[0J"

#define USE(ansi_code) printf(ansi_code)


typedef struct {
    short x, y;
} Point;

#define gotoxy(_x, _y) printf("\033[%d;%dH", _y, _x)
#define PAUSE gotoxy(WIDTH-2  , HEIGHT / 2); printf(BLINKING("PAUSE")); _getch()

Point snake[100];
Point food;
char snake_length = 1;
char direction = RIGHT;
char game_state = 3;
/*
Game over    state: ???????X
Game paused  state: ??????X?
*/