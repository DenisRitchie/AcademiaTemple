#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <string_view>
#include<windows.h>
#include <chrono>
#define color SetConsoleTextAttribute

std::string GetRosalinaFileContent()
{
	
	
	std::string rosalina;

	uintmax_t file_size = std::filesystem::file_size("Rosalina.txt");
	std::ifstream rosalina_file{ "Rosalina.txt" };
	

	rosalina.resize(file_size);
	rosalina_file.read(rosalina.data(), file_size);

	return std::move(rosalina);
}

int32_t main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int fila = 1;
	int col = 1;
	

	std::string rosalina = GetRosalinaFileContent();

	for (int i = 0; i < rosalina.length(); i++) {
		

		if (rosalina.at(i) == '#') {
			if (fila >= 1 && fila <= 5)
				SetConsoleTextAttribute(h, 8);
			else if (fila == 24 && col >= 39 && col <= 43)
				SetConsoleTextAttribute(h, 13);
			else if (fila >= 6 && fila <= 26)
				SetConsoleTextAttribute(h, 14);
			else if (fila == 29 && col >= 39 && col <= 43)
				SetConsoleTextAttribute(h, 14);
			else if(fila >= 32 && fila <=35 && col==61)
				SetConsoleTextAttribute(h, 8);
			else if (fila == 46 && col >=39 && col <=43)
				SetConsoleTextAttribute(h, 8);
			else
				SetConsoleTextAttribute(h, 11);
		}

		if (rosalina.at(i) == '(') {
			if(fila < 6)
				SetConsoleTextAttribute(h, 8);
			else if( fila >= 6 && fila <= 24)
				SetConsoleTextAttribute(h, 14);
			else if(fila >= 29)
				SetConsoleTextAttribute(h, 11);
			if(fila>=6 && fila <=7 && col>=28)
				SetConsoleTextAttribute(h, 8);
		}

		if (rosalina.at(i) == '/') {
			if(fila<=6)
				SetConsoleTextAttribute(h, 8);

			if(fila>=4 && fila <=5 && col>=29 && col<=30)
				SetConsoleTextAttribute(h, 9);
			if (fila >= 4 && fila <= 6 && col >= 37 && col <= 40)
				SetConsoleTextAttribute(h, 12);
			if (fila >= 4 && fila <= 5 && col >= 47 && col <= 48)
				SetConsoleTextAttribute(h, 9);

			if(fila>=7 && fila <=25)
				SetConsoleTextAttribute(h, 14);

			if (fila == 25 && col>=37 && col<=45)
				SetConsoleTextAttribute(h, 8);
			if (fila >= 47 && fila <= 48 && col >= 30 && col <= 50)
				SetConsoleTextAttribute(h, 9);
		}

		if (rosalina.at(i) == '&') {
			SetConsoleTextAttribute(h, 8);
		}
		if (rosalina.at(i) == '.') {
			SetConsoleTextAttribute(h, 8);
		}


		std::cout << rosalina.at(i);

		SetConsoleTextAttribute(h, 15);

		col++;
		if ((int)rosalina.at(i) == 10) {
			fila++;
			col = 1;
		}
			
	}


	//std::cout << rosalina << std::endl;
	//std::cout << rosalina.length() << std::endl;
	

	return 0;






}

