// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MailslotServer.h"
#include <thread>
#include <chrono>
#include <iostream>
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
//#include <locale>

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

void ReadEvent(
  Win32::Icp::Mailslot::MailslotServer&,
  const Win32::Icp::Mailslot::MailslotServer::MailslotServerReadEventArgs& info)
{
  // stdout imprimir por pantalla
  HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  WriteConsoleW(hOutputConsole,
    info.Message.data(),
    info.Message.length(),
    nullptr,
    nullptr);
  std::wcout.put(u'\n');

  /*if (info.Message.starts_with(u"Coord:"))
  {
    COORD coord;
    std::wstringstream entrada{ (LPCWSTR)info.Message.data(), std::ios::in };

    std::wstring dummy;
    std::getline(entrada, dummy);
    entrada >> coord.X >> coord.Y;
    std::wcout << L"Las coordenadas son: (" << coord.X << L", " << coord.Y << L")\n";
  }*/
}

//funcion para generar números random
int32_t GenerateRandomNumber(const int32_t min, const int32_t max)
{
    std::random_device device;  //Se utilizrar para genera números aleatorios
    std::mt19937 generator(device());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}


int32_t main()
{
  Win32::Icp::Mailslot::MailslotServer server{ u"EjemploComunicacionProcesos" };
  //server.EnableLogs = true;
  int32_t indice = 0;
  int32_t lost = 0;
  int32_t winn = 0;

  COORD coord{ .X = 10, .Y = 10 };
  server.MailslotServerRead += ReadEvent;

  while (true)
  {
    server.Read();
    std::wstringstream entrada;
    HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (indice < 50)
    {
        system("cls");
        SetConsoleCursorPosition(hOutputConsole, coord);
        entrada << WriteConsoleW(hOutputConsole, u"╔══╦═╗", 7, nullptr, nullptr);
        SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 1 });
        entrada << WriteConsoleW(hOutputConsole, u"║  ║ ║", 7, nullptr, nullptr);
        SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 2 });
        entrada << WriteConsoleW(hOutputConsole, u"╠══╬═╩════╗", 12, nullptr, nullptr);
        SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 3 });
        entrada << WriteConsoleW(hOutputConsole, u"╚══╩══════╝", 12, nullptr, nullptr);
        SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 4 });
        entrada << WriteConsoleW(hOutputConsole, u"  O    O   ", 12, nullptr, nullptr);

        auto str = entrada.str();
        //server.Read(std::u16string{ str.cbegin(), str.cend() });
        ++indice;
        //++coord.X;
        coord.X += GenerateRandomNumber(1, 3);// moverse de 1 a 3 pasos de forma aleatoria
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        lost = coord.X;
    }
  }


  return 0;
}
