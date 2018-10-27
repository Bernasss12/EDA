#define _CRT_SECURE_NO_WARNINGS

#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

// Cria uma matriz completamente vazia, 0 linhas, 0 colunas e todos os elementeos null
Matriz::Matriz()
{
	elems = NULL;
	linhas = 0;
	colunas = 0;
}
// Cria uma matriz a 0 de acordo com os valores de linhas e colunas dados
void Matriz::Iniciar(int nLinhas, int nColunas)
{
	linhas = nLinhas;
	colunas = nColunas;
	elems = new float*[linhas];
	for (int i = 0; i < linhas; i++)
	{
		elems[i] = new float[colunas];
		for (int j = 0; j < colunas; j++)
		{
			elems[i][j] = 0;//Todos os elementos sao inicializados como 0
		}
	}
}
// Cria matriz apartir de outra
Matriz::Matriz(const Matriz& m1)
{
	Iniciar(m1.linhas, m1.colunas);
	for (int i = 0; i < m1.linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			elems[i][j] = m1.elems[i][j];
		}
	}
}
// Inicia matriz
Matriz::Matriz(int nLinhas, int nColunas)
{
	Iniciar(nLinhas, nColunas);
}
// Apaga a matriz
void Matriz::Apagar()
{
	for (int i = 0; i<linhas; i++)
		delete[]elems[i];
	delete[]elems;
}
// Le matriz apartir de ficheiro
bool Matriz::Ler(char*nome_ficheiro)
{
	FILE*ficheiro;
	ficheiro = fopen(nome_ficheiro, "r");
	if (!ficheiro) return false;
	fscanf_s(ficheiro, "%d,%d", &linhas, &colunas);
	Iniciar(linhas, colunas);
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
			fscanf_s(ficheiro, "%f", &elems[i][j]);
	}
	fclose(ficheiro);
	return true;
}
// Imprime a matriz
void Matriz::Escrever()
{
	for (int i = 0; i < linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			printf("%.1f  ", elems[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
// Metodo destruidor de matrizes
Matriz::~Matriz()
{
	Apagar();
}
// Verifica a possibilidade de somar duas matrizes
bool Matriz::PodeSomar(const Matriz* pm)
{
	return linhas == pm->linhas && colunas == pm->colunas;
}
// Verifica a possibilidade de multiblicar duas matrizes
bool Matriz::PodeMultiplicar(const Matriz* pm)
{
	return colunas == pm->linhas;
}
// Operador que iguala a matriz da direita à da esquerda
const Matriz& Matriz::operator = (const Matriz& m1)
{
	Iniciar(m1.linhas, m1.colunas);
	for (int i = 0; i < m1.linhas; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			elems[i][j] = m1.elems[i][j];
		}
	}

	return *this;
}
// Operador que resulta na soma das matrizes em questao
Matriz Matriz::operator + (const Matriz& m1)
{
	Matriz resultado(m1.linhas, m1.colunas);
	if (PodeSomar(&m1)) {
		for (int i = 0; i < linhas; i++)
		{
			for (int j = 0; j < colunas; j++)
			{
				resultado.elems[i][j] = elems[i][j] + m1.elems[i][j];
			}
		}
	}
	else
	{
		printf("\nA soma nao eh possivel");
	}

	return resultado;
}
// Operador que resulta no produto das matrizes inseridas
Matriz Matriz::operator * (const Matriz& m1)
{
	if (PodeMultiplicar(&m1)) {
		Matriz temp = *this;
		Apagar();
		Iniciar(temp.colunas, m1.linhas);
		for (int i = 0; i < temp.linhas; i++)
		{
			for (int j = 0; j < temp.colunas; j++)
			{
				for (int k = 0; k < temp.colunas; k++)
				{
					elems[i][j] += temp.elems[i][k] * m1.elems[k][j];
				}
			}
		}
	}
	else
	{
		printf("\nO produto nao eh possivel");
	}
	return *this;
}
//Decompoe matrizes
Matriz Matriz::DecomporLU()
{
	if (!Quadrada()) return Matriz();

	Matriz upper = Matriz(linhas, colunas);
	Matriz lower = Matriz(linhas, colunas);
	Matriz temp = *this;
	Matriz result = Matriz(linhas, colunas);

	for (int i = 0; i < linhas; i++)
	{
		// Matriz U
		for (int k = i; k < linhas; k++) {
			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower.elems[i][j] * upper.elems[j][k]);
			upper.elems[i][k] = temp.elems[i][k] - sum;
		}

		// Matriz L
		for (int k = i; k < linhas; k++) {
			if (i == k)
				lower.elems[i][i] = 1; // Diagonal = 1
			else {
				int sum = 0;
				for (int j = 0; j < i; j++)
					sum += (lower.elems[k][j] * upper.elems[j][i]);
				lower.elems[k][i] = (temp.elems[k][i] - sum) / upper.elems[i][i];
			}
		}
	}
	//Resultado
	result = lower;
	for (int i = 0; i < linhas; i++)
	{
		result.elems[i][i] = 0; // Diagonal = 0
	}
	return result + upper;
}
//Decompoe 
Matriz Matriz::DecomporLU(char mode)
{
	if (!Quadrada()) return Matriz();

	Matriz upper = Matriz(linhas, colunas);
	Matriz lower = Matriz(linhas, colunas);
	Matriz temp = *this;
	Matriz result = Matriz(linhas, colunas);

	for (int i = 0; i < linhas; i++)
	{
		// Matriz U
		for (int k = i; k < linhas; k++) {
			int sum = 0;
			for (int j = 0; j < i; j++)
				sum += (lower.elems[i][j] * upper.elems[j][k]);
			upper.elems[i][k] = temp.elems[i][k] - sum;
		}

		// Matriz L
		for (int k = i; k < linhas; k++) {
			if (i == k)
				lower.elems[i][i] = 1; // Diagonal = 1
			else {
				int sum = 0;
				for (int j = 0; j < i; j++)
					sum += (lower.elems[k][j] * upper.elems[j][i]);
				lower.elems[k][i] = (temp.elems[k][i] - sum) / upper.elems[i][i];
			}
		}
	}
	if (mode == 'L') return lower; //Devolve L
	else if (mode == 'U') return  upper; //Devolve U
	else return Matriz();
}

/*** Funcoes extra ***/

//Verifica se a matriz eh quadrada
bool Matriz::Quadrada()
{
	return linhas == colunas;
}
//Devolve as linhas da matriz
int Matriz::Linhas()
{
	return linhas;
}
//Devolve as colunas da matriz
int Matriz::Colunas()
{
	return colunas;
}
//Devolve o elemento [l][c] da matriz
float Matriz::Elemento(int linha, int coluna)
{
	return elems[linha][coluna];
}
//Devolve o conjunto dos elementos da matriz
float** Matriz::Elementos()
{
	return elems;
}
