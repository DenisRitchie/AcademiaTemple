/*ARITMETICA DE PUNTEROS*/

#include <iostream>
#include <string_view>
#include<string>
#include <chrono>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;



void CreateTableWords(char ****table, const int32_t filas, const int32_t columnas, const int32_t word_size) noexcept
{
	*table = new (std::nothrow)char **[filas];
	//int x = 0;
	//table[x] = new char** [filas];
	for (int32_t i = 0; i < filas; ++i)
	{
		*((*table)+i) = new char *[columnas];
		//table[x][i] = new char* [columnas];
		for (int32_t c=0;c!=columnas;++c)
		{
			*(*((*table)+i)+c) = new char[word_size];
			//table[x][i][c] = new char[word_size];
		}
	} 
}
void DeleteTableWords(char**** table, const int32_t filas, const int32_t columnas)
{
	
	for (size_t i =0; i <filas; ++i)
	{
		for (size_t j = 0; j < columnas; ++j)
		{
			//delete[] table[0][i][j];
			delete[] *(*((*table) + i)+j);
		}

		//delete[] table[0][i];
		delete[] *((*table) + i);
	}
	//delete[] table[0];
	delete[] * table;
	cout << "tabla eliminada" << endl<<endl;
}
int32_t main()
{

	HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, ".utf8");
	char ***tabla;
	 int32_t filas;
	 int32_t columnas;
	const int32_t word_size{20};
	cout << "ingrese el numero de filas para la tabla: ";
	cin >> filas;
	cout << "ingrese el numero de columnas para la tabla: ";
	cin >> columnas;
	string texto2;
	cout << "ingrese la palabra que se mostrara en la tabla: ";
	cin >> texto2;
	int32_t tamanioTexto = sizeof(texto2);
	char* texto = const_cast<char*>(texto2.c_str());
	CreateTableWords(&tabla, filas, columnas, word_size);
	
	for (size_t i = 0; i < filas; i++)
	{
		for (size_t j = 0; j < columnas; j++)
		{
			std::char_traits<char>::copy(tabla[i][j],texto,tamanioTexto-12);
		}
		cout << endl;
	}

	COORD coordFila= { .X = 5,.Y = 5 };
	COORD coordFila2 = { .X = 5,.Y = 5 };
	SHORT var = 5;
	SHORT var2 = 5;
	
	SetConsoleCursorPosition(hOutputConsole, coordFila);
	for (size_t i = 0; i < filas; i++)
	{
		var = 5;
		coordFila2 = { .X = var ,.Y = var2 };
		SetConsoleCursorPosition(hOutputConsole, coordFila2);
		for (size_t j = 0; j< columnas; j++)
		{
			cout << "----------"<<endl;
			SetConsoleCursorPosition(hOutputConsole, { coordFila2.X, coordFila2.Y + 1 });
			cout << "+ " << tabla[i][j] << " +"<<endl;
			SetConsoleCursorPosition(hOutputConsole, { coordFila2.X, coordFila2.Y + 2 });
			cout << "----------" << endl;
			var = var + tamanioTexto-12;
			coordFila2 = { .X = var ,.Y = var2 };
			SetConsoleCursorPosition(hOutputConsole, coordFila2);	
		}
		var2=var2+2;

	}
	var2=20;
	var = 0;
	coordFila2 = { .X = var ,.Y = var2 };
	SetConsoleCursorPosition(hOutputConsole, coordFila2);
	cout << endl;
	cout << "Presione la tecla Y para eliminar la tabla: ";
	char tecla;
	cin >> tecla;
	bool bandera = true;
	while (bandera == true)
	{
		if (tecla == 'Y' || tecla == 'y')
		{
			DeleteTableWords(&tabla, filas, columnas);
			bandera = false;
		}
		else
		{
			cout << "presione la tecla Y para eliminar la tabla: ";
			cin >> tecla;
		}
	}
		return 0;
}


