// pipeServidor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <iostream>


#include <chrono>

#include <fstream>
#include <conio.h>
#include <stdlib.h>


#include <iomanip>
#include <ciso646>
#include <algorithm>
#include <array>
#include <tuple>
#include <string>
#include <string_view>
#include <iterator>
#include <utility>

#include <thread>
#include <random>
#include <sstream>
#include <string>
#include <cstring>
#pragma comment(lib, "Winmm.lib")

/*---------------------inicio color------------------*/
namespace Win32::ConsoleApi
{
	enum class ConsoleColor : WORD
	{
		Black = 0,
		DarkBlue = 1,
		DarkGreen = 2,
		DarkCyan = 3,
		DarkRed = 4,
		DarkMagenta = 5,
		DarkYellow = 6,
		Gray = 7,
		DarkGray = 8,
		Blue = 9,
		Green = 10,
		Cyan = 11,
		Red = 12,
		Magenta = 13,
		Yellow = 14,
		White = 15
	};

	constexpr WORD ForegroundMask = 0xf;
	constexpr WORD BackgroundMask = 0xf0;

	constexpr WORD ConsoleColorToColorAttribute(ConsoleColor color, bool is_background) noexcept
	{
		if (is_background)
			return static_cast<WORD>((static_cast<int32_t>(color) << 4));

		return static_cast<WORD>(color);
	}

	constexpr ConsoleColor ColorAttributeToConsoleColor(WORD color) noexcept
	{
		if ((color & BackgroundMask) != 0)
			color = static_cast<WORD>((((int32_t)color) >> 4));

		return (ConsoleColor)color;
	}

	void SetForegroundColor(const ConsoleColor value) noexcept
	{
		WORD color = ConsoleColorToColorAttribute(value, false);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		WORD attrs = csbi.wAttributes;
		attrs &= ~((WORD)ForegroundMask);

		attrs = (WORD)(((DWORD32)(WORD)attrs) | ((DWORD32)(WORD)color));

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attrs);
	}

	namespace Implementation
	{
		struct ConsoleColorImpl
		{
			ConsoleColor Color;
		};
	}

	inline Implementation::ConsoleColorImpl SetColor(ConsoleColor color) noexcept
	{
		return { color };
	}

	inline ::std::ostream& operator<<(::std::ostream& os, const Implementation::ConsoleColorImpl& color_impl) noexcept
	{
		return SetForegroundColor(color_impl.Color), os;
	}
}

namespace Win32
{
	using Win32::ConsoleApi::SetColor;
	using Win32::ConsoleApi::ConsoleColor;
	using Win32::ConsoleApi::operator<<;
}

class Timer
{
public:
	Timer() noexcept : m_StartTimePoint{ std::chrono::high_resolution_clock::now() }
	{
	}

	~Timer() noexcept
	{
		Stop();
	}

	void Stop() noexcept
	{
		auto end_time_point = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch();
		auto duration = end - start;
		double ms = duration.count() * 0.001;

		using namespace Win32;

		std::cout << SetColor(ConsoleColor::Yellow) << (char32_t*)& duration << SetColor(ConsoleColor::Green) << " (" << ms << "ms)\n" << SetColor(ConsoleColor::Gray);
		std::cout << SetColor(ConsoleColor::Yellow);
		std::cout << (char32_t*)& duration;
		std::cout << (char32_t*)& duration << SetColor(ConsoleColor::Green);

		std::cout << "hola" << "hola2" << "hola3";
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};

struct StructValue
{
	int32_t Value;
	/*bool operator==(const StructValue&) const = default;
	auto operator<=>(const StructValue&) const = default;*/
};

StructValue& operator++(StructValue& struct_value) noexcept
{
	++struct_value.Value;
	return struct_value;
}

StructValue operator++(StructValue& struct_value, int) noexcept
{
	StructValue temp = struct_value;
	++struct_value.Value;
	return temp;
}

/*---------------------fin color------------------*/

using namespace std;
int32_t main(void)
{	
	using namespace Win32;
	HANDLE hPipe1,hPipe2,hPipeServer, hPipeServer2;
	char buffer1[1024], buffer2[1024], bServer[1024];
	DWORD dwRead1, dwRead2,dwWriteServer;
	HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD coordAviso= { .X = 25 ,.Y = 0 };
	SetConsoleCursorPosition(hOutputConsole, coordAviso);
	cout << SetColor(ConsoleColor::Magenta) << ".::SI LOS PARTICIPANTES ESTAN LISTOS PRESIONE 0 PARA COMENZAR LA CARRERA::. " << endl;

	int32_t senial;
	cin >> senial;

	hPipeServer = CreateFile(TEXT("\\\\.\\pipe\\PipeServer"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	hPipeServer2 = CreateFile(TEXT("\\\\.\\pipe\\PipeServer2"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	
	if (senial == 0)
	{

		if (hPipeServer != INVALID_HANDLE_VALUE)
		{

			WriteFile(hPipeServer,
				"Start",
				5,
				&dwWriteServer,
				NULL);

			CloseHandle(hPipeServer);
		}
		if (hPipeServer2 != INVALID_HANDLE_VALUE)
		{

			WriteFile(hPipeServer2,
				"Start",
				5,
				&dwWriteServer,
				NULL);

			CloseHandle(hPipeServer2);
		}

	}
	else
	{
		return 0;
	}

	hPipe1 = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipecarrito1"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 
		PIPE_UNLIMITED_INSTANCES,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	hPipe2 = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipecarrito2"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,   
		PIPE_UNLIMITED_INSTANCES,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	if (hPipe1 == INVALID_HANDLE_VALUE)
	{
		cout << "Fallo!!!" << endl;
	}
	if (hPipe2 == INVALID_HANDLE_VALUE)
	{
		cout << "Fallo!!!" << endl;
	}
	
	SHORT car1X, car1Y;
	SHORT car2X, car2Y;
	COORD coord1;// = { .X = car1X,.Y = car1Y };
	COORD coord2;// = { .X = car2X,.Y = car2Y };

	SHORT car1XX = 5, car1YY = 3, car2XX = 5, car2YY = 10;
	COORD coordinicio1 = { .X = car1XX,.Y = car1YY };
	COORD coordinicio2 = { .X = car2XX,.Y = car2YY };
	COORD coordAnuncioGanador = { .X = 50 ,.Y = 14 };
	COORD coordAnuncioPerdedor = { .X = 50 ,.Y = 15 };

	car1Y = 3;
	car2Y = 10;
	car1X = 16;
	car2X = 16;
	int32_t val1=0, val2=0;
	bool bandera = true;
	int32_t contador = 0;
	while (true)
	{
		
		SetConsoleCursorPosition(hOutputConsole, coordinicio1);
		cout << SetColor(ConsoleColor::Blue) << "CARRITO1:::  " << endl;
		SetConsoleCursorPosition(hOutputConsole, coordinicio2);
		cout << SetColor(ConsoleColor::Yellow) <<"CARRITO2:::  " << endl;

		if ((ConnectNamedPipe(hPipe2, NULL) != FALSE))
		{
			
			while ((ReadFile(hPipe2, buffer2, sizeof(buffer2) - 1, &dwRead2, NULL) != FALSE))
			{
				buffer2[dwRead2] = '\0';
				string ac = (char*)& buffer2[0];
				string ac2 = { ac[0],ac[1] };
				val2 = stoi(ac2);
		
			}
		}

		DisconnectNamedPipe(hPipe2);
		
		if ((ConnectNamedPipe(hPipe1, NULL) != FALSE)) 
		{
			
			while ((ReadFile(hPipe1, buffer1, sizeof(buffer1) - 1, &dwRead1, NULL) != FALSE))
			{
				buffer1[dwRead1] = '\0';				
				string ac = (char*)& buffer1[0];
				string ac2 = {ac[0],ac[1]};
				val1 = stoi(ac2);
			}
			
		}
		
		DisconnectNamedPipe(hPipe1);	
			
		if (val1>val2)
		{
			--car1X;
			coord1 = { .X = car1X,.Y = car1Y };
			SetConsoleCursorPosition(hOutputConsole, coord1);
			cout << " ";

			++car1X;
			coord1 = { .X = car1X,.Y = car1Y };
			SetConsoleCursorPosition(hOutputConsole, coord1);
			
			cout << SetColor(ConsoleColor::Green);
			WriteConsoleW(hOutputConsole, u"█", 1, nullptr, nullptr);

			SetConsoleCursorPosition(hOutputConsole, coordAnuncioGanador);
			cout << SetColor(ConsoleColor::Green) << "GANA CARRO1!!!";

			--car2X;
			coord2 = { .X = car2X,.Y = car2Y };
			SetConsoleCursorPosition(hOutputConsole, coord2);
			cout << " ";

			++car2X;
			coord2 = { .X = car2X,.Y = car2Y };
			SetConsoleCursorPosition(hOutputConsole, coord2);

			cout << SetColor(ConsoleColor::Red);
			WriteConsoleW(hOutputConsole, u"█", 1, nullptr, nullptr);

			SetConsoleCursorPosition(hOutputConsole, coordAnuncioPerdedor);
			cout << SetColor(ConsoleColor::Red) << "PIERDE CARRO2!!!";

		}
		else
		{
			--car2X;
			coord2 = { .X = car2X,.Y = car2Y };
			SetConsoleCursorPosition(hOutputConsole, coord2);
			cout << " ";

			++car2X;
			coord2 = { .X = car2X,.Y = car2Y };
			SetConsoleCursorPosition(hOutputConsole, coord2);
			
			cout << SetColor(ConsoleColor::Green);
			WriteConsoleW(hOutputConsole, u"█", 1, nullptr, nullptr);
			SetConsoleCursorPosition(hOutputConsole, coordAnuncioGanador);
			cout << SetColor(ConsoleColor::Green) << "GANA CARRO2!!!";

			--car1X;
			coord1 = { .X = car1X,.Y = car1Y };
			SetConsoleCursorPosition(hOutputConsole, coord1);
			cout << " ";

			++car1X;
			coord1 = { .X = car1X,.Y = car1Y };
			SetConsoleCursorPosition(hOutputConsole, coord1);

			cout << SetColor(ConsoleColor::Red);
			WriteConsoleW(hOutputConsole, u"█", 1, nullptr, nullptr);
			SetConsoleCursorPosition(hOutputConsole, coordAnuncioPerdedor);
			cout << SetColor(ConsoleColor::Red) << "PIERDE CARRO1!!!";

		}
		++car1X;
		++car2X;

		++contador;

	}

	//cout << "contador = " << contador<<endl;
	return 0;
}