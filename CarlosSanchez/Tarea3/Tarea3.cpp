/*Pues quiero que hagas una funciono para crear una tabla de palabras dinamicamente al estilo lenguaje C
La firma de la función sería la siguiente:

void CreateTableWords( char **table, const int32 filas, const int32 columnas,  const int32 word_size );
void DeleteTableWords( char **table,  const int32 filas, const int32 columnas );

Esa sera la tarea #3 para todos.*/
#include <iostream>
#include<stdio.h>
#include<locale>
#include<string>

void marco(const int32_t t, const int32_t c)
{
    for (int32_t i = 0; i != c; ++i)
    {
        std::cout<< '+' << std::string(t, '-');
    }
    std::cout << "+\n";
}
void CreateTableWords(char**** table, const int32_t filas, const int32_t columnas, const int32_t word_size)
{
    *table = new char** [filas];
    int32_t f = 0, c = 0;

    for (f = 0; f != filas; ++f)
    {
        *(*table + f) = new char* [columnas];
        for (c = 0; c != columnas; ++c)
        {
            *(*(*table + f) + c) = new char[word_size];
            fflush(stdin);
            std::cout << "Introducir palabra: ";
            std::cin>>*(*(*table + f) + c);
        }
    }
    std::cout << "\nTabla de cadenas:\n\n";
    
    for (f = 0; f != filas; ++f)
    {
        marco(word_size, columnas);
        for (c = 0; c != columnas; ++c)
        {
            int32_t space = word_size - strlen(*(*(*table + f) + c));
            std::cout << "-" << *(*(*table + f) + c)<<std::string(space, ' ');
        }
        std::cout<< "-"<<std::endl;
    }
    marco(word_size, columnas);
}

void DeleteTableWords(char**** table, const int32_t filas, const int32_t columnas)
{
    for (size_t f = 0; f != filas; ++f)
    {
        for (size_t c = 0; c != filas; ++c)
        {
            delete[] *(*(*table + f) + c);
        }
        delete[] *(*table + f);
    }
    delete[]* table;
}

void verificar(int32_t& a)
{
    do{
        std::cin >> a;
        system("cls");
        if (a<0)
            std::cout << "Valor inválido\n\n";
    } while (a<0);
}

int32_t main()
{
    setlocale(LC_ALL, ".utf8");
    char*** cadenas = nullptr;
    int32_t size, nfilas, ncolumnas;

    std::cout << "Tamaño de cada palabra: ";
    verificar(size);
    std::cout << "Número de filas: ";
    verificar(nfilas);
    std::cout << "Número de columnas: ";
    verificar(ncolumnas);
    CreateTableWords(&cadenas, nfilas, ncolumnas, size);
    DeleteTableWords(&cadenas, nfilas, ncolumnas);

    return EXIT_SUCCESS;
}