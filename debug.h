/*
	Author : Jason.Ghost
	Time : 2016/7/3
*/
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#include <conio.h>

#ifndef DEBUG
#define DEBUG

// control model that debug on console or in file.
// priority level of 'FILE_DEBUG' larger than 'CONSOLE_DEBUG'
#define FILE_DEBUG
#define CONSOLE_DEBUG

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

FILE * DEBUG_FILE = NULL;
const char DEBUG_FILE_NAME[] = "debug.log";

// must invoke this function on the head of application when you use file to debug!
inline void InitFileDebug(void) {
	DEBUG_FILE = fopen(DEBUG_FILE_NAME, "a+");
	if (DEBUG_FILE == NULL) exit(EXIT_FAILURE);
}

inline void SetColor(int back, int front) {
    static HANDLE handle = 0;
    if(!handle) handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, SETCOLOR(back, front));
}

#ifdef FILE_DEBUG
#define TIMESTAMP \
    SetColor(LIGHT_BLACK, LIGHT_WHITE); \
    printf("[%d | line(%d)]:", time(0), __LINE__);
#else
#define TIMESTAMP \
    fprintf(DEBUG_FILE, "[%d | line(%d)]:", time(0), __LINE__);
#endif

#ifdef FILE_DEBUG

	#define DEBUG_WARNING(msg, ...) \
		TIMESTAMP \
		fprintf(DEBUG_FILE, "  "); \
		fprintf(DEBUG_FILE, msg, ## __VA_ARGS__); \
		fprintf(DEBUG_FILE, "\n");

	#define DEBUG_MESSAGE(msg, ...) \
		TIMESTAMP \
		fprintf(DEBUG_FILE, "  "); \
		fprintf(DEBUG_FILE, msg, ## __VA_ARGS__); \
		fprintf(DEBUG_FILE, "\n");

	#define DEBUG_ERROR(msg, ...) \
		TIMESTAMP \
		fprintf(DEBUG_FILE, "  "); \
		fprintf(DEBUG_FILE, msg,## __VA_ARGS__); \
		fprintf(DEBUG_FILE, "\n"); \
		exit(EXIT_FAILURE);

#else

#ifndef CONSOLE_DEBUG

	#define DEBUG_WARNING(msg, ...)
	#define DEBUG_MESSAGE(msg, ...)
	#define DEBUG_ERROR  (msg, ...) \
		exit(EXIT_FAILURE);

#else

	#define DEBUG_WARNING(msg, ...) \
		TIMESTAMP \
		SetColor(DARK_BLACK, DARK_YELLOW); \
		printf("  "); \
		printf(msg, ## __VA_ARGS__); \
		putchar('\n');

	#define DEBUG_MESSAGE(msg, ...) \
		TIMESTAMP \
		SetColor(DARK_BLACK, DARK_WHITE); \
		printf("  "); \
		printf(msg, ## __VA_ARGS__); \
		putchar('\n');

	#define DEBUG_ERROR(msg, ...) \
		TIMESTAMP \
		SetColor(DARK_BLACK, DARK_RED); \
		printf("  "); \
		printf(msg,## __VA_ARGS__); \
		putchar('\n'); \
		getch(); \
		exit(EXIT_FAILURE);


#endif

#endif

#endif