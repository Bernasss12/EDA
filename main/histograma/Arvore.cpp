#include "Arvore.h"
#include <cstdio>
#include <algorithm>
#include "Circulo.h"
#include "Ponto.h"
#include "Linha.h"


Arvore::Arvore()
{
	nos = NULL;
	nnos = 0;
}


Arvore::~Arvore()
{
}
	
bool Arvore::LerDados(char* fich)
{
	FILE *pfile;
	fopen_s(&pfile, fich, "r");
	if (pfile == NULL)
		return false;
	else
	{
		fscanf_s(pfile, "%d", &nnos);
		nos = new No[nnos];

		for (int i = 0; i < nnos; i++) {
			int tempx, tempy, tempv;
			fscanf_s(pfile, "%d,%d,%d", &tempx, &tempy, &tempv);
			nos[i] = No(Circulo(Ponto(tempx, tempy), 25, tempv), i);
		}

		fclose(pfile);
		return true;
	}
}

void Arvore::DesenharCirculos(HWND window)
{
	for (int i = 0; i < nnos; i++) {
		if(nos[i].ativo) nos[i].c.Desenhar(window, RGB(175, 0, 0));
		else nos[i].c.Desenhar(window, RGB(0, 175, 0));
	}
}

void Arvore::DesenharLinhas(HWND window)
{
	for(int i = 0; i < nnos; i++)
	{
		if(nos[i].parent != -1)
		{
			if (nos[i].ativo && nos[nos[i].parent].ativo) Linha(Ponto(nos[i].c.Centro().ObterX(), nos[i].c.Centro().ObterY() - 25), nos[nos[i].parent].c.Centro()).Desenhar(window, RGB(200, 0, 0));
			else Linha(Ponto(nos[i].c.Centro().ObterX(), nos[i].c.Centro().ObterY() - 25), nos[nos[i].parent].c.Centro()).Desenhar(window, RGB(0, 200, 0));

		}
	}
}

int Arvore::Ativo()
{
	for (int i = 0; i < nnos; i++) if(nos[i].ativo) return i;
	return -1;
}

int Arvore::Ativos()
{
	int n = 0;
	for (int i = 0; i < nnos; i++) if (nos[i].ativo) n++;
	return n;
}

int Arvore::Contem(Ponto p)
{
	for (int i = 0; i < nnos; i++) if (nos[i].c.Contem(p)) return i;
	return -1;
}

void Arvore::DefenirFilhos()
{
	for(int i = 0; i < nnos; i++)
	{
		if(nos[nos[i].parent].first_child != -1)
		{
			nos[nos[i].parent].first_child = i;
		}else if(nos[nos[i].parent].second_child != -1)
		{
			nos[nos[i].parent].second_child = i;
		}
		else;
	}
}

void Arvore::Desativar()
{
	for (int i = 0; i < nnos; i++) nos[i].Desativar();
}

bool Arvore::PesquisarPais(int no1, int no2)
{
	if(no1 == no2)
	{
		return true;
	}else if (nos[no1].parent != -1)
	{
		PesquisarPais(nos[no1].parent, no2);
	}else
	{
		return false;
	}
}

void Arvore::AtivarPais(int no1, int no2)
{
	if (no1 == no2)
	{
		nos[no1].Ativar();
		return;
	}
	else if (nos[no1].parent != -1)
	{
		nos[no1].Ativar();
		AtivarPais(nos[no1].parent, no2);
		return;
	}
	else
	{
		return;
	}
}

void Arvore::ProcessarClique(Ponto p)
{
	int no = Contem(p);
	int no_a;
	if(no != -1)
	{
		switch (Ativos()) 
		{ 
		case 0:
			nos[no].Ativar();
			break;
		case 1:
			no_a = Ativo();
			if (PesquisarPais(no, Ativo()))
			{
				nos[no].Ativar(); 
				AtivarPais(no, no_a);
			}
			else if (PesquisarPais(no_a, no))
			{
				nos[no].Ativar(); 
				AtivarPais(no_a, no);
			}
			else Desativar();
			break;
		default:
			Desativar();
			break;
		}
	}else
	{
		Desativar();
	}
}

