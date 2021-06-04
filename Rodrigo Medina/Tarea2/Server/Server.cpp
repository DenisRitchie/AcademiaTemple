#include "MailslotServer.h"
#include <thread>
#include <chrono>
#include <locale>


#define ImprimirValores() std::cout << "ADVERTENCIA: el codigo del carrito FALLARA si se cambia de completo a minimizado, por favor, solo usar un modo en cada instancia de la aplicacion\n";\
                          std::cout << "Asimismo, es necesario insertar la opcion primero en el servidor y luego al cliente, ambos la misma opcion\n"; \
                          std::wcout << L"Inserte si desea resolucion de la carrera en ventana completa o reducida: ";
#define MAX_DIST_PANTALLA_MINIMIZADA 100
#define MAX_DIST_PANTALLA_COMPLETA 180

static uint16_t Opcion_Pantalla = 0;


void ReadEvent(
    Win32::Icp::Mailslot::MailslotServer&,
    const Win32::Icp::Mailslot::MailslotServer::MailslotServerReadEventArgs& info
)
{
    // stdout
    HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //uint16_t Opcion_Pantalla = 0;
    //std::wstringstream entradaInicial{ (LPCWSTR)info.Message.data(), std::ios::in };
    //entradaInicial >> Opcion_Pantalla;

    COORD coord1{ 0 }, coord2{ 0 }, coord3{ 0 };
    std::wstringstream entrada{ (LPCWSTR)info.Message.data(), std::ios::in };
    entrada >> coord1.X >> coord1.Y >> coord2.X >> coord2.Y;
    std::cout << "Coordenadas de carrito 1 = X: " << coord1.X << " Y: " << coord1.Y << "\n";
    std::cout << "Coordenadas de carrito 2 = X: " << coord2.X << " Y: " << coord2.Y << "\n";

    if (coord2.X < coord1.X)
    {
        std::wcout << L"El carrito 1 esta ganando al carrito 2!\n";
    }
    else if (coord2.X > coord1.X)
    {
        std::wcout << L"El carrito 2 esta ganando al carrito 2!\n";
    }
    else
    {
        std::wcout << L"Ambos carritos estan en la misma posicion\n";
    }

    if (coord1.X >= Opcion_Pantalla && coord2.X < Opcion_Pantalla)
    {
        std::wcout << L"El carrito 1 gano!\n";
        system("pause");
    }

    if (coord2.X >= Opcion_Pantalla && coord1.X < Opcion_Pantalla)
    {
        std::wcout << L"El carrito 2 gano!\n";
        system("pause");
    }

    if (coord1.X >= Opcion_Pantalla && coord2.X >= Opcion_Pantalla)
    {
        std::wcout << L"Empate\n";
    }
}

auto IngreseResolucionConsola() noexcept -> int16_t
{
    uint16_t Opcion_Pantalla = 0;
    std::string Opcion{ 0 };
    ImprimirValores()
    std::cin >> Opcion;

    if (!_stricmp(Opcion.c_str(), "completa"))
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
    Win32::Icp::Mailslot::MailslotServer server{ u"EjemploComunicacionProcesos" };
    //server.EnableLogs = true;

    server.MailslotServerRead += ReadEvent;
    Opcion_Pantalla = IngreseResolucionConsola();

    while (true)
    {
        server.Read();

        std::this_thread::sleep_for(std::chrono::milliseconds(1'000));
    }

    return 0;
}
