#include "Rede.h"
#include <cstdio>



Rede::Rede()
{
	inicio = 0;
	fim = 0;
	nnos = 0;
	ncaminhos = 0;
	nos = NULL;
	caminhos = NULL;
}

Rede::~Rede()
{
	delete[] nos;
	delete[] caminhos;
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
			//printf("\n%2d: ", i + 1);
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
				//printf("%2d, ", nos[i].destinos[j]);
			}
			
		}

		fclose(fNos);
		fclose(fCaminhos);
		return true;
	}
	return false;
}

void Rede::DesenharCaminhos(HWND janelaId)
{
	int count = 0;
	for (int i = 0; i < ncaminhos; i++){
		if(caminhos[i].Ativa())Linha(nos[caminhos[i].Partida()].c.Centro(), nos[caminhos[i].Destino()].c.Centro()).Desenhar(janelaId, COLOR_ACTIVE_PATH);
		else Linha(nos[caminhos[i].Partida()].c.Centro(), nos[caminhos[i].Destino()].c.Centro()).Desenhar(janelaId, COLOR_INACTIVE);
		count++;
		//printf("\n\nPrinting: %d-%d\n", i, nos[i].destinos[j] - 1);
	}
	//printf("\n\nCaminhos count: %d", count);
}

void Rede::CarregarCaminhos() {
	
	bool existe;
	int linhas_temporario = 0;
	int linhas = 0;
	int partida_temp, destino_temp;

	for (int i = 0; i < nnos; i++)
	{
		linhas_temporario += nos[i].length;
	}
	
	//Cria vetor de arestas com muito mais espaco do que possivelmente necessario
	Aresta* temp = new Aresta[linhas_temporario];

	for (int i = 0; i < nnos; i++) {
		for (int j = 0; j < nos[i].length; j++) {
			existe = false;
			partida_temp = min(i, nos[i].destinos[j] - 1);
			destino_temp = max(i, nos[i].destinos[j] - 1);

			//Caso ja hajam caminhos definidos, verifica todos os existentes para nao registar caminhos repetidos
			if (linhas > 0) {
				for (int k = 0; k < linhas; k++) {
					if (temp[k].Partida() == partida_temp && temp[k].Destino() == destino_temp) {
						existe = true;
						break;
					}
				}
			}

			//Caso o caminho ainda nao exista cria-o
			if (!existe) {
				temp[linhas] = Aresta(Linha(nos[partida_temp].c.Centro(), nos[destino_temp].c.Centro()).ObterComprimento(), partida_temp, destino_temp);
				linhas++;
				//printf("\nAdicionado %d -> %d", partida_temp, destino_temp);
			}
			else {

				//printf("\nJa existe %d -> %d", partida_temp, destino_temp);
			}
		}
	}

	//Cria e transfere a informacao necessaria para um vetor com o tamanho necessario
	caminhos = new Aresta[linhas + 1];
	for (int i = 0; i < linhas; i++) {
		caminhos[i] = temp[i];
	}

	ncaminhos = linhas + 1;

	//Apaga vetor temporario
	delete[] temp;
}

void Rede::DesenharNos(HWND janelaId)
{
	for (int i = 0; i < nnos; i++) {
		nos[i].Desenhar(janelaId);
	}
}

void Rede::AtivarCaminho(int v, int c, Graph grafo){
	grafo.Dijkstra(v);
	int temp_inicio, temp_fim, ver_inicio, ver_fim;
	for (int i = 0; i < grafo.VertNumber(); i++) {
		temp_inicio = min(c, grafo.PrevVert(c));
		temp_fim = max(c, grafo.PrevVert(c));
		//Ativar primeiro no
		if (i == 0) nos[c].Ativar();
		else if (c != v) {
			//Ativar nos
			nos[c].Ativar();
			c = grafo.PrevVert(c);
			//Ativar caminho
			for (int j = 0; j < ncaminhos; j++) {
				ver_inicio = caminhos[j].Partida();
				ver_fim = caminhos[j].Destino();
				if (ver_inicio == temp_inicio && ver_fim == temp_fim) caminhos[j].Ativar();
			}
			if (c == v) break;
		}
	}
}

int Rede::Contem(Ponto p)
{
	int contem = -1;
	for (int i = 0; i < nnos; i++) {
		if (nos[i].c.Contem(p)) {
			contem = i;
			break;
		}
	}
	return contem;
}

int Rede::Ativos()
{
	int count = 0;
	for (int i = 0; i < nnos; i++)
		if (nos[i].ativo) count++;
	return count;
}

void Rede::update(Janela janela, Graph grafo)
{
	int a = Ativos();
	int n = Contem(janela.ObterPonto());
	if (n != -1) {
		if (a == 0) {
			nos[n].Ativar();
			inicio = n;
		}
		else if (a == 1) {
			if (nos[n].Ativo()) nos[n].Desativar();
			else {
				nos[n].Ativar();
				fim = n;
				grafo.WritePath(inicio, fim);
				AtivarCaminho(inicio, fim, grafo);
				printf("\n\n%d -> %d", inicio + 1, fim + 1);
			}
		}
		else {
			for (int i = 0; i < nnos; i++) nos[i].Desativar();
			for (int i = 0; i < ncaminhos; i++) caminhos[i].Desativar();
			inicio = 0;
			fim = 0;
		}
	}
	else {
		for (int i = 0; i < nnos; i++) nos[i].Desativar();
		for (int i = 0; i < ncaminhos; i++) caminhos[i].Desativar();
		inicio = 0;
		fim = 0;
	}
}
