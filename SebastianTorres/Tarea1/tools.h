#pragma once

#ifndef TOOLS_H_INCLUDE
#define TOOLS_H_INCLUDE

#ifdef __cplusplus
/// Common C++ headers
#include <iostream>
#include <string>
#include <cstdio> // for printf()
#else
#include <stdio.h>	// for printf()
#include <string.h> // for strlen()
#endif				// __cplusplus

#ifdef _WIN32
#include <windows.h> // for WinAPI and Sleep()
#define _NO_OLDNAMES // for MinGW compatibility
#include <conio.h>	 // for getch() and kbhit()
#define getch _getch
#define kbhit _kbhit
#else
#include <termios.h>   // for getch() and kbhit()
#include <unistd.h>	   // for getch(), kbhit() and (u)sleep()
#include <sys/ioctl.h> // for getkey()
#include <sys/types.h> // for kbhit()
#include <sys/time.h>  // for kbhit()

/// Function: getch
int getch(void)
{
	setbuf(stdin, NULL);
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

/*/// Function: kbhit
/// Determines if keyboard has been hit.
/// Windows has this in conio.h
int kbhit(void)
{
	static short first = 1;
	static struct termios newt;
	int bytes = 0;
	if (first)
	{
		setbuf(stdin, NULL);
		tcgetattr(STDIN_FILENO, &newt);
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		first = 0;
	}
	ioctl(STDIN_FILENO, FIONREAD, &bytes);
	return bytes > 0 ? 1 : 0;
}*/

void keyboard(unsigned short st)
{
	static struct termios oldt, newt;
	static short first = 1;
	if (first)
	{
		tcgetattr(STDIN_FILENO, &oldt);
		first = 0;
	}
	if (st)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
	else
	{
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	}
}

#endif

/// Function: cleanBuffer
/// Limpia el buffer de entrada.
void cleanBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

/// TABLA DE VALORES DE COLORES
/// Definición de las constantes para cada color.

#ifdef __cplusplus
#ifndef TOOLS_STRING_T
typedef std::string TOOLS_STRING_T;
#define writhLine(text) std::cout << text;
#endif // TOOLS_STRING_T

#else // __cplusplus
#ifndef TOOLS_STRING_T
typedef const char *TOOLS_STRING_T;
#define writhLine(text) printf("%s", text);
#endif // TOOLS_STRING_T

#endif // __cplusplus

// Secuencia de espace ANSI

const TOOLS_STRING_T ANSI_CLEAR = "\033[2J\033[3J\033[1;1H";
const TOOLS_STRING_T ANSI_CONSOLE_TITLE_PRE = "\033]0;";
const TOOLS_STRING_T ANSI_CONSOLE_TITLE_POS = "\007";
const TOOLS_STRING_T ANSI_CURSOR_HIDE = "\033[?25l";
const TOOLS_STRING_T ANSI_CURSOR_SHOW = "\033[?25h";
const TOOLS_STRING_T ANSI_RESET_COLOR = "\033[0m";
const TOOLS_STRING_T ANSI_BLACK = "\033[30m";
const TOOLS_STRING_T ANSI_RED = "\033[31m";
const TOOLS_STRING_T ANSI_GREEN = "\033[32m";
const TOOLS_STRING_T ANSI_YELLOW = "\033[33m";
const TOOLS_STRING_T ANSI_BLUE = "\033[34m";
const TOOLS_STRING_T ANSI_MAGENTA = "\033[35m";
const TOOLS_STRING_T ANSI_CYAN = "\033[36m";
const TOOLS_STRING_T ANSI_WHITE = "\033[37m";
const TOOLS_STRING_T ANSI_BRIGHT_BLACK = "\033[90m";
const TOOLS_STRING_T ANSI_BRIGHT_RED = "\033[91m";
const TOOLS_STRING_T ANSI_BRIGHT_GREEN = "\033[92m";
const TOOLS_STRING_T ANSI_BRIGHT_YELLOW = "\033[93m";
const TOOLS_STRING_T ANSI_BRIGHT_BLUE = "\033[94m";
const TOOLS_STRING_T ANSI_BRIGHT_MAGENTA = "\033[95m";
const TOOLS_STRING_T ANSI_BRIGHT_CYAN = "\033[96m";
const TOOLS_STRING_T ANSI_BRIGHT_WHITE = "\033[97m";
const TOOLS_STRING_T ANSI_BACKGROUND_BLACK = "\033[40m";
const TOOLS_STRING_T ANSI_BACKGROUND_RED = "\033[41m";
const TOOLS_STRING_T ANSI_BACKGROUND_GREEN = "\033[42m";
const TOOLS_STRING_T ANSI_BACKGROUND_YELLOW = "\033[43m";
const TOOLS_STRING_T ANSI_BACKGROUND_BLUE = "\033[44m";
const TOOLS_STRING_T ANSI_BACKGROUND_MAGENTA = "\033[45m";
const TOOLS_STRING_T ANSI_BACKGROUND_CYAN = "\033[46m";
const TOOLS_STRING_T ANSI_BACKGROUND_WHITE = "\033[47m";
const TOOLS_STRING_T ANSI_BACKGROUND_BRIGHT_BLACK = "\033[100m";
const TOOLS_STRING_T ANSI_BACKGROUND_BRIGHT_RED = "\033[101m";
const TOOLS_STRING_T ANSI_BACKGROUND_BRIGHT_GREEN = "\033[102m";
const TOOLS_STRING_T ANSI_BACKGROUND_BRIGHT_YELLOW = "\033[103m";
const TOOLS_STRING_T ANSI_BACKGROUND_BRIGHT_BLUE = "\033[104m";
const TOOLS_STRING_T ANSI_BACKGROUND_BRIGHT_MAGENTA = "\033[105m";
const TOOLS_STRING_T ANSI_BACKGROUND_BRIGHT_CYAN = "\033[106m";
const TOOLS_STRING_T ANSI_BACKGROUND_BRIGHT_WHITE = "\033[107m";

TOOLS_STRING_T GetANSIColor(const int c)
{
	switch (c)
	{
	case 0:
		return ANSI_BLACK;
	case 1:
		return ANSI_RED;
	case 2:
		return ANSI_GREEN;
	case 3:
		return ANSI_YELLOW;
	case 4:
		return ANSI_BLUE;
	case 5:
		return ANSI_MAGENTA;
	case 6:
		return ANSI_CYAN;
	case 7:
		return ANSI_WHITE;
	case 8:
		return ANSI_BRIGHT_BLACK;
	case 9:
		return ANSI_BRIGHT_RED;
	case 10:
		return ANSI_BRIGHT_GREEN;
	case 11:
		return ANSI_BRIGHT_YELLOW;
	case 12:
		return ANSI_BRIGHT_BLUE;
	case 13:
		return ANSI_BRIGHT_MAGENTA;
	case 14:
		return ANSI_BRIGHT_CYAN;
	case 15:
		return ANSI_BRIGHT_WHITE;
	default:
		return "";
	}
}

TOOLS_STRING_T GetANSIBackgroundColor(const int c)
{
	switch (c)
	{
	case 0:
		return ANSI_BACKGROUND_BLACK;
	case 1:
		return ANSI_BACKGROUND_RED;
	case 2:
		return ANSI_BACKGROUND_GREEN;
	case 3:
		return ANSI_BACKGROUND_YELLOW;
	case 4:
		return ANSI_BACKGROUND_BLUE;
	case 5:
		return ANSI_BACKGROUND_MAGENTA;
	case 6:
		return ANSI_BACKGROUND_CYAN;
	case 7:
		return ANSI_BACKGROUND_WHITE;
	case 8:
		return ANSI_BACKGROUND_BRIGHT_BLACK;
	case 9:
		return ANSI_BACKGROUND_BRIGHT_RED;
	case 10:
		return ANSI_BACKGROUND_BRIGHT_GREEN;
	case 11:
		return ANSI_BACKGROUND_BRIGHT_YELLOW;
	case 12:
		return ANSI_BACKGROUND_BRIGHT_BLUE;
	case 13:
		return ANSI_BACKGROUND_BRIGHT_MAGENTA;
	case 14:
		return ANSI_BACKGROUND_BRIGHT_CYAN;
	case 15:
		return ANSI_BACKGROUND_BRIGHT_WHITE;
	default:
		return "";
	}
}

/// Function: setColor
/// Color del texto, Colocar el nombre del color de acuerdo
/// a la tabla.
void setColor(const int color)
{
	writhLine(GetANSIColor(color)) //printf("%s",GetANSIColor(color));		// \033 o %c -> 0x1B
}

/// Function: backgroundColor
/// Establece un color de fondo.
void setBackgroundColor(const int color)
{
	writhLine(GetANSIBackgroundColor(color));
}

/// Function: resetColor
/// Reestablece el color inicial que tenia
void resetColor()
{
	writhLine(ANSI_RESET_COLOR);
}

/// Function: cls
/// Borra la pantalla y coloca el cursor en la posicion (0,0).
void cls(void)
{
	writhLine(ANSI_CLEAR);
}

/// Function: gotoxy
/// El cursor se mueve a <x>; <y> coordenada dentro de la ventana gráfica, donde <x>
///	es la columna de la línea  <y>
void gotoxy(int x, int y)
{
	printf("\033[%d;%dH", y + 1, x + 1);
}

//	Function: consoleTitle
//	Coloca un titulo a la terminal
// 	Solo funciona para la consula nueva de windows.
void consoleTitle(const char *title)
{
	writhLine(ANSI_CONSOLE_TITLE_PRE + title + ANSI_CONSOLE_TITLE_POS);
}

void msleep(unsigned int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	// usleep argument must be under 1 000 000
	if (ms > 1000)
		sleep(ms / 1000000);
	usleep((ms % 1000000) * 1000);
#endif
}

void setCursorVisibility(char visible)
{
#if defined(_WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsoleOutput, &structCursorInfo); // Get current cursor size
	structCursorInfo.bVisible = (visible ? TRUE : FALSE);
	SetConsoleCursorInfo(hConsoleOutput, &structCursorInfo);
#else  // _WIN32 || USE_ANSI
	//printf(visible ? ANSI_CURSOR_SHOW : ANSI_CURSOR_HIDE);
#endif // _WIN32 || USE_ANSI
}

/// Function: hidecursor
/// Hides the cursor.
void hidecursor(void)
{
	setCursorVisibility(0);
}

/// Function: showcursor
/// Shows the cursor.
void showcursor(void)
{
	setCursorVisibility(1);
}

#endif // TOOLS_H_INCLUDE
