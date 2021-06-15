#include<iostream>
#include<string>
#include<windows.h>
#define color SetConsoleTextAttribute 

int32_t main()
{
	setlocale(LC_ALL, ".utf8");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	const char a = u'_', b = u'▓', c = u'▒', d = u'░', e = u'█';
	const char mario[12052] =
#include "Mario.txt"
	;
	for (int i = 0; i < 12052; ++i)
	{
		if (mario[i]==a){
			color(hConsole, 7);
		}
		else if(mario[i]==b){
			color(hConsole, 4);
		}
		else if (mario[i] == c) {
			color(hConsole, 1);
		}
		else if (mario[i] == d) {
			color(hConsole, 12);
		}
		else if (mario[i] == e) {
			color(hConsole, 0);
		}
		else{
			color(hConsole, 8);
		}
		std::cout << mario[i];
	}
	
	return 0;
}