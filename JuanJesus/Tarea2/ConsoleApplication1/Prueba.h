#pragma once

#include <iostream>
#include <Windows.h>

class Prueba
{
private:
	COORD coord1{ .X = 0 , .Y = 0 };
	COORD coord2{ .X = 0 , .Y = 0 };

public:

	Prueba() = default;
	Prueba cord1(COORD coord1)
	{
		this->coord1.X = coord1.X;
	};
	Prueba cord2(COORD coord2)
	{
		this->coord2.X = coord2.X;
	}

	int32_t GetCoord1()
	{
		return coord1.X;
	}

	int32_t GetCoord2()
	{
		return coord2.X;
	}

};