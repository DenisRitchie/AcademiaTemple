#pragma once
#include <iostream>
#include <chrono>
#include <Windows.h>
#include <string>

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

        std::cout
            << SetColor(ConsoleColor::Yellow) << duration
            << SetColor(ConsoleColor::Green) << " (" << ms << "ms)\n"
            << SetColor(ConsoleColor::Gray);
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
};

struct StructValue
{
    int32_t Value;
    bool operator==(const StructValue&) const = default;
    auto operator<=>(const StructValue&) const = default;
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