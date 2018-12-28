#pragma once
#include "Aresta.h"

class Graph
{
private:
	float** adj_mat;
	int	vert_number;
	int edge_number;
	float maxWeight;
	float totalWeight;

	int *source_vert;
	float *path_weight;

	int *adj_vert;

public:
	Graph(int v);
	~Graph();

	void InsertEdge(Aresta e);
	void RemoveEdge(Aresta e);

	void WriteADJ();
	void WriteMinCostPath();

	void Dijkstra(int s);
	void SortVert(int v);
	void RemoveVert(int v);
	bool IsAdjVert(int v);

	int PrevVert(int v);
	float PathWeight(int v);

	int VertNumber() { return vert_number; };

	void WritePath(int v, int c);
};

