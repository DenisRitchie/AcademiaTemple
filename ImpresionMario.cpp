// ImpresionMario.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <chrono>
#include <Windows.h>

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
        struct ConsoleColorImpl {
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
int main()
{
    using namespace std;
    using namespace Win32;
	setlocale(LC_ALL, ".utf8");
	std::string mario =
			#include "Mario.txt"
			;
    //cout << SetColor(ConsoleColor::R+6ed) << mario;
	//std::cout << mario;
    //Codigo Unicode: 3 bytes.
    //Para los colores de adentro de la ropa de mario
    
    for (size_t i = 0; i < mario.size(); i++)
	{
        /*
        if(mario[i] == 95)
        {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        */
        // else if (mario[i] == -30 || mario[i] == -106 || mario[i] == -124)
        //{
         // -30 y -106  y -109 para ropa amarilla cout << SetColor(ConsoleColor::Yellow) << mario[i];
        //}
 
        if (mario[i] == -30 || mario[i] == -106 || mario[i] == -109)
        {
            cout << SetColor(ConsoleColor::Red) << mario[i];
        }
        // 4270: -30 4271: -106 4272: -110}
        else if (mario[i] == -30 || mario[i] == -106 || mario[i] == -110)
        {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        else if(mario[i] == -106 || mario[i] == -111 || mario[i] == -30)
        {
            cout << SetColor(ConsoleColor::Yellow) << mario[i];
        }
        else
        {
            cout << SetColor(ConsoleColor::White) << mario[i];
        }
    }
	return EXIT_SUCCESS;
}