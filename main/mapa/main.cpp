#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Janela.h"
#include "Rede.h"
#include "Graph.h"

#define VERDE RGB(0,255,0)
#define AZUL RGB(0,0,255)
#define VERMELHO RGB(255,0,0)

void main()
{
	char fich_mapa[] = { "d:\\EDA\\Mapa.txt" };
	char fich_rede[] = { "d:\\EDA\\Rede.txt" };
	char imgpath[] = { "d:\\EDA\\MAPA.bmp" };

	Janela janela;
	HWND janelaId;

	Rede rede;
	if (rede.ObterNos(fich_mapa, fich_rede)) {
		printf("Carregado com sucesso.");
	}
	else{
		printf("Falha ao obter os nos.");
		exit(1);
	}
	rede.CarregarCaminhos();
	
	Graph grafo(rede.nnos);
	for (int i = 0; i < rede.ncaminhos; i++) grafo.InsertEdge(rede.caminhos[i]);

	//grafo.WriteADJ();

	if (janela.Criar((char*)"Mapa", (char*)imgpath)) {
		if ((janelaId = janela.ObterId()) != NULL) {
			
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0)) {
				DispatchMessage(&msg); 
				if (janela.Click()) {
					rede.update(janela, grafo);
				}
				rede.DesenharCaminhos(janelaId);
				rede.DesenharNos(janelaId);
			}
		}
	}

	printf("\n\n\n\n\n");
}

