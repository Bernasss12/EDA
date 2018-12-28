#pragma once
#define RAIO 10
#define COLOR_ACTIVE RGB(226, 180, 63)
#define COLOR_ACTIVE_PATH RGB(219, 146, 21)
#define COLOR_INACTIVE RGB(72, 137, 242)
#include "Circulo.h"
#include "Linha.h"
#include "Aresta.h"
#include "Janela.h"
#include "Graph.h"

class No
{
public:
	Circulo c;
	int index;
	int length;
	int* destinos;
	bool ativo;

	void Desenhar(HWND janelaId) {
		if (ativo) c.Desenhar(janelaId, COLOR_ACTIVE); else c.Desenhar(janelaId, COLOR_INACTIVE);};
	No() { c = Circulo(); index = -1; destinos = NULL; length = 0; ativo = false; };
	No(int x, int y, int index_p) { c = Circulo(Ponto(x, y), RAIO, index_p); index = index_p; destinos = NULL; length = 0; ativo = false; };
	~No() {};

	bool Ativo() { return ativo; };
	void Ativar() { ativo = true; };
	void Desativar() { ativo = false; }
};

class Rede
{
public:
	int inicio, fim;

	Aresta* caminhos;
	No* nos;
	int ncaminhos;
	int nnos;
	Rede();
	~Rede();

	bool ObterNos(char* nPath, char* dPath);
	void DesenharCaminhos(HWND janelaId);
	void CarregarCaminhos();
	void DesenharNos(HWND janelaId);
	void AtivarCaminho(int v, int c, Graph grafo);

	int Contem(Ponto p);

	int Ativos();

	void update(Janela janela, Graph grafo);
};