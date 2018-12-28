#include "Ponto.h"
#include <Math.h>

Ponto::Ponto()
{
	x = 0;
	y = 0;
}

Ponto::Ponto(int x1, int y1)
{
	x = x1;
	y = y1;
}


void Ponto::AtribuirXY(int x1, int y1)
{
	x = x1;
	y = y1;
}

float Ponto::ObterDistancia(Ponto p2)
{
	return sqrt(pow(x - p2.ObterX(), 2) + pow(y - p2.ObterY(), 2));
}

int Ponto::ObterX()
{
	return x;
}

int Ponto::ObterY()
{
	return y;
}

Ponto::~Ponto()
{
}
