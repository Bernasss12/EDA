#pragma once
#define RAIO 10
#define COLOR RGB(255, 0, 0)
#define COLOR_LINHA RGB(0, 0, 150)
#include "Circulo.h"
#include "Linha.h"

class No
{
public:
	Circulo c;
	int index;
	int length;
	int* destinos;

	void Desenhar(HWND janelaId) { c.Desenhar(janelaId, COLOR); }
	No() { c = Circulo(); index = -1; destinos = NULL; length = 0; };
	No(int x, int y, int index_p) { c = Circulo(Ponto(x, y), RAIO, index_p); index = index_p; destinos = NULL; length = 0; };
	~No() {};
};

class Rede
{
public:
	No* nos;
	int nnos;
	Rede();
	~Rede();

	bool ObterNos(char* nPath, char* dPath);
	void DesenharLinhas(HWND janelaId);
};