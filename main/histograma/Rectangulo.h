#pragma once
#include <Windows.h>
#include "Ponto.h"

class Rectangulo
{
private:
	Ponto topo_esq, base_dir;
public:
	Rectangulo(Ponto tl, Ponto br);
	Rectangulo(int x1, int y1, int x2, int y2);
	void Desenhar(HWND janelaId, long cor);
	bool Contem(Ponto p); 
	bool Contem(Rectangulo r);
	double ObterArea();
	int ObterPerimetro();
};

