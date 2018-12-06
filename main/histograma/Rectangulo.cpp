#include "Rectangulo.h"


Rectangulo::Rectangulo(Ponto tl, Ponto br)
{
	topo_esq = tl;
	base_dir = br;
}

Rectangulo::Rectangulo(int x1, int y1, int x2, int y2)
{
	topo_esq = Ponto(x1, y1);
	base_dir = Ponto(x2, y2);
}

void Rectangulo::Desenhar(HWND janelaId, long cor)
{
	Ponto top_right(base_dir.ObterX(), topo_esq.ObterY());
	Ponto bottom_left(base_dir.ObterX(), base_dir.ObterY());
	HDC DrawHDC = GetDC(janelaId);
	HBRUSH hOldBrush;
	HBRUSH hNewBrush;
	hNewBrush = CreateSolidBrush(cor);
	hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
	RECT rect;
	rect.bottom = base_dir.ObterY();
	rect.left = topo_esq.ObterX();
	rect.right = base_dir.ObterX();
	rect.top = topo_esq.ObterY();
	FillRect(DrawHDC, &rect, hNewBrush);
	DeleteObject(SelectObject(DrawHDC, hOldBrush));
	ReleaseDC(janelaId, DrawHDC);
}

bool Rectangulo::Contem(Ponto p)
{
	return ((p.ObterX() >= topo_esq.ObterX()) && (p.ObterX() <= base_dir.ObterX()) && (p.ObterY() >= topo_esq.ObterY()) && (p.ObterY() <= base_dir.ObterY()));
}

bool Rectangulo::Contem(Rectangulo r)
{
	return ((r.topo_esq.ObterX() >= topo_esq.ObterX()) && (r.base_dir.ObterX() <= base_dir.ObterX()) && (r.topo_esq.ObterY() >= topo_esq.ObterY()) && (r.base_dir.ObterY() <= base_dir.ObterY()));
}

double Rectangulo::ObterArea()
{
	return (topo_esq.ObterX() - base_dir.ObterX())*(topo_esq.ObterY() - base_dir.ObterY());
}

int Rectangulo::ObterPerimetro()
{
	return (abs(topo_esq.ObterX() - base_dir.ObterX())) * 2 + (abs(topo_esq.ObterY() - base_dir.ObterY())) * 2;
}
