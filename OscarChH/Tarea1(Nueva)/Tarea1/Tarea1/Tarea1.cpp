#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <string_view>
#include "Color.hpp"
#include "opciones.hpp"

std::string GetRosalinaFileContent();
void ConfigColor(const std::string&, size_t, int16_t);


int main()
{
	using namespace Win32;
	using  std::cout;
	std::string rosalina = GetRosalinaFileContent();

	int16_t count_n{};//contador para saltos de linea

	for (size_t i = 0; i < rosalina.length(); ++i)
	{
		if (rosalina[i] == '\n')
			++count_n;
		if (rosalina[i] == '@')
			cout << SetColor(ConsoleColor::White);
		else if (rosalina[i] == '%')
			cout << SetColor(ConsoleColor::DarkGray);
		else
			ConfigColor(rosalina,i,count_n);
		cout << rosalina[i];
	}
	std::cout << "\n\n "<<count_n;

	return 0;
}






void ConfigColor(const std::string& s, size_t i, int16_t n_saltos)
{
	using namespace Win32;
	using  std::cout;
	
	if (n_saltos < 6)
		ConfigColorOneTwo(s, i);

	else if (n_saltos >= 6 && n_saltos < 8)
		ConfigColorSixSeven(s, i);

	else if (n_saltos >= 8 && n_saltos < 17)
		ConfigColorEightSeventen(s, i);
	else if (n_saltos >= 17 && n_saltos < 21)
		ConfigColor17_21(s, i);
	else if (n_saltos >= 21 && n_saltos < 25)
		ConfigColor21_25(s, i);
	else if (n_saltos >= 25 && n_saltos < 27)
		ConfigColor25_27(s, i);
	else if (n_saltos >= 27 && n_saltos < 29)
		ConfigColor27_29(s, i);
	else if (n_saltos == 29)
		ConfigColor29(s, i);
	else if (n_saltos >= 30 && n_saltos < 34)
		Config30_34(s, i);
	else if (n_saltos >= 34 && n_saltos < 37)
		ConfigColor34_37(s, i);
	else if (n_saltos >= 37 && n_saltos < 44)
		ConfigColor37_44(s, i);
	else if (n_saltos >= 44 && n_saltos < 48)
		ConfigColor44_48(s, i);
	else if (n_saltos >= 48)
		ConfigColorEnd(s,i);
	else
		cout << SetColor(ConsoleColor::Cyan);
}



std::string GetRosalinaFileContent()
{
	std::string rosalina;

	uintmax_t file_size = std::filesystem::file_size("Rosalina.txt");
	std::ifstream rosalina_file{ "Rosalina.txt" };

	rosalina.resize(file_size);
	rosalina_file.read(rosalina.data(), file_size);

	return std::move(rosalina);
}


