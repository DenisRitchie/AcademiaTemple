#include<iostream>
#include<string>
#include<stdio.h>
#include <chrono>
#include <Windows.h>

namespace Win32::ConsoleApi 
{
    enum class ConsoleColor : WORD 
    {
        Black       = 0,
        DarkBlue    = 1,
        DarkGreen   = 2,
        DarkCyan    = 3,
        DarkRed     = 4,
        DarkMagenta = 5,
        DarkYellow  = 6,
        Gray        = 7,
        DarkGray    = 8,
        Blue        = 9,
        Green       = 10,
        Cyan        = 11,
        Red         = 12,
        Magenta     = 13,
        Yellow      = 14,
        White       = 15
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

int32_t ascii(char letra)
{
    int32_t valor = letra;
    
    return valor;
}


int32_t main(){

        using namespace Win32;

        setlocale(LC_ALL, ".utf8");

        std::string mario =  #include "Mario.txt";


            for( int32_t i = 0; i <=mario.size(); ++i )
                {
                    //std::cout<<mario[i];    

                    //std::cout << ascii(mario[i]) <<" ";

                    if(mario[i] == 95){
                             std::cout << SetColor(ConsoleColor::red)<<mario[i];
                     }
                     else if (mario[i] == -30 || mario[i] == -106|| mario[i] == -128 ){
                            std::cout << SetColor(ConsoleColor::White)<<mario[i];
                     }
                     else{
                            std::cout << SetColor(ConsoleColor::Blue)<<mario[i];   
                     }

                }    

}