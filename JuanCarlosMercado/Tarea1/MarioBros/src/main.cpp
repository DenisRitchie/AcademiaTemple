#include <iostream>
#include <string>

using namespace std;

namespace pixels {
	const string black_full		{ "\033[0;30m█" };
	const string black_left		{ "\033[0;30m▌" };
	const string black_right	{ "\033[0;30m▐" };
	const string black_up		{ "\033[0;30m▀" };
	const string black_down		{ "\033[0;30m▄" };


	const string white			{ "\033[1;37m█" };
	const string eyes			{ "\033[0;34m▒" };
	const string red			{ "\033[0;31m█" };
	const string green			{ "\033[0;32m" };
	const string skin			{ "\033[0;33m░" };
	const string gold			{ "\033[1;33m█" };
	const string cofee			{ "\033[0;33m█" };
	const string light_blue		{ "\033[1;34m░" };
	const string blue			{ "\033[0;34m█" };
	const string magenta		{ "\033[0;35m" };
	const string cyan			{ "\033[0;36m" };
	const string reset			{ "\033[0m"    };
}

int32_t main()
{
	u32string mario =
		#include "../txt/U_mario-utf8.txt"
	;

	// const char *mario_chars = ( const char * )mario.data();

	int32_t numero_de_caracteres = mario.size();
	char32_t caracter;
	u32string cadena;

	for ( int32_t i = 0; i < numero_de_caracteres; i++ ) {
		caracter = mario[i];
		cadena = mario[i];

		if ( caracter == U'\n' )
			cout << pixels::reset << endl;

		else if ( caracter == U'.')
			cout << pixels::light_blue;

		else if ( caracter == U'_')
			cout << pixels::white;

		else if ( caracter == U'$' )
			cout << pixels::eyes;

		else if ( caracter == U'█' )
			cout << pixels::black_full;

		else if ( caracter == U'▄' )
			cout << pixels::black_down;

		else if ( caracter == U'▀' )
			cout << pixels::black_up;

		else if ( caracter == U'▌' )
			cout << pixels::black_left;

		else if ( caracter == U'▐')
			cout << pixels::black_right;
		 
		else if ( caracter == U'▓' ) // ─
			cout << pixels::red;

		else if ( caracter == U'▒' ) // ─
			cout << pixels::blue;

		else if ( caracter == U'░' ) // ─
			cout << pixels::skin;

		else if ( caracter == U',' ) // ─
			cout << pixels::gold;

		else if ( caracter == U'T' ) // ─
			cout << pixels::cofee;
	}
	
	return EXIT_SUCCESS;
}
