#pragma once
#include <windows.h>
#include "Ponto.h"
class Circulo {
private:
	Ponto centro; // coordenadas do centro
	int raio; // raio do c�rculo
	int valor; // n�mero que se escreve dentro do c�rculo
public:
	Circulo(); // construtor por defeito
	Circulo(Ponto c, int r, int v);
	Ponto Centro() { return centro; }
	void Desenhar(HWND janelaId, long cor); // Desenha graficamente o circulo
	bool Contem(Ponto p); // verifica se o ponto est� dentro do circulo
};

