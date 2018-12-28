#pragma once

class Aresta {
private:
	int p;
	int d;
	float weight;
	bool ativa;

public:
	Aresta();
	Aresta(float w, int vi, int vf);
	~Aresta();

	int Partida();
	int Destino();
	float Distancia();

	bool Ativa() { return ativa; }
	void Ativar() { ativa = true; }
	void Desativar() { ativa = false; }
};

