#include <iostream>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include<ctime>
#include <random>
#include<stdio.h>
#include<stdlib.h>

using namespace std;



void retardo() {
	for (int i = 0; i < 2500; i++)
	{

		for (int k = 0; k < 11000; k++)
		{

		}
	};


}



void carTecho(int x, int y) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hcon, dwPos);


}

char opcion;
int a = 1;
int b = 1;

void carMedio(int x1, int y1) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x1;
	dwPos.Y = y1;

	SetConsoleCursorPosition(hcon, dwPos);



};

char opcion1;
int a1 = 0;
int b1 = 2;



void carRueda(int x2, int y2) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x2;
	dwPos.Y = y2;

	SetConsoleCursorPosition(hcon, dwPos);



};

char opcion2;
int a2 = 0;
int b2 = 3;





void carTecho2(int x, int y) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hcon, dwPos);


}

char opcion3;
int a4 = 1;
int b4 = 5;

void carMedio2(int x1, int y1) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x1;
	dwPos.Y = y1;

	SetConsoleCursorPosition(hcon, dwPos);



};

char opcion4;
int a5 = 0;
int b5 = 6;



void carRueda2(int x2, int y2) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x2;
	dwPos.Y = y2;

	SetConsoleCursorPosition(hcon, dwPos);



};

char opcion5;
int a6 = 0;
int b6 = 7;



int main() {


	int boton = 0;
	srand(time(NULL));


	cout << "\t Bienvenido a la carrera de Autos \n" << endl;
	cout << "\n1. Presione la tecla 1 para iniciar" << endl;
	cin >> boton;


	while (boton != 1) {

		cout << "\n1. Presione la tecla 1 para iniciar" << endl;
		cin >> boton;
	}

	int c = 0;
	int d = 0;


	for (int i = 0; i < 200; i++)
	{

		system("cls");

		cout << ("\033[0;31m");
		carTecho(a, b);
		cout << "_/\\______\\__ ";

		carMedio(a1, b1);
		cout << "/ ,-. -|-  ,-.`-.  ";


		carRueda(a2, b2);
		cout << "`( o )----( o )-'";

		cout << ("\033[0;0m");





		cout << ("\033[0;40;32m");
		carTecho2(a4, b4);
		cout << "_/\\______\\__ ";


		carMedio2(a5, b5);
		cout << "/ ,-. -|-  ,-.`-.  ";



		carRueda2(a6, b6);
		cout << "`( o )----( o )-'";

		cout << ("\033[0;0m");
		//opcion=getch();
		//opcion1=getch();
		//opcion2=getch();






		int mA = rand() / 100;
		int mb = rand() / 100;










		if (mA > mb)
		{

			c++;
			a++;
			a1++;
			a2++;

			retardo();

		};

		if (mb > mA)
		{
			d++;
			a4++;
			a5++;
			a6++;
			retardo();

		}

		if (c > d)
		{

			cout << ("\033[0;31m");
			cout << "\n" << endl;
			cout << "\nGanando  el Auto Rojo" << endl;
			cout << ("\033[0;0m");
			retardo();

		}
		else
		{
			cout << ("\033[0;40;32m");
			cout << "\n" << endl;
			cout << "\n" << endl;
			cout << "\nGanando el Auto Verde" << endl;
			cout << ("\033[0;0m");
			retardo();
		}

	}

	if (c > d) {

		system("cls");
		cout << ("\033[0;31m");
		cout << "\t EL GANADOR ES EL AUTO ROJO";
		cout << ("\033[0;0m");
	}
	else {

		system("cls");
		cout << ("\033[0;40;32m");
		cout << "\t EL GANADOR ES EL AUTO VERDE";
		cout << ("\033[0;0m");




	}

}