#include <iostream>
#include <chrono>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>


namespace ConsoleApi
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
    using ConsoleApi::SetColor;
    using ConsoleApi::ConsoleColor;
    using ConsoleApi::operator<<;
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

        std::cout << SetColor(ConsoleColor::Yellow) << (char32_t*)&duration << SetColor(ConsoleColor::Green) << " (" << ms << "ms)\n" << SetColor(ConsoleColor::Gray);
        std::cout << SetColor(ConsoleColor::Yellow);
        std::cout << (char32_t*)&duration;
        std::cout << (char32_t*)&duration << SetColor(ConsoleColor::Green);

        std::cout << "hola" << "hola2" << "hola3";
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};

struct StructValue
{
    int32_t Value;
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

int32_t main()
{
    using namespace Win32;
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".utf8");

    std::cout << SetColor(ConsoleColor::Gray);
    std::string mario1 =
#include "Mario.txt"
        ;

    int32_t j = 0;
    int32_t longitud = mario1.length();

    while (j < longitud)
    {

        if (mario1[j] == -128 || mario1[j] == -106 || mario1[j] == -124 || mario1[j] == -30 || mario1[j] == -120 || mario1[j] == -116 || mario1[j] == -112 || mario1[j] == -109 || mario1[j] == -111 || mario1[j] == 110 || mario1[j] == 95)
        {
            if (mario1[j] == -128 || mario1[j] == -106 || mario1[j] == -124 || mario1[j] == -30 || mario1[j] == -120 || mario1[j] == -116 || mario1[j] == -112)
            {
                std::cout << SetColor(ConsoleColor::White) << mario1[j];
            }
            if (mario1[j] == -109)
            {
                std::cout << SetColor(ConsoleColor::Red) << mario1[j];
            }
            if (mario1[j] == -111 || mario1[j] == 110)
            {
                std::cout << SetColor(ConsoleColor::Yellow) << mario1[j];
            }
            if (mario1[j] == 95)
            {
                std::cout << SetColor(ConsoleColor::Black) << mario1[j];
            }

        }
        else
        {
            std::cout << SetColor(ConsoleColor::Blue) << mario1[j];
        }


        ++j;
    }

    return 0;
}