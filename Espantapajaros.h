#pragma once
#include"Boton.h"

struct Espantapajaros
{
	float x;
	float y;
	float areaX;
	float areaY;
	float areaWidth;
	float areaHeight;
	ALLEGRO_BITMAP* espantaImagen = al_load_bitmap("Espantapajaros.png");
	bool estado = false;
	Espantapajaros(float X, float Y)
	{
		x = X-10;
		y = Y-3;
		areaX = X - 60;
		areaY = Y - 60;
		areaWidth = 180;
		areaHeight = 180;

	}
	//void crearEspantapajaros()
	//{
		//estado = true;
	//	al_draw_bitmap(espantaImagen, x, y, 0);
	//}

};
