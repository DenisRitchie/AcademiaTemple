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
#include <conio.h>

#pragma comment(lib, "Winmm.lib")

using namespace std;

//FUNCION PARA CREAR NUMEROS ALEATORIOS:
int32_t GenerateRandomNumber(const int32_t min, const int32_t max)
{
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<> distribution(min, max);
  return distribution(generator);
}

//FUNCION PARA ESCRIBIR DATOS DE UN HANDLE
void WriteFiles(HANDLE createFile,char dwBufferWrite[1023],DWORD dwNoByteWrite)
{
    BOOL writeFile;

    writeFile = WriteFile(
        createFile,
        dwBufferWrite,
        sizeof(dwBufferWrite),
        &dwNoByteWrite,
        NULL
    );
}

//FUNCION PARA CREAR CONEXIONES ENTRE PROCESOS
HANDLE CreateMails(std::wstring nombreMail) 
{
    HANDLE createMail;
    std::wstring path = L"\\\\.\\mailslot\\" + nombreMail;
    
    createMail = CreateMailslot(
        path.c_str(),
        0,
        MAILSLOT_WAIT_FOREVER,
        NULL
    );
    return createMail;
}

//FUNCION PARA LEER INFORMACION PASADO DE UNA CONEXION MAILSLOT
auto ReadFiles(HANDLE hHandle,char obtenerDatos[1023],DWORD dwNoByteWrite) -> BOOL
{
    BOOL readFile;

    readFile = ReadFile(
        hHandle,
        obtenerDatos,
        sizeof(char[1023]),
        &dwNoByteWrite,
        NULL
    );
    return readFile;
}

//FUNCION PARA CREAR CREAR LA CONEXION Y PODER ESCIBIR O RECIBIR INFORMACION
auto CreateFiles(std::wstring nombreMail) -> HANDLE 
{
    HANDLE createFile = GetStdHandle(STD_OUTPUT_HANDLE);
    std::wstring path = L"\\\\.\\mailslot\\" + nombreMail;
    
    createFile = CreateFile(
        path.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    return createFile;
}

//FUNCION PARA CREAR UN AUTO:
auto CrearAuto(HANDLE hOutputConsole,
    int32_t obtenerColorCarro,
    COORD coord, 
    COORD coordLine, 
    COORD coordLine2) -> void
{
    std::cout << "\n====================" << std::endl;
    std::cout << "| Velocidad: " << coord.X << "Km/h|" << std::endl;
    std::cout << "====================\n" << std::endl;

    SetConsoleCursorPosition(hOutputConsole, coordLine);
    SetConsoleTextAttribute(hOutputConsole, 7);
    WriteConsole(hOutputConsole, u"\n=======================================================================================================",
        100, nullptr, nullptr);

    SetConsoleTextAttribute(hOutputConsole, obtenerColorCarro);
    SetConsoleCursorPosition(hOutputConsole, coord);
    WriteConsoleW(hOutputConsole, u"    ____", 12, nullptr, nullptr);
    SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 1 });
    WriteConsoleW(hOutputConsole, u" __/  |_|_", 12, nullptr, nullptr);
    SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 2 });
    WriteConsoleW(hOutputConsole, u"|  _ CAR _`-.", 20, nullptr, nullptr);
    SetConsoleCursorPosition(hOutputConsole, { coord.X, coord.Y + 3 });
    WriteConsoleW(hOutputConsole, u"'-(_)---(_)--'", 15, nullptr, nullptr);

    SetConsoleTextAttribute(hOutputConsole, 7);
    SetConsoleCursorPosition(hOutputConsole, coordLine2);
    WriteConsole(hOutputConsole, u"=======================================================================================================\n",
        100, nullptr, nullptr);
}

//FUNCION PRINCIPAL
int32_t main()
{
    setlocale(LC_ALL, ".utf8");
  /*
    //PlaySoundW(L"transi.wav", NULL, SND_FILENAME);
  ╔═════════╗
  ║         ║
  ║         ║
  ║         ║
  ║         ║
  ╚═════════╝
  */

  int32_t indice = 0;
  COORD coord1 = { .X = 0, .Y = 6 };
  COORD coord2 = { .X = 0, .Y = 16 };

  COORD coordLine1 = { .X = 0, .Y = 3 };
  COORD coordLine2 = { .X = 0, .Y = 10 };
  COORD coordLine3 = { .X = 0, .Y = 13 };
  COORD coordLine4 = { .X = 0, .Y = 20 };

  HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  BOOL writeFile = TRUE;
  BOOL writeFile2 = TRUE;

  HANDLE infoCliente = GetStdHandle(STD_OUTPUT_HANDLE);
  BOOL leerInfo = TRUE;
  char obtenerColorCarro[1023];

  HANDLE createFile = GetStdHandle(STD_OUTPUT_HANDLE);
  HANDLE createFile2 = GetStdHandle(STD_OUTPUT_HANDLE);

  char dwBufferWrite[1023];
  char dwBufferWrite2[1023];

  DWORD dwNoByteWrite = 0;
  DWORD dwBufferWriteSize = sizeof(dwBufferWrite);
  
  infoCliente = CreateMails(L"INFOCLIENTE");
  leerInfo = ReadFiles(infoCliente, obtenerColorCarro, 0);
  
  while ( indice < 42 )
  { 
      system("cls");
      
      createFile = CreateFiles(L"MYMAILSERVER");
      createFile2 = CreateFiles(L"MYMAILSERVER2");
      
      //DESCOMENTAR PARA MOVERSE CON LA TECLA: ->
    /*  if(_kbhit())
      {
        switch(_getch())
        {
        case 77:
            coord.X += GenerateRandomNumber(1,2);
            break;
        }
      }
      CrearAuto(hOutputConsole, int32_t(*obtenerColorCarro), coord, coordLine, coordLine2);*/

      //MOVIMIENTO AUTOMATICO
      CrearAuto(hOutputConsole, int32_t(*obtenerColorCarro), coord1, coordLine1, coordLine2); 
      coord1.X += GenerateRandomNumber(1, 3);

      CrearAuto(hOutputConsole, 7, coord2, coordLine3, coordLine4);
      coord2.X += GenerateRandomNumber(1, 3);

    ++indice;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    *dwBufferWrite = static_cast<char>(coord1.X);
    *dwBufferWrite2 = static_cast<char>(coord2.X);

    WriteFiles(createFile, dwBufferWrite, dwNoByteWrite);
    WriteFiles(createFile2, dwBufferWrite2, dwNoByteWrite);
  }

  std::cin.get();
  
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
