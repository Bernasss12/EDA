#include "Rede.h"
#include <cstdio>
#include "Linha.h"


Rede::Rede()
{
	nnos = 0;
	nos = NULL;
}


Rede::~Rede()
{
}

bool Rede::ObterNos(char * nPath, char * dPath)
{
	FILE *fNos;
	FILE *fCaminhos;

	fopen_s(&fNos, nPath , "r");
	fopen_s(&fCaminhos, dPath, "r");

	if (fNos == NULL || fCaminhos == NULL)
	{
		return false;
	}else
	{
		int nnosc = 0;
		fscanf_s(fNos, "%d", &nnos);
		fscanf_s(fCaminhos, "%d", &nnosc);

		if (nnos != nnosc) return false;

		nos = new No[nnos];

		for (int i = 0; i < nnos; i++) {
			printf("\n%2d: ", i + 1);
			int tempx, tempy;
			fscanf_s(fNos, "%d,%d", &tempx, &tempy);
			nos[i] = No(tempx, tempy, i + 1);
			int nCaminhos = 0;
			fscanf_s(fCaminhos, "%d,", &nCaminhos);
			nos[i].destinos = new int[nCaminhos];
			nos[i].length = nCaminhos;
			for(int j = 0; j <nCaminhos; j++)
			{
				fscanf_s(fCaminhos, "%d,", &nos[i].destinos[j]);
				printf("%2d, ", nos[i].destinos[j]);
			}
			
		}

		fclose(fNos);
		fclose(fCaminhos);
		return true;
	}
	return false;
}

void Rede::DesenharLinhas(HWND janelaId)
{   
	for (int i = 0; i < nnos; i++)
	{
		for(int j = 0; j < nos[i].length; j++)
		{
			Linha(nos[i].c.Centro(), nos[nos[i].destinos[j] - 1].c.Centro()).Desenhar(janelaId, COLOR_LINHA);
			printf("\n\nPrinting: %d-%d", i, nos[i].destinos[j] - 1);
		}
		printf("\n");
	}
}
