#include <stdio.h>
#include <Windows.h>
#include <time.h>

#include <conio.h>

#ifndef DEBUG
#define DEBUG

#define DEBUGING

#define DARK_BLACK          0
#define DARK_BLUE           1
#define DARK_GREEN          2
#define DARK_CYAN           3
#define DARK_RED            4 
#define DARK_PINK           5
#define DARK_YELLOW         6
#define DARK_WHITE          7
#define LIGHT_BLACK         8
#define LIGHT_BLUE			9
#define LIGHT_GREEN         10
#define LIGHT_CYAN          11
#define LIGHT_RED           12
#define LIGHT_PINK          13
#define LIGHT_YELLOW        14
#define LIGHT_WHITE         15

#define SETCOLOR(back, front) ((back) << 4 | (front))

inline void SetColor(int back, int front) {
    static HANDLE handle = 0;
    if(!handle) handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, SETCOLOR(back, front));
}

#define TIMESTAMP \
    SetColor(LIGHT_BLACK, LIGHT_WHITE); \
    printf("[%d | line(%d)]:", time(0), __LINE__);

#ifndef DEBUGING
#define CONSOLE_WARNING(msg, ...)
#define CONSOLE_MESSAGE(msg, ...)
#define CONSOLE_ERROR  (msg, ...) \
	exit(EXIT_FAILURE);
#else

#define CONSOLE_WARNING(msg, ...) \
	TIMESTAMP \
	SetColor(DARK_BLACK, DARK_YELLOW); \
	printf("  "); \
	printf(msg, ## __VA_ARGS__); \
	putchar('\n');

#define CONSOLE_MESSAGE(msg, ...) \
	TIMESTAMP \
	SetColor(DARK_BLACK, DARK_WHITE); \
	printf("  "); \
	printf(msg, ## __VA_ARGS__); \
	putchar('\n');

#define CONSOLE_ERROR(msg, ...) \
	TIMESTAMP \
	SetColor(DARK_BLACK, DARK_RED); \
	printf("  "); \
	printf(msg,## __VA_ARGS__); \
	putchar('\n'); \
	getch(); \
    exit(EXIT_FAILURE);
#endif

#endif