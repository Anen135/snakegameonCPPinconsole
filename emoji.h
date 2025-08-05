#pragma once
#include "snake.h"
#include <string.h>

#define EMOJI_X 42
#define EMOJI_Y 5
#define EMOJI_DELICIOUS "(≧◡≦) Oishii~! Delicious, Nyaa~!"
#define EMOJI_HIT "(╥﹏╥) Painful, Nyaa~!"
#define CLEAR_EMOJI ""

char emoji[64] = CLEAR_EMOJI; // Буфер для хранения эмоции


#ifdef _WIN32
DWORD WINAPI emotion_timer(LPVOID lpParam) {
    Sleep(1000);
    strcpy(emoji, CLEAR_EMOJI);
    return 0;
}

#else
void *emotion_timer(void *arg) {
    Sleep(1000);
    strcpy(emoji, CLEAR_EMOJI);
    return NULL;
}
#endif
void show_emotion(const char *emotion) {
    #ifdef _WIN32
        strncpy(emoji, emotion, sizeof(emoji) - 1); // Копируем эмоцию
        CreateThread(NULL, 0, emotion_timer, NULL, 0, NULL);
    #else
        pthread_t thread;
        pthread_create(&thread, NULL, emotion_timer, NULL);
        pthread_detach(thread);
    #endif
}
