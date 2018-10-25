#pragma once

// Defini��o da classe Matriz que contem as opera��es
// tipicas de matrizes

class Matriz {
private:
	float **elems;
	int linhas;
	int colunas;
	// Fun��es privadas
	void Apagar();
	void Iniciar(int nLinhas, int nColunas);
public:
	Matriz();
	Matriz(const Matriz& m1); 
	Matriz(int nLinhas, int nColunas);
	~Matriz();
	bool PodeMultiplicar(const Matriz *pm);
	bool PodeSomar(const Matriz* pm);
	const Matriz& operator = (const Matriz& m1);
	Matriz operator + (const Matriz& m1);
	Matriz operator * (const Matriz& m1);
	bool Ler(char* nome_ficheiro);
	void Escrever();
	Matriz DecomporLU();

	//Funcoes extra "getters"
	int Linhas();
	int Colunas();
	float Elemento(int linha, int coluna); 
	float** Elementos(); 
};