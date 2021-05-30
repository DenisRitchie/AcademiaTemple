#include "MailslotClient.h"
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
#include <sstream>


//Aqui definimos las constantes y los sobrenombres para poder manejar las resoluciones (al menos en mi computadora), de mejor manera.

using MailSlotCliente = Win32::Icp::Mailslot::MailslotClient;
#define ImprimirValores() std::cout << "ADVERTENCIA: el codigo del carrito FALLARA si se cambia de completo a minimizado, por favor, solo usar un modo en cada instancia de la aplicacion\n";\
                          std::cout << "Asimismo, es necesario insertar la opcion primero en el servidor y luego al cliente, ambos la misma opcion\n"; \
                          std::wcout << L"Inserte si desea resolucion de la carrera en ventana completa o reducida: ";               
#define MAX_DIST_PANTALLA_MINIMIZADA 100
#define MAX_DIST_PANTALLA_COMPLETA 180

int32_t GenerateRandomNumber(const int32_t min, const int32_t max) noexcept
{
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<> distribution(min, max);
  return distribution(generator);
}


void ImprimirYCorrer(COORD& coord1,COORD& coord2, HANDLE& hOutputConsole, MailSlotCliente& client, uint16_t& Resolucion) noexcept
{
    size_t i = 0, Max_Dist = 0;
    if (Resolucion)
    {
        Max_Dist = Resolucion;
    }
    else
    {
        std::cerr << "Error al obtener maxima resolucion\n";
        return;
    }

    while (i <= Max_Dist)
    {
        system("cls");
  
        SetConsoleCursorPosition(hOutputConsole, coord1);
        WriteConsoleW(hOutputConsole, u"   ▄█▀▀█▀▀█▄", 12, nullptr, nullptr);
        SetConsoleCursorPosition(hOutputConsole, { coord1.X, coord1.Y + 1 });
        WriteConsoleW(hOutputConsole, u"███████████████", 20, nullptr, nullptr);
        SetConsoleCursorPosition(hOutputConsole, { coord1.X, coord1.Y + 2 });
        WriteConsoleW(hOutputConsole, u" ▀▀0▀▀▀▀▀▀0▀▀▀", 20, nullptr, nullptr);

        SetConsoleCursorPosition(hOutputConsole, coord2);
        WriteConsoleW(hOutputConsole, u"   ▄█▀▀█▀▀█▄", 12, nullptr, nullptr);
        SetConsoleCursorPosition(hOutputConsole, { coord2.X, coord2.Y + 1 });
        WriteConsoleW(hOutputConsole, u"███████████████", 20, nullptr, nullptr);
        SetConsoleCursorPosition(hOutputConsole, { coord2.X, coord2.Y + 2 });
        WriteConsoleW(hOutputConsole, u" ▀▀0▀▀▀▀▀▀0▀▀▀", 20, nullptr, nullptr);
        
        {
            coord1.X += GenerateRandomNumber(1, 3);
            coord2.X += GenerateRandomNumber(1, 3);
            //Si el valor es mayor o igual 
            if ((coord1.X >= Max_Dist) || (coord2.X >= Max_Dist))
            {
                std::wstringstream salida;
                salida << coord1.X++ << "\n" << coord1.Y << "\n" << coord2.X++ << "\n" << coord2.Y << "\n";
                auto str = salida.str();
                client.Write(std::u16string{ str.cbegin(), str.cend() });
                system("pause");
            }
            std::wstringstream salida;
            salida << coord1.X++ << "\n" << coord1.Y <<"\n" << coord2.X++ << "\n" << coord2.Y << "\n";
            auto str = salida.str();
            client.Write(std::u16string{ str.cbegin(), str.cend()});
        }

        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

auto IngreseResolucionConsola() noexcept -> int16_t 
{
    uint16_t Opcion_Pantalla = 0;
    std::string Opcion{ 0 };
    ImprimirValores()
    std::cin >> Opcion;

    if (!_stricmp(Opcion.c_str(),"completa"))
    {
        Opcion_Pantalla = MAX_DIST_PANTALLA_COMPLETA;
    }
    else if (!_stricmp(Opcion.c_str(), "minimizada"))
    {
        Opcion_Pantalla = MAX_DIST_PANTALLA_MINIMIZADA;
    }
    else
    {
        std::cerr << "uso: <opcion: Minimizada, minimizada, Completa, completa>";
    }

    return Opcion_Pantalla;
}


int32_t main(void)
{
      SetConsoleTitle(L"Carros!");
      HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      MailSlotCliente Cliente{ u"EjemploComunicacionProcesos" };
      COORD coordCarro1{ .X = 0, .Y = 10};
      COORD coordCarro2{ .X = 0, .Y = 20 };

      //Implementar codigo si Resolucion Maxima Pantalla Completa o pantalla reducida
      uint16_t Resolucion = IngreseResolucionConsola();

      //Funcion que se encarga de enviar los datos y imprimir los carritos
      ImprimirYCorrer(coordCarro1, coordCarro2, hOutputConsole, Cliente, Resolucion);
      return 0;
  }



