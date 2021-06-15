#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>

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

namespace Implementation
{
	struct ConsoleColorImpl
	{
		ConsoleColor Color;
	};
}

constexpr WORD ForegroundMask = 0xf;
constexpr WORD BackgroundMask = 0xf0;


constexpr WORD ConsoleColorToColorAttribute(ConsoleColor, bool) noexcept;
constexpr ConsoleColor ColorAttributeToConsoleColor(WORD) noexcept;
void SetForegroundColor(const ConsoleColor) noexcept;
inline Implementation::ConsoleColorImpl SetColor(ConsoleColor) noexcept;
inline ::std::ostream& operator<<(::std::ostream&, const Implementation::ConsoleColorImpl&) noexcept;
bool search_element(std::vector<int32_t>, int32_t&) noexcept;
void app() noexcept;
std::string ascii_art() noexcept;
void print_ascii_art_color(std::string&, std::vector<int32_t>&)  noexcept;

int32_t main()
{
	setlocale(LC_ALL, ".utf8");
	app();
	return EXIT_SUCCESS;
}

void app() noexcept
{
	std::vector<int32_t> _mario_values{};
	std::string _mario = ascii_art();


	for (auto& _value : _mario)
	{
		int32_t _target = static_cast<int32_t>(_value);
		if (!search_element(_mario_values, _target))
		{
			_mario_values.push_back(_target);
		}
	}
	std::sort(_mario_values.begin(), _mario_values.end());

	/*
	for (auto& i : _mario_values)
	{
		std::cout << i << std::endl;
	}
	*/
	print_ascii_art_color(_mario, _mario_values);
}

std::string ascii_art() noexcept
{
	return
#include "Mario.txt"
		;
}
bool search_element(std::vector<int32_t> _elements, int32_t& _target) noexcept
{
	std::sort(_elements.begin(), _elements.end());
	return std::binary_search(_elements.begin(), _elements.end(), _target);
}

void print_ascii_art_color(std::string& _art, std::vector<int32_t>& _art_values) noexcept
{
	for (const auto& _value : _art)
	{
		if (_value == _art_values[2])
		{
			std::cout << SetColor(ConsoleColor::Black) << _value;
		}
		else if (_value == _art_values[5])
		{
			std::cout << SetColor(ConsoleColor::DarkYellow) << _value;
		}
		else if (_value == _art_values[6])
		{
			std::cout << SetColor(ConsoleColor::DarkBlue) << _value;
		}
		else if (_value == _art_values[7])
		{
			std::cout << SetColor(ConsoleColor::DarkRed) << _value;
		}
		else if (_value == _art_values[12])
		{
			std::cout << SetColor(ConsoleColor::White) << _value;
		}
		else
		{
			std::cout << SetColor(ConsoleColor::Black) << _value;
		}
	}
}


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

inline Implementation::ConsoleColorImpl SetColor(ConsoleColor color) noexcept
{
	return { color };
}

inline ::std::ostream& operator<<(::std::ostream& os, const Implementation::ConsoleColorImpl& color_impl) noexcept
{
	return SetForegroundColor(color_impl.Color), os;
}
