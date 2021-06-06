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
//#include <sstream>

//Para que funcione PlaysoundW() se debe llamar 
#pragma comment(lib, "Winmm.lib")

using namespace std;

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
  //PlaySoundW(L"Recording.wav", NULL, SND_FILENAME);

  /*
  ╔══╦═╗
  ║  ║ ║
  ╠══╬═╩════╗
  ╚══╩══════╝
    O     O
  */

  int32_t indice = 0;
  COORD coord = { .X = 10, .Y = 10 };
  // obtener el manejador de la consola
  HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  //se mueve el cuadro
  while ( indice < 70 )
  {
    system("cls");

    SetConsoleCursorPosition(hOutputConsole, coord);
    WriteConsoleW(hOutputConsole, u"╔══╦═╗", 7, nullptr, nullptr);
    SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 1 });
    WriteConsoleW(hOutputConsole, u"║  ║ ║", 7, nullptr, nullptr);
    SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 2 });
    WriteConsoleW(hOutputConsole, u"╠══╬═╩════╗", 12, nullptr, nullptr);
    SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 3 });
    WriteConsoleW(hOutputConsole, u"╚══╩══════╝", 12, nullptr, nullptr);
    SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 4 });
    WriteConsoleW(hOutputConsole, u"  O    O   ", 12, nullptr, nullptr);
    /*SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 5 });
    WriteConsoleW(hOutputConsole, u"╚═════════╝", 12, nullptr, nullptr);*/

    ++indice;
    //++coord.X;
    coord.X += GenerateRandomNumber(1, 3);// moverse de 1 a 3 pasos de forma aleatoria
    
    //pausa
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  return 0;
}

/*
3 Programas
----------------------
1 programas -> 1 carrito (dibujar, mover aleatoriamente)
1 programas -> 1 carrito (dibujar, movel aleatoriamente)
----------------------
1 programa -> Comentar como va la carrera
*/
