#pragma once

#include "Color.hpp"

int32_t countCharacter(const std::string& s, char c, size_t i)
{
	int32_t count{};
	
	size_t iCount{};
	
	//conteo hacia atras
	while (s[i - iCount] == c)
	{
		++count;
		++iCount;
	}
		

	iCount = 1;

	//conteo hacia delante
	while (s[i + iCount] == c)
	{
		++count;
		++iCount;
	}
		
	
	return count;
}


void ConfigColorOneTwo(const std::string &c,size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{};
	switch (c[i])
	{
	case '@':
		cout << SetColor(ConsoleColor::White);
		break;

	case '*':
		if (c[i - 1] == '/')
			cout << SetColor(ConsoleColor::Blue);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '/':
		temp = countCharacter(c, c[i], i);
		if (temp == 5 || temp == 3)
			cout << SetColor(ConsoleColor::Red);
		else if (temp == 2)
			cout << SetColor(ConsoleColor::Blue);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;

	case ',':
		if (c[i + 1] == '/')
			cout << SetColor(ConsoleColor::Blue);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;

	default:
		cout << SetColor(ConsoleColor::DarkGray);
	}
}

void ConfigColorSixSeven(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{countCharacter(c, c[i], i)};


	switch (c[i])
	{
	case '(':
		if (temp == 2 || c[i+1] != '/')
			cout << SetColor(ConsoleColor::DarkYellow);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '#':
		if (temp == 2)
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::DarkYellow);
		break;
	case '.':
		cout << SetColor(ConsoleColor::White);
		break;
	case '/':
		if (temp == 4)
			cout << SetColor(ConsoleColor::Red);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	default:
		cout << SetColor(ConsoleColor::DarkYellow);
		break;
	}
}


void ConfigColorEightSeventen(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;

	switch (c[i])
	{
	case '.':
	case ',':
		cout << SetColor(ConsoleColor::White);
		break;
	default:
		cout << SetColor(ConsoleColor::DarkYellow);
	}
}


void ConfigColor17_21(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };
	switch (c[i])
	{
		case '/':
			if (temp == 1)
				cout << SetColor(ConsoleColor::DarkGray);
			else
				cout << SetColor(ConsoleColor::DarkYellow);
			break;
		case '#':
			if (temp == 1 || c[i-1] == '*' || c[i-2] == '*')
				cout << SetColor(ConsoleColor::DarkGray);
			else
				cout << SetColor(ConsoleColor::DarkYellow);
			break;
		case '*':
			if (c[i + 1] == ',')
				cout << SetColor(ConsoleColor::DarkYellow);
			else if (c[i-1] == '%')
				cout << SetColor(ConsoleColor::Cyan);
			else cout << SetColor(ConsoleColor::DarkGray);
			break;
		case ',':
			if (temp == 1)
				cout << SetColor(ConsoleColor::DarkYellow);
			else if (c[i - 1] == '.' || c[i - 2] == '.')
				cout << SetColor(ConsoleColor::DarkGray);
			else
				cout << SetColor(ConsoleColor::Red);
			break;
		case '(':
			if (temp == 1)
				cout << SetColor(ConsoleColor::DarkYellow);
			else
				cout << SetColor(ConsoleColor::DarkGray);
			break;
		case '.':
			if (temp == 1)
				cout << SetColor(ConsoleColor::White);
			else if (temp == 5)
				cout << SetColor(ConsoleColor::Blue);
			else if (c[i - 1] == ' ' || c[i - 2] == ' ')
				cout << SetColor(ConsoleColor::DarkYellow);
			else
				cout << SetColor(ConsoleColor::Blue);
			break;
		default:
			cout << SetColor(ConsoleColor::DarkGray);
	}
}


void ConfigColor21_25(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };

	switch (c[i])
	{
	case '(':
		if (temp == 1 && c[i-1] != '&')
			cout << SetColor(ConsoleColor::DarkYellow);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;

	case '#':
		if (temp == 5)
			cout << SetColor(ConsoleColor::DarkMagenta);
		else if (temp == 1)
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::DarkYellow);
		break;
	case '/':
		if(temp == 1 && c[i-1] != '#')
			cout << SetColor(ConsoleColor::DarkGray);
		else 
			cout << SetColor(ConsoleColor::DarkYellow);
		break;
	case '*':
		if (temp == 5)
			cout << SetColor(ConsoleColor::Blue);
		else
			cout << SetColor(ConsoleColor::DarkYellow);
		break;
	case '.':
		if(c[i-1] == '#')
			cout << SetColor(ConsoleColor::DarkYellow);
		else
			cout << SetColor(ConsoleColor::White);
		break;
	case ',':
		if (temp == 1 && (c[i-1] == '(' || c[i-1] == '*'))
			cout << SetColor(ConsoleColor::Red);
		else 
			cout << SetColor(ConsoleColor::DarkYellow);
		break;
	default:
		cout << SetColor(ConsoleColor::DarkGray);
	}
}

void ConfigColor25_27(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };

	switch (c[i])
	{
	case '#':
		if (temp == 1)
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::DarkYellow);
		break;
	case ',':
		if (temp == 1)
			cout << SetColor(ConsoleColor::Red);
		else
			cout << SetColor(ConsoleColor::DarkYellow);
		break;
	case '/':
		if (temp == 2 || c[i - 1] == '#')
			cout << SetColor(ConsoleColor::DarkYellow);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '.':
		if (c[i - 1] == '#')
			cout << SetColor(ConsoleColor::DarkYellow);
		else
			cout << SetColor(ConsoleColor::White);
		break;
	case '(':
		cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '&':
		if (c[i - 1] == '#' || c[i - 2] == '#')
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::White);

		break;
	case '*':
		if (temp == 9)
			cout << SetColor(ConsoleColor::DarkGray);
		else if (c[i+1] == '/')
			cout << SetColor(ConsoleColor::DarkGray);
		else if(c[i+1] == '&' || c[i+2] == '&')
			cout << SetColor(ConsoleColor::DarkGray);
		else if(c[i-1] == '%' || c[i-2] == '%')
			cout << SetColor(ConsoleColor::DarkGray);
		else if(c[i-1] == '&' || c[i-2] == '&')
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::DarkYellow);
		break;
	default:
		cout << SetColor(ConsoleColor::White);

	}
}


void ConfigColor27_29(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };

	switch (c[i])
	{
	case '*':
		if (temp == 5)
			cout << SetColor(ConsoleColor::DarkYellow);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '/':
	case '#':
	case '(':
		cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '&':
		if(temp == 2)
			cout << SetColor(ConsoleColor::White);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	case ',':
		if(temp == 5)
			cout << SetColor(ConsoleColor::DarkYellow);
		else
			cout << SetColor(ConsoleColor::White);
		break;
	default:
		cout << SetColor(ConsoleColor::White);
	}
}

void ConfigColor29(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };
	
	switch (c[i])
	{
	case '(':
		cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '#':
		if (temp == 5)
			cout << SetColor(ConsoleColor::DarkYellow);
		break;
	default:
		cout << SetColor(ConsoleColor::Cyan);
		break;
	}
}

void Config30_34(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };

	switch (c[i])
	{
	case '*':
		if (c[i + 7] == '/' || c[i + 6] == '/')
			cout << SetColor(ConsoleColor::DarkYellow);
		else if (c[i + 5] == '/' || c[i + 4] == '/' || c[i + 3] == '/')
			cout << SetColor(ConsoleColor::DarkYellow);
		else
			cout << SetColor(ConsoleColor::Cyan);;
		break;
	case '.':
		cout << SetColor(ConsoleColor::White);
		break;
	case '#':
		if (temp == 1)
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::Cyan);
		break;
	case '/':
		if(temp == 1)
			cout << SetColor(ConsoleColor::Cyan);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '(':
		if (c[i-1] == '/' || c[i+1] == '/')
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::Cyan);
		break;
	case ',':
		if (c[i - 3] == ' ')
			cout << SetColor(ConsoleColor::Cyan);
		else if (temp == 1)
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::Blue);
		break;
	case '&':
		if(temp == 2)
			cout << SetColor(ConsoleColor::White);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	default:
		cout << SetColor(ConsoleColor::DarkGray);
		break;
	}
}

void ConfigColor34_37(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };

	switch (c[i])
	{
	case '/':
		if (temp == 2)
		{
			if (c[i + 2] == '(' || c[i + 1] == '(')
				cout << SetColor(ConsoleColor::Blue);
			else if (c[i - 1] == '(' || c[i - 2] == '(')
				cout << SetColor(ConsoleColor::Blue);
			else
				cout << SetColor(ConsoleColor::DarkGray);
		}
		else
			cout << SetColor(ConsoleColor::Cyan);
		break;
	case '&':
		if (temp == 2 || temp == 1)
			cout << SetColor(ConsoleColor::White);
		else if (c[i + 4] == '%' || c[i + 3] == '%')
			cout << SetColor(ConsoleColor::White);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '*':
		if (temp == 1)
			cout << SetColor(ConsoleColor::White);
		else if(temp == 5)
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::Cyan);
		break;
	case '(':
		if(temp == 1 && c[i+1] == '#')
			cout << SetColor(ConsoleColor::Blue);
		else
			cout << SetColor(ConsoleColor::Cyan);
		break;
	case '#':
		cout << SetColor(ConsoleColor::Cyan);
		break;
	default:
		cout << SetColor(ConsoleColor::White);
	}
}

void ConfigColor37_44(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };
	switch (c[i])
	{
	case '.':
		cout << SetColor(ConsoleColor::White);
		break;
	default:
		cout << SetColor(ConsoleColor::Cyan);
		break;
	}
}

void ConfigColor44_48(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };
	switch (c[i])
	{
	case '#':
		if (temp == 5)
			cout << SetColor(ConsoleColor::DarkGray);
		else if (c[i - 1] == ' ' || c[i - 2] == ' ')
			cout << SetColor(ConsoleColor::DarkGray);
		else if (c[i + 2] == ',' || c[i + 1] == ',')
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::Cyan);
		break;
	case '&':
		if (temp == 5)
			cout << SetColor(ConsoleColor::White);
		else if (c[i - 1] == '#' || c[i + 1] == '#')
			cout << SetColor(ConsoleColor::DarkGray);
		else
			cout << SetColor(ConsoleColor::White);;
		break;
	case ',':
		if (temp == 1)
			cout << SetColor(ConsoleColor::White);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '*':
		cout << SetColor(ConsoleColor::DarkGray);
		break;
	case '/':
		if (temp == 5)
			cout << SetColor(ConsoleColor::Blue);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	default:
		cout << SetColor(ConsoleColor::White);
		break;
	}
}

void ConfigColorEnd(const std::string& c, size_t i)
{
	using namespace Win32;
	using std::cout;
	int32_t temp{ countCharacter(c, c[i], i) };
	switch (c[i])
	{
	case '/':
		cout << SetColor(ConsoleColor::Blue);
		break;
	case '(':
		if(temp == 1)
			cout << SetColor(ConsoleColor::White);
		else
			cout << SetColor(ConsoleColor::DarkGray);
		break;
	default:
		cout << SetColor(ConsoleColor::White);
		break;
	}
}
