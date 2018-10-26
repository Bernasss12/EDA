#pragma once

// Definição da classe Matriz que contem as operações
// tipicas de matrizes

class Matriz {
private:
	float **elems;
	int linhas;
	int colunas;
	// Funções privadas
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
	Matriz DecomporLU(char);
	float calcularDet();
	Matriz obterInversa();

	//Funcoes extra "getters"
	bool Quadrada();
	int Linhas();
	int Colunas();
	float Elemento(int linha, int coluna); 
	float** Elementos(); 
};