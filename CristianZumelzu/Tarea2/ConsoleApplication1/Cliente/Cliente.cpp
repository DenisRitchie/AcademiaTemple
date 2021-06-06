// Cliente.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MailslotClient.h"
#include "iostream"
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

//Función para leer en utf-16
std::u16string ReadLineInUtf16()
{
  std::u16string result;
  char16_t character;
  DWORD number_of_chars_read;
  HANDLE InputHandle = GetStdHandle(STD_INPUT_HANDLE);
  bool not_is_newline = true;

  do {
    ReadConsoleW(InputHandle, &character, 1, &number_of_chars_read, nullptr);

    if (std::char_traits<char16_t>::eq(character, u'\r'))
    {
      ReadConsoleW(InputHandle, &character, 1, &number_of_chars_read, nullptr);

      if (std::char_traits<char16_t>::eq(character, u'\n'))
        not_is_newline = false;
    }

    if (not_is_newline)
      result.push_back(character);

  } while (not_is_newline);

  return std::move(result);
}

//funcion para generar números random
int32_t GenerateRandomNumber(const int32_t min, const int32_t max)
{
    std::random_device device;  //Se utilizrar para genera números aleatorios
    std::mt19937 generator(device());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}

int main()
{
  Win32::Icp::Mailslot::MailslotClient client{ u"EjemploComunicacionProcesos" };

  int32_t indices = 0;
  int32_t win;
  COORD coord{ .X = 10, .Y = 10 };
  

	while (true)
	{
    std::u16string mensaje = ReadLineInUtf16();

    if (mensaje.empty())
      break;

     client.Write(mensaje);

    {
         std::wstringstream salida;
         HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
         //salida << "Coord:\n" << coord.X++ << "\n" << coord.Y++ << "\n";
         
         //se mueve el auto
         while (indices < 50)
         {
             system("cls");
             SetConsoleCursorPosition(hOutputConsole, coord);
             salida << WriteConsoleW(hOutputConsole, u"╔══╦═╗", 7, nullptr, nullptr);
             SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 1 });
             salida << WriteConsoleW(hOutputConsole, u"║  ║ ║", 7, nullptr, nullptr);
             SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 2 });
             salida << WriteConsoleW(hOutputConsole, u"╠══╬═╩════╗", 12, nullptr, nullptr);
             SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 3 });
             salida << WriteConsoleW(hOutputConsole, u"╚══╩══════╝", 12, nullptr, nullptr);
             SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 4 });
             salida << WriteConsoleW(hOutputConsole, u"  O    O   ", 12, nullptr, nullptr);

             auto str = salida.str();
             client.Write(std::u16string{ str.cbegin(), str.cend() });
             ++indices;
             //++coord.X;
             coord.X += GenerateRandomNumber(1, 3);// moverse de 1 a 3 pasos de forma aleatoria

             //pausa
             std::this_thread::sleep_for(std::chrono::milliseconds(500));
             win = coord.X;
             salida << win;
         }
    }
	}
	return 0;
}