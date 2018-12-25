#pragma once
#include "Rede.h"

class Aresta {
private:
	int v;
	int w;
	float weight;

public:
	Aresta();
	Aresta(Rede r, int vi, int vf);
	~Aresta();

	int Begin();
	int End();
	int Weight();
};

