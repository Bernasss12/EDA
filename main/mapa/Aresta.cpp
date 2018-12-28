#include "Aresta.h"

Aresta::Aresta()
{
	p = 0;
	d = 0;
	weight = 0;
	ativa = false;
}

Aresta::Aresta(float w, int vi, int vf)
{
	p = vi;
	d = vf;
	weight = w;
	ativa = false;
}


Aresta::~Aresta()
{
}

int Aresta::Partida()
{
	return p;
}

int Aresta::Destino()
{
	return d;
}

float Aresta::Distancia()
{
	return weight;
}
