#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <string_view>

#include<stdio.h>
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


std::string GetRosalinaFileContent()
{
	std::string rosalina;

	uintmax_t file_size = std::filesystem::file_size("Rosalina.txt");
	std::ifstream rosalina_file{ "Rosalina.txt" };

	rosalina.resize(file_size);
	rosalina_file.read(rosalina.data(), file_size);

	return std::move(rosalina);
}

int32_t main()
{
    using namespace Win32;
	std::string rosalina = GetRosalinaFileContent();
	
    //    std::cout << rosalina << std::endl;

    for (int32_t i = 0; i <= rosalina.size(); ++i)
    {
        

        //Pintando solo el cabello
		if (rosalina[i] == 35 && ((i<=1500 && i>=540) || (i<= 513 && i>=507) || (i>=1560 && i<=1592) || (i>=1595 && i<=1603)|| (i>=1641 && i<=1700 ) || (i>=1715 && i<=1780) 
            || (i>= 1800 && i<= 1860)|| (i>=1883 && i<=1920) || (i>=1930 && i<=1980) || (i>=1990 && i<=2200) || (i==1925) || (i==1924) ))
		{
            std::cout << SetColor(ConsoleColor::DarkYellow) << rosalina[i];
		}

        //Pintando la boca
        else if (rosalina[i] == 35 && (i<=1990 && i>=1985 ))
        {
            std::cout << SetColor(ConsoleColor::DarkMagenta) << rosalina[i];
        }
        //Pintando no sé
        else if (rosalina[i] == 38)
        {
            std::cout << SetColor(ConsoleColor::White) << rosalina[i];
        }
		//Pintando el vestido
        else if (rosalina[i] == 35 && (i>=2380 && i<=5000))
        {
            std::cout << SetColor(ConsoleColor::Cyan) << rosalina[i];
        }

        else 
        {
            std::cout << SetColor(ConsoleColor::White) << rosalina[i];
        }
	}

    
	return 0;

}