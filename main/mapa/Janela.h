#pragma once
#include <Windows.h>
#include "Ponto.h"

class Janela {
private:
	HWND janelaId;
	Ponto cur_coord;
	bool clickou;
	static Janela* objecto;
	static Janela* ObterObjecto();
public:
	Janela();
	~Janela();
	bool Criar(char* sTitulo, char* sNome);
	static LRESULT CALLBACK DespacharMensagens(HWND janId, unsigned int msg, WPARAM wp, LPARAM lp);
	HWND ObterId() { return janelaId; }
	bool Click() { return clickou; }
	Ponto ObterPonto() { return cur_coord; }
};