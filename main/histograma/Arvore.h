#pragma once
#include "Circulo.h"

class No
{
public:
	Circulo c;
	int index;
	int parent;
	int first_child;
	int second_child;
	bool ativo;

	No() { c = Circulo(); index = 0; parent = 0; ativo = false; };
	No(Circulo circulo, int i) { c = circulo;  index = i; ativo = false; parent = -1; first_child = -1; second_child = -1; };
	~No() {};
	void DefenirPai(int p) { parent = p; }
	void Ativar() { ativo = true; }
	void Desativar() { ativo = false; }
};

class Arvore
{
public:
	No* nos;
	int nnos;

	Arvore();
	~Arvore();
	int Ativo();
	int Ativos();
	int Contem(Ponto p);
	void DefenirFilhos();
	bool LerDados(char* fich);
	bool PesquisarPais(int no1, int no2);
	void AtivarPais(int no1, int no2);
	void Desativar();
	void DesenharCirculos(HWND window);
	void DesenharLinhas(HWND window);
	void ProcessarClique(Ponto p);
};

