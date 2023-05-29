#pragma once
#include<string>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include <iostream>
#include<thread>
using namespace std;
struct Boton
{
	float x=0;
	float y=0;
	int identificador=0;
	ALLEGRO_BITMAP* botonImagenV = al_load_bitmap("botonVender.png");
	ALLEGRO_BITMAP* botonImagenC = al_load_bitmap("botonComprar.png");
	float height = al_get_bitmap_height(botonImagenV);
	float width = al_get_bitmap_width(botonImagenV);
	Boton(){}
	Boton(float X, float Y)
	{
		x = X;
		y = Y;
		
	}

};