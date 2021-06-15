
/*
    Program: Mario de colores
    
    Description: Programa para pintar textArt de Mario en sus colores reales.

    En la case 1 se imprimió a Mario por la pantalla, usando el #include "Mario.txt"
    La tarea consiste en imprimir el mismo Mario en la pantalla pero ya coloreado

    Código de ejemplo para mostrar texto coloreado
    Sólo funciona en Windows, Recuerdar activar el flag de C++20

    By: YGM
    Data: 28/04/2021
    Time: 21:10
    Visual Studio 2019 Enterprise
*/

#include "ColoresConsole.h"

int32_t ascii(char letra) {

    int32_t valorASCII = letra;

    return valorASCII;
}

int32_t main() {

    using namespace std;
    using namespace Win32;

    setlocale(LC_ALL, ".utf8");

    string mario =
        #include "Mario.txt"
        ;

    //  cout << mario << endl;

    /*  // Ciclo for para localizar los codigos de los caracteres especiales de Mario
    for (int i = 0; i < mario.size(); i++) {

        cout << ascii(mario[i]) << " ";
        cout << i << " ";
    }
    */

    for (int32_t i = 0; i < mario.size(); i++) {

        // Underscore
        if (mario[i] == 95) {
            cout << SetColor(ConsoleColor::White) << mario[i];
        }

        // Ojos Azules
        else if (i >= 2518 && i <= 2530) {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        else if (i >= 2677 && i <= 2682) {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        else if (i >= 2692 && i <= 2696) {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        else if (i >= 2838 && i <= 2843) {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        else if (i >= 2874 && i <= 2885) {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        else if (i >= 2999 && i <= 3001) {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        else if (i >= 3044 && i <= 3046) {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        else if (i >= 3207 && i <= 3209) {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }
        else if (i >= 3365 && i <= 3367) {
            cout << SetColor(ConsoleColor::Blue) << mario[i];
        }

        // Zapatos
        // Zapato derecho
        else if (i >= 7908 && i <= 7926) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 8077 && i <= 8115) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 8252 && i <= 8305) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 8436 && i <= 8495) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 8618 && i <= 8656) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 8669 && i <= 8689) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 8807 && i <= 8833) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 8873 && i <= 8881) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 8996 && i <= 9019) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9032 && i <= 9064) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9068 && i <= 9076) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9178 && i <= 9198) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9208 && i <= 9252) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9350 && i <= 9367) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9377 && i <= 9430) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9520 && i <= 9537) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9547 && i <= 9603) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9688 && i <= 9705) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9712 && i <= 9771) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9857 && i <= 9868) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 9875 && i <= 9934) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 10020 && i <= 10028) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 10050 && i <= 10091) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 10180 && i <= 10182) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 10192 && i <= 10206) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 10231 && i <= 10240) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 10338 && i <= 10376) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 10479 && i <= 10523) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 10615 && i <= 10650) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        // Zapato izquierdo
        else if (i >= 11177 && i <= 11179) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11252 && i <= 11263) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11327 && i <= 11347) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11399 && i <= 11431) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11460 && i <= 11516) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11545 && i <= 11601) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11631 && i <= 11684) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11717 && i <= 11719) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11717 && i <= 11770) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11804 && i <= 11851) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11889 && i <= 11930) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 11969 && i <= 12001) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }
        else if (i >= 12048 && i <= 12065) {
            cout << SetColor(ConsoleColor::DarkRed) << mario[i];
        }

        // Piel y Botones
        else if (mario[i] == -30 || mario[i] == -106 || mario[i] == -111) {
            cout << SetColor(ConsoleColor::DarkYellow) << mario[i];
        }

        // Pantalones
        else if (mario[i] == -30 || mario[i] == -106 || mario[i] == -110) {
            cout << SetColor(ConsoleColor::DarkBlue) << mario[i];
        }

        // Gorro y Playera
        else if (mario[i] == -30 || mario[i] == -106 || mario[i] == -109) {
            cout << SetColor(ConsoleColor::Red) << mario[i];
        }

        // Contorno
        else {
            cout << SetColor(ConsoleColor::Black) << mario[i];
        }
    }

    return 0;
}