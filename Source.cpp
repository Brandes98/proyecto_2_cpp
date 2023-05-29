/*
#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <fstream>
#include <Windows.h>
#define BlockSize 60
int loadCounterX = 0, loadCounterY = 0, mapSizeX, mapSizeY;
using namespace std;

struct Game {

	int main() {

		if (!al_init()) {
			al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return -1;
		}
		al_install_keyboard();
		al_init_font_addon();
		al_init_ttf_addon();
		al_init_primitives_addon();
		al_init_image_addon();
		int map[100][100];
		LoadMap("mapa.txt", map);
		ALLEGRO_DISPLAY* ventana = al_create_display(800, 600);
		ALLEGRO_FONT* hello_honey = al_load_font("Macaroni.ttf", 20, 0);
		ALLEGRO_COLOR azulElectrico = al_map_rgb(44, 117, 255);
		ALLEGRO_BITMAP* jugador = al_load_bitmap("chester.jpg");
		ALLEGRO_BITMAP* mapeo = al_load_bitmap("tierr3a.png");
		//int ancho = GetSystemMetrics(SM_CXSCREEN);
		//int alto = GetSystemMetrics(SM_CYSCREEN);

		al_set_window_title(ventana, "Mi Juego");
		al_set_window_position(ventana, 800 / 2 - 800 / 2, 800 / 2 - 600 / 2);

		//al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);

		//eventos timer
		ALLEGRO_TIMER* segundoTimer = al_create_timer(1.0);
		ALLEGRO_TIMER* fps = al_create_timer(1.0 / 30);

		ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

		al_register_event_source(event_queue, al_get_timer_event_source(fps));
		al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_display_event_source(ventana));
		al_start_timer(fps);
		al_start_timer(segundoTimer);


		int segundos = 0;
		int fotogramas = 0;
		float y = 0, x = 0, moveSpeed = 60;
		bool done = true;

		//al_draw_rectangle(x, y, x + 20, y + 20, azulElectrico, 2.0);

		while (done)
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			DrawMap(map, mapeo);
			al_draw_bitmap(jugador, x, y, NULL);
			ALLEGRO_EVENT Evento;
			al_wait_for_event(event_queue, &Evento);

			if (Evento.type == ALLEGRO_EVENT_TIMER) {
				if (Evento.timer.source == segundoTimer) {
					segundos++;
				}


			}
			if (Evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				done = false;
			}
			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (Evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_DOWN:
					y += moveSpeed; break;
				case ALLEGRO_KEY_UP:
					y -= moveSpeed; break;
				case ALLEGRO_KEY_RIGHT:
					x += moveSpeed; break;
				case ALLEGRO_KEY_LEFT:
					x -= moveSpeed; break;
				case ALLEGRO_KEY_ESCAPE:
					done = false; break;

				}
				//cout << "no afecta";
			//
			}




			al_draw_text(hello_honey, al_map_rgb(255, 255, 255), 500, 0, NULL, ("Segundos: " + to_string(segundos)).c_str());


			al_flip_display();
		}
		al_destroy_display(ventana);
		al_destroy_timer(segundoTimer);
		al_destroy_event_queue(event_queue);
		return 0;
	}
	void LoadMap(const char* filename, int map[][100])
	{
		std::ifstream openfile(filename);
		if (openfile.is_open())
		{
			openfile >> mapSizeX >> mapSizeY;
			while (!openfile.eof())
			{
				openfile >> map[loadCounterX][loadCounterY];
				loadCounterX++;
				if (loadCounterX >= mapSizeX)
				{
					loadCounterX = 0;
					loadCounterY++;
				}
			}
		}
		else
		{

		}
	}
	void DrawMap(int map[][100], ALLEGRO_BITMAP* mapeo)
	{
		for (int i = 0; i < mapSizeX; i++)
		{
			for (int j = 0; j < mapSizeY; j++)
			{
				if (map[i][j] == 0)
					//al_draw_filled_rectangle(i * BlockSize, j * BlockSize, i * BlockSize + BlockSize, j * BlockSize + BlockSize, al_map_rgb(0, 0, 255));
					al_draw_bitmap(mapeo, BlockSize * i, BlockSize * j, NULL);

			}
		}
	}
};*/