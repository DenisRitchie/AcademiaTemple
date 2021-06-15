// Cliente.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MailslotClient.h"
#pragma comment(lib, "Winmm.lib")

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

//FUNCION PARA LEER INFORMACION PASADO DE UNA CONEXION MAILSLOT
auto ReadFiles(HANDLE hHandle, char obtenerDatos[1023], DWORD dwNoByteWrite) -> BOOL
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

//FUNCION PARA ESCRIBIR DATOS DE UN HANDLE
void WriteFiles(HANDLE createFile, char dwBufferWrite[1023], DWORD dwNoByteWrite)
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

int main()
{
    setlocale(LC_ALL,".utf8");

    std::string win = 
        #include "Debug/win.txt"
        ;
    std::string over =
        #include "Debug/over.txt"
        ;

    Win32::Icp::Mailslot::MailslotClient client{ u"EjemploComunicacionProcesos" };

    HANDLE hOutupuConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    HANDLE mailS = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE mailS2 = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE pasarInfoCliente = GetStdHandle(STD_OUTPUT_HANDLE);

    BOOL writeColor;

    char dwBufferRead[1023];
    char dwBufferRead2[1023];
    char escribirColor[1023];

    DWORD dwBufferReadSize = sizeof(dwBufferRead);
    DWORD dwNoByteRead = 0;

    mailS = CreateMails(L"MYMAILSERVER");

    mailS2 = CreateMails(L"MYMAILSERVER2");

    pasarInfoCliente = CreateFiles(L"INFOCLIENTE");

    std::string afterExit;
    std::wstringstream salida;
    
    COORD coord{ .X = 10, .Y = 10 };
    COORD coord2{ .X = 10, .Y = 10 };

    std::string voto;
    std::int32_t colorCarrito;

    SetConsoleTextAttribute(hOutupuConsole, 4);
    std::cout << "IMPORTANTE\nPara poder Avanzar su carrito presione la flechita -> " << std::endl;

    SetConsoleTextAttribute(hOutupuConsole, 7);
    std::cout << "==================================================\n";
    std::cout << "\tSeleccione el color de su carrito\n";
    std::cout << "==================================================\n";
    std::cout << "Colores: \n\
        \n1:Azul\
        \n2:Verde\
        \n3:AguaMarina\
        \n4:Rojo\
        \n5:Purpura\
        \n6:Amarillo\
        \n7:Blanco\
        \n8:Gris\
        \n9:Azul Claro\n-> ";
    
    std::cin >> colorCarrito;
    if(colorCarrito > 0 && colorCarrito <10)
    {
        std::cout << "Seleccionado Correctamente\n" << std::endl;
        std::cout << "COMENZANDO CARRERA\n" << std::endl;
        std::cout << "Resumen Carrera\n" << std::endl;

        *escribirColor = char(colorCarrito);
        int32_t ventaja = 0;

        WriteFiles(pasarInfoCliente,escribirColor,dwNoByteRead);

        while (true)
        {
            /* if (mailS ==, INVALID_HANDLE_VALUE)
             {
                 std::cout << "Error al crear el mail" << std::endl;
             }
             else
             {
                 std::cout << "Mail creado correctamente" << std::endl;

             }*/

            ReadFiles(mailS, dwBufferRead, dwNoByteRead);
            ReadFiles(mailS2, dwBufferRead2, dwNoByteRead);
            
            coord.X = int32_t(*dwBufferRead);
            coord2.X = int32_t(*dwBufferRead2);

            /*if (!readFile)
            {
                std::cout << "Error al leer el contenido" << std::endl;
            }
            else
            {
                std::cout << "Leido correctamente: " << coord.X << std::endl;
            }*/
            if (coord.X > coord2.X)
            {
                salida << "Tu carro va ganando\n" << std::endl;
                auto str = salida.str();
                client.Write(std::u16string{ str.cbegin(),str.cend() });
                if (ventaja == 3)
                {
                    std::cout << "Tu Carro tiene una ventaja de: " << ventaja << std::endl;
                    PlaySound(L"C:\\Users\\Jesus\\Desktop\\Curso c++\\ConsoleApplication1\\ConsoleApplication1\\carro.wav", NULL, SND_ASYNC);
                    ventaja = 0;
                }
            }
            else
            {
                salida << "El Carro Rival va ganando\n" << std::endl;
                auto str = salida.str();
                client.Write(std::u16string{ str.cbegin(),str.cend() });
                if (ventaja == 3)
                {
                    std::cout << "El Carro rival tiene una ventaja de: " << ventaja << std::endl;
                    ventaja = 0;
                    PlaySound(L"C:\\Users\\Jesus\\Desktop\\Curso c++\\ConsoleApplication1\\ConsoleApplication1\\carroRival.wav", NULL, SND_ASYNC);
                }
            }
            ventaja++;
            if (coord.X >= 80 )
            {
                system("cls");
                for (int32_t i = 0; i < win.size(); ++i)
                {
                    std::cout << win[i];
                }
                PlaySound(L"C:\\Users\\Jesus\\Desktop\\Curso c++\\ConsoleApplication1\\ConsoleApplication1\\ganaste.wav", NULL, SND_ASYNC);
                std::cin >> afterExit;
                break;
            }
            else if (coord2.X >= 80 )
            {
                system("cls");
                for (int32_t i = 0; i < over.size(); ++i)
                {
                    std::cout << over[i];
                }
                PlaySound(L"C:\\Users\\Jesus\\Desktop\\Curso c++\\ConsoleApplication1\\ConsoleApplication1\\gameover.wav", NULL, SND_ASYNC);
                std::cin >> afterExit;

                break;
            }
            //std::u16string mensaje = ReadLineInUtf16();

          /*  if (mensaje.empty())
              break;

            {
              std::wstringstream salida;
              salida << "Coord:\n" << coord.X++ << "\n" << coord.Y++ << "\n";
              auto str = salida.str();

              client.Write(std::u16string{ str.cbegin(), str.cend() });
            }*/

        }
    }
    else if(std::to_string(colorCarrito).length() > 1)
    {
        while (true) 
        {
            int32_t salir = 0;
            std::cout << "Ingreso muchos caracteres" << std::endl;
            std::cout << "Ingrese 0:Para Salir" << std::endl;
            if (salir == 0)
            {
                break;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        while (true)
        {
            int32_t salir;
            std::cout << "Ingreso un numero o caracter no valido" << std::endl;
            std::cout << "Ingrese 0:Para Salir" << std::endl;
            std::cin >> salir;
            if(salir==0)
            {
                break;
            }
            else
            {
                break;
            }
        }
    }
    
	return 0;
}