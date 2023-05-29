#pragma once
# include"plantillas.h"
# include <cstring>
struct Mercado
{
	double descuento;
	bool estado = false;
	int productos[5] = { 1,2,3,4,5 };
	
	Boton* listaBotones[5] = { new Boton(),new Boton(),new Boton(),new Boton(),new Boton() };
	ALLEGRO_BITMAP* mercadoImagen = al_load_bitmap("mercado.png");
	ALLEGRO_FONT* letra = al_load_font("Macaroni.ttf", 20, 0);
	float x = 0;
	float y = 600;
	int espantapajaros = 1;
	int identificador = 0;
	void crear(int segundos)
	{
		if (segundos>99 &&  (segundos / 100) % 3 == 0)
		{
			estado = true;
			al_draw_bitmap(mercadoImagen,x,y,0);
			
				
			for (int i = 0; i < 5; i++)
			{
				if (i == 4)
				{
					al_draw_text(letra, al_map_rgb(0, 0, 0), 0, 660 + (23 * (i + 1)), 0, "Producto: EspantaP" );
					
				}
				else {
					al_draw_text(letra, al_map_rgb(0, 0, 0), 0, 660 + (23 * (i + 1)), 0, ("Producto: Arbol " + to_string(i)).c_str());

				}
				listaBotones[i]->x = 200;
				listaBotones[i]->y = (660 + (23 * (i + 1)));
				
			}
		}
		else
		{
			estado = false;
		}
	}
};
