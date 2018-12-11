#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Ponto.h"
#include "Rectangulo.h"
#include "Janela.h"
#include "Hist.h"
#include "Dados.h"
#include "Linha.h"
#include "Circulo.h"
#include "Arvore.h"

#define VERDE RGB(0,255,0)
#define AZUL RGB(0,0,255)
#define VERMELHO RGB(255,0,0)

#define RAIO 

void main()
{
	char fich[] = { "d:\\EDA\\Mapa.txt" };

	Janela janela;
	HWND janelaId;

	Arvore tree = Arvore();
	tree.LerDados(fich);
	tree.nos[0].DefenirPai(-1);
	tree.nos[1].DefenirPai(0);
	tree.nos[2].DefenirPai(0);
	tree.nos[3].DefenirPai(1);
	tree.nos[4].DefenirPai(1);
	tree.nos[5].DefenirPai(2);
	tree.nos[6].DefenirPai(2);
	tree.nos[7].DefenirPai(3);
	tree.nos[8].DefenirPai(4);
	tree.nos[9].DefenirPai(4);
	tree.nos[10].DefenirPai(5);

	tree.DefenirFilhos();

	if (janela.Criar((char*)"Arvore binaria")) {
		if ((janelaId = janela.ObterId()) != NULL) {
			tree.DesenharCirculos(janelaId);
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0)) {
				//Ouvir
				DispatchMessage(&msg); 
				if (janela.Click()) {
					tree.ProcessarClique(Ponto(janela.ObterPonto().ObterX(), janela.ObterPonto().ObterY()));
				}
				
				//Desenhar Linhas
				tree.DesenharLinhas(janelaId);

				//Desenhar Circulos
				tree.DesenharCirculos(janelaId);
			}
		}
	}

	printf("\n\n\n\n\n");
}

