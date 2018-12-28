#include "Graph.h"
#include <stdio.h>

Graph::Graph(int v)
{
	int i, j;

	edge_number = 0;
	vert_number = v;
	maxWeight = 0;
	adj_mat = new float*[vert_number];
	source_vert = new int [vert_number];
	path_weight = new float [vert_number];
	adj_vert = new int [vert_number];

	for (i = 0; i < vert_number; i++)
		adj_mat[i] = new float [vert_number];

	for (i = 0; i < vert_number; i++)
	{
		source_vert[i] = -1;
		path_weight[i] = -1;
		adj_vert[i] = -1;
		for (j = 0; j < vert_number; j++)
			adj_mat[i][j] = 0;
	}
}

Graph::~Graph(void)
{
}

void Graph::InsertEdge(Aresta e)
{
	int v = e.Partida();
	int w = e.Destino();
	float weight = e.Distancia();

	if (v >= 0 && v < vert_number && 
		w >= 0 && w < vert_number)
	{
		if (adj_mat[v][w] < 0) edge_number++;
		adj_mat[v][w] = weight;
		adj_mat[w][v] = weight;
		maxWeight += weight;
	}
}

void Graph::RemoveEdge(Aresta e)
{
	int v = e.Partida();
	int w = e.Destino();

	if (v >= 0 && v < vert_number &&
		w >= 0 && w < vert_number)
	{
		if (adj_mat[v][w] >= 0) edge_number --;
		maxWeight -= adj_mat[v][w];
		adj_mat[v][w] = 0;
		adj_mat[w][v] = 0;
		
	}
}

void Graph::WriteADJ()
{
	int i, j;
	for (i=0; i<vert_number; i++)
	{
		for (j=0; j<vert_number; j++)
			printf ("%7.2f  ", adj_mat[i][j]);
		printf("\n");
	}
}

void Graph::WriteMinCostPath()
{
	for (int v=0; v < vert_number; v++)
		if (source_vert[v] < 0)
			printf ("Vert: %2d, Vert. anterior: --, Comp.: %7.2f \n", v + 1, path_weight[v]);
		else
			printf ("Vert: %2d, Vert. anterior: %2d, Comp.: %7.2f \n", v + 1, source_vert[v] + 1, path_weight[v]);
}

// Algoritmo de Dijkstra em relação ao vértice de partida s
void Graph::Dijkstra (int s)
{
	int v, w;

	for (v = 0; v < vert_number; v++)
	{
		path_weight [v] = maxWeight;
		adj_vert[v] = v;
	}
	path_weight[s] = 0;
	SortVert(s);

	//printf("\nFase 1.\n");
	//printf("\nAdj vert: %d", adj_vert[0]);

	while (adj_vert[0] != -1)	// Lista vazia de vértices adjacentes
	{
		//printf("\nAdj vert: %d", adj_vert[0]);
		if (path_weight[v=adj_vert[0]] != maxWeight)
		{
			RemoveVert(0);
			for ( w = 0; w < vert_number; w++)
				if (w != v && IsAdjVert(w) && adj_mat[v][w] > 0)	// Vértice adjacente
					if (path_weight[w] > path_weight[v] + adj_mat[v][w])
					//if (path_weight[w] > adj_mat[v][w])
					{
						path_weight[w] = path_weight[v] + adj_mat[v][w];
						SortVert(w);
						source_vert[w] = v;
					}
		}
	}
}

bool Graph::IsAdjVert(int v)
{
	for (int i = 0; i < vert_number && adj_vert[i] != -1; i++)
		if (adj_vert[i] == v)
			return true;
	return false;
}

void Graph::SortVert(int v)
{
	int i, j;
	float weight = path_weight[v];
	// Encontrar a posição de v dentro do array adj_vert
	for (i = 0; i < vert_number && adj_vert[i] != -1; i++)
		if (adj_vert[i] == v)
			break;
	if (i >= vert_number)
		return;
	// Deslocamento para a esquerda dos vértices à direita de v
	for ( ; i < vert_number-1 && adj_vert[i] != -1; i++)
		adj_vert[i] = adj_vert[i+1];
	//Inserção no indice correcto de v de acordo com a sua prioridade
	for (i = 0; i < vert_number-1 && adj_vert[i] != -1; i++)
		if (path_weight[v] < path_weight[adj_vert[i]])
		{
			for (j = vert_number-1; j > i; j--)
				adj_vert[j] = adj_vert[j-1];
			adj_vert[i] = v;
			break;
		}
	if (adj_vert[i] == -1)
		adj_vert[i] = v;
}

void Graph::RemoveVert(int v)
{
	int i;
	for (i = v; i < vert_number-1 && adj_vert[i] != -1; i++)
		adj_vert[i] = adj_vert[i+1];
	if (i >= 0 && i < vert_number)
		adj_vert[i] = -1;
}

int Graph::PrevVert(int v)
{
	if (v >= 0 && v < vert_number)
		return source_vert[v];
	return -1;
}

float Graph::PathWeight(int v)
{
	if (v >= 0 && v < vert_number)
		return path_weight[v];
	return -1;
}

void Graph::WritePath(int v, int c) {
	Dijkstra(v);
	totalWeight = 0;
	for (int i = 0; i < vert_number; i++) {
		if (i == 0) { 
			printf("\n\n%2d -> ", c + 1); 
			totalWeight += PathWeight(c);
		}
		else if(c != v){
			printf("%2d", PrevVert(c) + 1);
			c = PrevVert(c);
			if (c == v) break;
			else printf(" <-- ");
		}
	}
	printf("\n\nTotal weight: %.2f", totalWeight);
}