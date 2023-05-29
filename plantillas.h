//#pragma once
#include"jugador.h"

struct Cultivo
{
	int x;
	int y;
	bool estado = false;
	ALLEGRO_BITMAP* picture = al_load_bitmap("tierr3a.png");
	float width = al_get_bitmap_width(picture);
	float height = al_get_bitmap_width(picture);
	Cultivo(int X, int Y)
	{
		x = X;
		y = Y;
	}
};