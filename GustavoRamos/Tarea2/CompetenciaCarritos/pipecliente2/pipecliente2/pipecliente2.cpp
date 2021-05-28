
#include <iostream>

#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <iomanip>
#include <ciso646>
#include <algorithm>
#include <array>
#include <tuple>
#include <string>
#include <string_view>
#include <iterator>
#include <utility>
#include <Windows.h>
#include <thread>
#include <random>
#include <sstream>
#include <string>
#include <cstring>
//#define BUFSIZE 512



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



using namespace std;


int32_t GenerateRandomNumber(const int32_t min, const int32_t max)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<> distribution(min, max);
	return distribution(generator);
}


int main(void)
{
	
	using namespace Win32;

	

	HANDLE hPipe, hPipeServer;
	DWORD dwWritten, dwReadServer;
	char buffServer[1024];
	string senial;

	hPipeServer = CreateNamedPipe(TEXT("\\\\.\\pipe\\PipeServer2"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	if ((ConnectNamedPipe(hPipeServer, NULL) != FALSE))
	{
	
		while ((ReadFile(hPipeServer, buffServer, sizeof(buffServer) - 1, &dwReadServer, NULL) != FALSE))
		{
			buffServer[dwReadServer] = '\0';
			string ac = (char*)& buffServer[0];
			senial = ac;
		

		}
	}
	DisconnectNamedPipe(hPipeServer);



	int32_t indice = 0;
	COORD coord = { .X = 10,.Y = 10 };
	COORD coordMeta = { .X = 130,.Y = 10 };

	HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << SetColor(ConsoleColor::Yellow);

	while (indice < 80)
	{
		system("cls");
		/*█
		   █
		  █
		   █
		  █
		   █*/
		SetConsoleCursorPosition(hOutputConsole, coordMeta);
		WriteConsoleW(hOutputConsole, u"█", 2, nullptr, nullptr);
		SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 1 });
		WriteConsoleW(hOutputConsole, u"█", 2, nullptr, nullptr);
		SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 2 });
		WriteConsoleW(hOutputConsole, u"█ ", 2, nullptr, nullptr);
		SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 3 });
		WriteConsoleW(hOutputConsole, u"█", 2, nullptr, nullptr);
		SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 4 });
		WriteConsoleW(hOutputConsole, u"█ ", 2, nullptr, nullptr);
		SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 5 });
		WriteConsoleW(hOutputConsole, u"█", 2, nullptr, nullptr);

		/*

		   ▄█▀▀█▀▀█▄     16 caracteres
         ███████████████
          ▀▀0▀▀▀▀▀▀0▀▀▀ 


		*/
		SetConsoleCursorPosition(hOutputConsole, coord);
		WriteConsoleW(hOutputConsole, u"  ▄█▀▀█▀▀█▄    ", 16, nullptr, nullptr);
		SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 1 });
		WriteConsoleW(hOutputConsole, u"███████████████", 16, nullptr, nullptr);
		SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 2 });
		WriteConsoleW(hOutputConsole, u"  ▀▀0▀▀▀▀▀▀0▀▀▀ ", 16, nullptr, nullptr);

		++indice;
		if (coord.X >= 105)
		{
			system("cls");
			WriteConsoleW(hOutputConsole, u"█", 2, nullptr, nullptr);
			SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 1 });
			WriteConsoleW(hOutputConsole, u"█", 2, nullptr, nullptr);
			SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 2 });
			WriteConsoleW(hOutputConsole, u"█ ", 2, nullptr, nullptr);
			SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 3 });
			WriteConsoleW(hOutputConsole, u"█", 2, nullptr, nullptr);
			SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 4 });
			WriteConsoleW(hOutputConsole, u"█ ", 2, nullptr, nullptr);
			SetConsoleCursorPosition(hOutputConsole, { coordMeta.X, coordMeta.Y + 5 });
			WriteConsoleW(hOutputConsole, u"█", 2, nullptr, nullptr);
			SetConsoleCursorPosition(hOutputConsole, { coordMeta.X + 5, coordMeta.Y + 1 });
			WriteConsoleW(hOutputConsole, u"LLEGO!!!", 8, nullptr, nullptr);
		
			indice = 80;
		}
		coord.X += GenerateRandomNumber(1, 3);

		int32_t a = coord.X;
		int32_t b = coord.Y;
		string coordenadas = to_string(a) + "," + to_string(b) + "\n";
		int32_t tamaniocoord = coordenadas.length();

		char* carro2 = const_cast<char*>(coordenadas.c_str());
		

		std::this_thread::sleep_for(std::chrono::milliseconds(600));

		hPipe = CreateFile(TEXT("\\\\.\\pipe\\Pipecarrito2"),
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		
		if (hPipe != INVALID_HANDLE_VALUE)
		{

			WriteFile(hPipe,
				carro2,
				tamaniocoord,
				&dwWritten,
				NULL);

			CloseHandle(hPipe);
		}
	}


	return (0);
}
/*
3 Programas
----------------------
1 programas -> 1 carrito (dibujar, mover aleatoriamente)
1 programas -> 1 carrito (dibujar, movel aleatoriamente)
----------------------
1 programa -> Comentar como va la carrera
*/
