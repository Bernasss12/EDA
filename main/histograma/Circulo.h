#pragma once
#include <windows.h>
#include "Ponto.h"
class Circulo {
private:
	Ponto centro; // coordenadas do centro
	int raio; // raio do círculo
	int valor; // número que se escreve dentro do círculo
public:
	Circulo(); // construtor por defeito
	Circulo(Ponto c, int r, int v);
	Ponto Centro() { return centro; }
	void Desenhar(HWND janelaId, long cor); // Desenha graficamente o circulo
	bool Contem(Ponto p); // verifica se o ponto está dentro do circulo
};

