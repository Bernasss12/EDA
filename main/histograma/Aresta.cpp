#include "Aresta.h"



Aresta::Aresta()
{
	v = 0;
	w = 0;
	weight = 0;
}

Aresta::Aresta(Rede r, int vi, int vf)
{
	v = vi;
	w = vf;
	weight = Linha(r.nos[vi].c.Centro(), r.nos[vf].c.Centro()).ObterComprimento();
}


Aresta::~Aresta()
{
}

int Aresta::Begin()
{
	return v;
}

int Aresta::End()
{
	return w;
}

int Aresta::Weight()
{
	return weight;
}
