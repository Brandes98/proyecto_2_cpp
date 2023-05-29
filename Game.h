#pragma once
//#include <iostream>
//#include"Mercado.h"
//#include <string>
#include "MejoresPuntajes.h"
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

// Devuelve un número aleatorio en un rango

//#include <allegro5/allegro_timer.h>
#include<thread>
#include<chrono>

//#include <allegro5/allegro_image.h>
#include <vector>
#include <fstream>
#include <Windows.h>
#define BlockSize 60
using namespace chrono;
//int TreeO::contador = 0;
int loadCounterX = 0, loadCounterY = 0, mapSizeX, mapSizeY;
std::vector<std::thread> threads;
vector<ALLEGRO_TIMER*> listaTime;
int posicionesX[10];
int posicionesY[10];
//using namespace std;
struct Sheep
{
	int probability;
	int frecuency;
	int speed;
	int buff;
	int X;
	int Y;
	bool active;
	ALLEGRO_BITMAP* sheepImage;
	float height = 60;
	float width = 59;
	Sheep(int x, int y)
	{
		probability = 90; //appear probability
		frecuency = 120; //when appear
		speed = 90; //how many fruits will eat
		buff = 1;
		X = x;
		Y = y;
		active = false;
		sheepImage = al_load_bitmap("Sheep.png");

	}

};
struct Game {
	string nombreJ;
	vector<Sheep*> listaSheep;
	vector<Crow*> listaCrow;
	vector<Worm*> listaWorm;
	vector<TreeO> listaHAB;
	vector<TreeH> listaHAH;
	vector<TreeA> listaHAA;
	vector<TreeF> listaHAF;
	Game(string name)
	{
		nombreJ = name;
	}
	int main() {

		if (!al_init()) {
			al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return -1;
		}
		

		al_install_keyboard();
		al_init_font_addon();
		al_init_ttf_addon();
		al_init_primitives_addon();
		al_install_mouse();
		al_init_image_addon();
		//--------------------------------------COLORES---------------------------------------//
		ALLEGRO_COLOR azulElectrico = al_map_rgb(44, 117, 255);
		ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
		ALLEGRO_COLOR blanco = al_map_rgb(255,255, 255);
		ALLEGRO_COLOR verde = al_map_rgb(0, 230, 0);
		//------------------------------------------------------------------------------------//
		ALLEGRO_DISPLAY* ventana = al_create_display(1500, 1000);
		ALLEGRO_FONT* hello_honey = al_load_font("Super_Comic.ttf", 20, 0);
		//ALLEGRO_BITMAP* buffer = al_get_backbuffer(ventana);
		//ALLEGRO_COLOR azulElectrico = al_map_rgb(44, 117, 255);

		//ALLEGRO_BITMAP* jugador = al_load_bitmap("chester.jpg");
		ALLEGRO_BITMAP* mapeo = al_load_bitmap("tierr3a.png");
		//int ancho = GetSystemMetrics(SM_CXSCREEN);
		//int alto = GetSystemMetrics(SM_CYSCREEN);

		al_set_window_title(ventana, "Mi Juego");
		al_set_window_position(ventana, 800 / 2 - 800 / 2, 800 / 2 - 600 / 2);

		//al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
		Cultivo* total[10][10];
		Jugador* jugador = new Jugador(nombreJ);
		Mercado* mercado = new Mercado();
		const char* nombreJugador = (jugador->nombre).c_str();

		//------------------------------------------------------//

		int segundos = 0;
		float deltaTime = 0.0f;
		const float FPS = 60.0f;
		int map[100][100];
		LoadMap("mapa.txt", map);
		crearStructurasCultivo(map, total);
		//eventos timer
		ALLEGRO_TIMER* segundoTimer = al_create_timer(1.0);
		ALLEGRO_TIMER* tMercado = al_create_timer(300.0);
		ALLEGRO_TIMER* PFPS = al_create_timer(1.0 / FPS);
		ALLEGRO_TIMER* B = al_create_timer(20.0);
		ALLEGRO_TIMER* H = al_create_timer(35.0);
		ALLEGRO_TIMER* A = al_create_timer(60.0);
		ALLEGRO_TIMER* F = al_create_timer(60.0);
		ALLEGRO_TIMER* ovejaTime = al_create_timer(60.0);
		ALLEGRO_TIMER* cuervoTime = al_create_timer(60.0);
		ALLEGRO_TIMER* gusanoTime = al_create_timer(60.0);
		ALLEGRO_TIMER* dsheep = al_create_timer(90.0);
		ALLEGRO_TIMER* dcraw= al_create_timer(90.0);
		ALLEGRO_TIMER* dworm = al_create_timer(60.0);
		//
		//ALLEGRO_TIMER* fps = al_create_timer(1.0 / 30);

		ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

		//al_register_event_source(event_queue, al_get_timer_event_source(fps));
		al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
		al_register_event_source(event_queue, al_get_timer_event_source(B));
		al_register_event_source(event_queue, al_get_timer_event_source(H));
		al_register_event_source(event_queue, al_get_timer_event_source(A));
		al_register_event_source(event_queue, al_get_timer_event_source(F));
		al_register_event_source(event_queue, al_get_timer_event_source(ovejaTime));
		al_register_event_source(event_queue, al_get_timer_event_source(cuervoTime));
		al_register_event_source(event_queue, al_get_timer_event_source(gusanoTime));
		al_register_event_source(event_queue, al_get_timer_event_source(dsheep));
		al_register_event_source(event_queue, al_get_timer_event_source(dcraw));
		al_register_event_source(event_queue, al_get_timer_event_source(dworm));
		al_register_event_source(event_queue, al_get_timer_event_source(PFPS));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_display_event_source(ventana));
		al_register_event_source(event_queue, al_get_mouse_event_source());
		//al_start_timer(fps);
		al_start_timer(segundoTimer);
		al_start_timer(tMercado);
		al_start_timer(PFPS);
		al_start_timer(B);
		al_start_timer(H);
		al_start_timer(A);
		al_start_timer(ovejaTime);
		al_start_timer(cuervoTime);
		al_start_timer(gusanoTime);
		al_start_timer(dsheep);
		al_start_timer(dcraw);
		al_start_timer(dworm);
		al_start_timer(F);
		
		//int fotogramas = 0;
		//float y = 0, x = 0, moveSpeed = 60;
		bool done = true;
		bool showImage = true;

		//al_draw_rectangle(x, y, x + 20, y + 20, azulElectrico, 2.0);
		bool pausa = true;
		while (done)
		{
			if (pausa)
			{
				
			}
			//al_draw_bitmap(mercado->mercadoImagen, mercado->x, mercado->y, 0);
			ALLEGRO_EVENT Evento;
			al_wait_for_event(event_queue, &Evento);
			int  t = 1;
			if (pausa) {
				al_clear_to_color(verde);

				DrawMap(map, mapeo, total, posicionesX,posicionesY);
			}
			if (Evento.type == ALLEGRO_EVENT_TIMER) {
				//if (listaTime.size() > 0) {
					//cout << "si valido el tamano de listaTime" << endl;
					//for (auto& tiemposB : listaTime) {
						//cout << "Si valida la lista de binarios" << endl;
						if (Evento.timer.source== B)
						{
							cout << "esta leyendo" << endl;
							if (jugador->listaArbolesBinarios.size() > 0)
							{
								cout << "Entro al ciclo de cultivar" << endl;
								for (auto& arboles : jugador->listaArbolesBinarios)
									arboles.growOTree();
							}
						}
					//}
			//	}		
					else if (Evento.timer.source== H)
						{
							cout << "esta leyendo" << endl;
							if (jugador->listaArbolesHeap.size() > 0)
							{
								cout << "Entro al ciclo de cultivar" << endl;
								for (auto& arboles : jugador->listaArbolesHeap) {
									arboles.growHTree();
									arboles.growHTree();
								}
							}
						}
					else if (Evento.timer.source == A)
						{
							cout << "esta leyendo" << endl;
							if (jugador->listaArbolesAvl.size() > 0)
							{
								cout << "Entro al ciclo de cultivar" << endl;
								for (auto& arboles : jugador->listaArbolesAvl)
									arboles.growATree();
							}
					}
					else if (Evento.timer.source == F)
						{
							cout << "esta leyendo" << endl;
							if (jugador->listaArbolesRojinegros.size() > 0)
							{
								cout << "Entro al ciclo de cultivar" << endl;
								for (auto& arboles : jugador->listaArbolesRojinegros) {
									arboles.growFTree();
									arboles.growFTree();
								}
							}
					}
					else if (Evento.timer.source == ovejaTime)
						{
							
							actualizarListaAB(jugador);
							ActualizarListaAH(jugador);
							ActualizarListaAA(jugador);
							ActualizarListaAF(jugador);
							agregarSheep();
						}
					else if (Evento.timer.source == cuervoTime)
						{
							actualizarListaAB(jugador);
							ActualizarListaAH(jugador);
							ActualizarListaAA(jugador);
							ActualizarListaAF(jugador);
							agregarCrow();
						}
					else if (Evento.timer.source == gusanoTime)
						{
							actualizarListaAB(jugador);
							ActualizarListaAH(jugador);
							ActualizarListaAA(jugador);
							ActualizarListaAF(jugador);
							agregarWorm();
						}
					else if (Evento.timer.source == dsheep)
						{
							destruirPorOveja();
						}
					else if (Evento.timer.source == dcraw)
						{
							destruirPorCuervo();
						}

					else if (Evento.timer.source == dworm)
						{
							destruirPorWorm();
						}
					else if (Evento.timer.source == segundoTimer) {
						cout << "si entra a segundos" << endl;
						segundos++;

					}
				
				//else if (Evento.timer.source == tMercado)
				//{
				//	showImage = !showImage;
				//}

			}
			if (Evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				done = false;
			}
			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (Evento.keyboard.keycode == ALLEGRO_KEY_DOWN)
				{
					jugador->moverAbajo();
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_UP)
				{
					jugador->moverArriba();
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_LEFT)
				{
					jugador->moverIzquierda();
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				{
					jugador->moverDerecha();
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				{
					done = false;
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
				{jugador->money -= 20;
					for (int i = 0; i < 10; i++)
						{
							for (int j = 0; j < 10; j++)
							{
								if (checkCollision(jugador, total[i][j]) == true)
								{
									//jugador->generarEspantapajaros();
									if (jugador->espantapajaros > 0)
									{
										jugador->agregarEspantapajaros();
										jugador->espantapajaros--;
										inhability(jugador);
										break;
									}
									
									
									cout << total[i][j]->x << " <- x , y->" << total[i][j]->y << endl;
									
									//std::this_thread::sleep_for(std::chrono::seconds(3));
								}
							}
						}
					
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_5)
				{
					for (int i=0;i<listaSheep.size();i++)
					{
						if (jugador, listaSheep[i])

						{
							listaSheep.erase(listaSheep.begin() + i);
							cout << "Se ha eliminado exitosamente la oveja" << endl;
						}
					}
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_6)
				{
					for (int i = 0; i < listaCrow.size(); i++)
					{
						if (jugador , listaCrow[i])
						{
							listaCrow.erase(listaCrow.begin() + i);
							cout << "se ha eliminado exitosamente el cuervo" << endl;

						}
					}

				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_7)
				{
					for (int i = 0; i < listaWorm.size(); i++)
					{
						if (jugador, listaWorm[i])

						{
							listaWorm.erase(listaWorm.begin() + i);
							cout << "se ha eliminado exitosamente el gusano" << endl;
						}
					}
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_P)
				{
					if (pausa == true)
						pausa = false;
					else
						pausa = true;
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_G)
				{
					guardarPuntajes(jugador);
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_1)
				{
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							if (checkCollision(jugador, total[i][j]) == true)
							{
								//jugador->generarEspantapajaros();
								if (jugador->ArbolBinario > 0) {
									//ALLEGRO_TIMER * s = al_create_timer(20.0);
									//al_start_timer(s);
									
									//listaTime.push_back(s);
									jugador->agregarArbolesBinarios();

									jugador->ArbolBinario-=1 ;
									inhability(jugador);
									break;
								}
								cout << jugador->x<<" " << jugador->y<<endl;
								//cout << total[i][j]->x << " <- x , y->" << total[i][j]->y << endl;

								//std::this_thread::sleep_for(std::chrono::seconds(3));
							}
						}
					}
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_2)
				{
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							if (checkCollision(jugador, total[i][j]) == true)
							{
								//jugador->generarEspantapajaros();
								if (jugador->ArbolHeap > 0)
								{
									jugador->agregarArbolesHeap();
									jugador->ArbolHeap--;
									inhabilityH(jugador);
									break;
								}
								cout << jugador->x << " " << jugador->y << endl;
								//cout << total[i][j]->x << " <- x , y->" << total[i][j]->y << endl;

								//std::this_thread::sleep_for(std::chrono::seconds(3));
							}
						}
					}
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_3)
				{
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							if (checkCollision(jugador, total[i][j]) == true)
							{
								//jugador->generarEspantapajaros();
								if (jugador->ArbolAvl > 0)
								{
									jugador->agregarArbolesAvl();
									jugador->ArbolAvl--;
									inhabilityA(jugador);
									break;
								}
								cout << jugador->x << " " << jugador->y << endl;
								//cout << total[i][j]->x << " <- x , y->" << total[i][j]->y << endl;

								//std::this_thread::sleep_for(std::chrono::seconds(3));
							}
						}
					}
				}
				else if (Evento.keyboard.keycode == ALLEGRO_KEY_4)
				{
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 10; j++)
						{
							if (checkCollision(jugador, total[i][j]) == true)
							{
								if (jugador->ArbolSplay > 0)
								{


									jugador->agregarArbolesF();
									jugador->ArbolSplay--;
									inhabilityF(jugador);
									break;
								}
								cout << jugador->x << " " << jugador->y << endl;
								//cout << total[i][j]->x << " <- x , y->" << total[i][j]->y << endl;

								//std::this_thread::sleep_for(std::chrono::seconds(3));
							}
						}
					}
				}
			}
			if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				int Mx = Evento.mouse.x;
				int My = Evento.mouse.y;
				
				if (Evento.mouse.button & 1)
				{
					if (checkCollisionBotonesVender(Mx, My, jugador))
					{
						
					}
					for (int i=0;i<5;i++)
					if (checkCollisionBotonesMercado(Mx, My, mercado->listaBotones[i]))
					{
						switch (i)
						{
						case 0:

							
							if (jugador->money >= 100)
						
								{
									jugador->money = jugador->money - 100;
									jugador->ArbolBinario = jugador->ArbolBinario+ 1;
								}
								break;
							case 1:
								
								if (jugador->money >= 130)
								{
									jugador->money = jugador->money - 130;
									jugador->ArbolHeap = jugador->ArbolHeap+ 1;
								}
								break;
							case 2:
								
								if (jugador->money >= 360)
								{
									jugador->money = jugador->money - 360;
									jugador->ArbolAvl = jugador->ArbolAvl+ 1;
								}
								break;
							case 3:
								
								if (jugador->money >= 600)
								{
									//std::this_thread::sleep_for(std::chrono::milliseconds(20000));
									jugador->money = jugador->money - 600;
									jugador->ArbolSplay = jugador->ArbolSplay+1;
								}
								break;
							default:
								if (jugador->money >= 200 && jugador->espantapajaros<2)

								{
									jugador->espantapajaros++;
									jugador->money -= 200;
								}
									break;
								
						}
					}

				}
			}
			
				
				if (pausa) {
					
					dibujarTierra(total);
					jugador->generarArbolesBinarios();
					jugador->generarArbolesHeap();
					jugador->generarArbolesAvl();
					jugador->generarArbolesF();
					jugador->generarEspantapajaros();
					mercado->crear(segundos);
					al_draw_bitmap(jugador->imagen, jugador->x, jugador->y, NULL);
					if (mercado->estado)
					{
						for (int i = 0; i < 5; i++)
						{
							al_draw_bitmap(mercado->listaBotones[i]->botonImagenC, mercado->listaBotones[i]->x, mercado->listaBotones[i]->y, 0);
						}
					}
					//jugador->generarEspantapajaros1();

					al_draw_text(hello_honey, negro, 620, 0, NULL, ("Segundos: " + to_string(segundos)).c_str());
					al_draw_text(hello_honey, negro, 620, 40, 0, ("Dinero: " + to_string(jugador->money)).c_str());
					al_draw_text(hello_honey, negro, 620, 20, NULL, "Nombre: ");
					al_draw_text(hello_honey, negro, 620, 65, 0, ("Cantidad sin plantar B: " + to_string(jugador->ArbolBinario)).c_str());
					al_draw_text(hello_honey, negro, 620, 85, 0, ("Cantidad sin plantar H: " + to_string(jugador->ArbolHeap)).c_str());
					al_draw_text(hello_honey, negro, 620, 105, 0, ("Cantidad sin plantar A: " + to_string(jugador->ArbolAvl)).c_str());
					al_draw_text(hello_honey, negro, 620, 125, 0, ("Cantidad sin plantar S: " + to_string(jugador->ArbolSplay)).c_str());
					al_draw_text(hello_honey, negro, 620, 145, 0, ("Cantidad sin poner EP: " + to_string(jugador->espantapajaros)).c_str());
					jugador->verCantidadFrutosB(mercado->estado);
					generarSheep();
					generarCrow();
					generarWorm();
					al_draw_text(hello_honey, negro, 740, 20, NULL, nombreJugador);
					al_flip_display();
				}
			}
		
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				al_destroy_bitmap(total[i][j]->picture);
			}
		}
		destruirArbolesBinarios(jugador);
		destruirBotonesMercado(mercado);
		al_destroy_display(ventana);
		al_destroy_timer(segundoTimer);
		al_destroy_bitmap(jugador->imagen);
		al_destroy_bitmap(mercado->mercadoImagen);
		destruirOvejas();
		destruirCuervos();
		destruirWorm();
		al_destroy_timer(PFPS);
		al_destroy_timer(B);
		al_destroy_timer(H);
		al_destroy_timer(A);
		al_destroy_timer(F);
		al_destroy_timer(ovejaTime);
		al_destroy_timer(cuervoTime);
		al_destroy_timer(gusanoTime);
		//al_destroy_bitmap(buffer);
		al_destroy_event_queue(event_queue);
		

		return 0;
	}
//----------------------------------CARGAR MAPA------------------------------------//
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
//-----------------------------------Dibujar Mapa, tierra--------------------------------------------------//

	void DrawMap(int map[][100], ALLEGRO_BITMAP* mapeo, Cultivo* cultivado[][10],int posicionesX[10],int posicionesY[10])
	{
		for (int i = 0; i < mapSizeX; i++)
		{
			for (int j = 0; j < mapSizeY; j++)
			{
				if (map[i][j] == 0) {
					//al_draw_filled_rectangle(i * BlockSize, j * BlockSize, i * BlockSize + BlockSize, j * BlockSize + BlockSize, al_map_rgb(0, 0, 255));
					//cultivado[i][j] = new Cultivo(i*BlockSize, j*BlockSize);
					//cultivado[i][j]->x = cultivado[i][j]->x * BlockSize;
					//cultivado[i][j]->y = cultivado[i][j]->y * BlockSize;
					posicionesX[i] = BlockSize * i;
					posicionesY[j] = BlockSize * j;
					
					al_draw_bitmap(mapeo, BlockSize * i, BlockSize * j, NULL);
					//al_draw_bitmap(mapeo, cultivado[i][j]->x, cultivado[i][j]->y,NULL);
				}
			}
		}
	}
	void crearStructurasCultivo(int map[][100], Cultivo* cultivado[][10])
	{
		for (int i = 0; i < mapSizeX; i++)
		{
			for (int j = 0; j < mapSizeY; j++)
			{
				if (map[i][j] == 0) {
					cultivado[i][j] = new Cultivo(i * BlockSize, j * BlockSize);

				}
			}
		}
	}
	void dibujarTierra(Cultivo* total[][10])
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				//cout << "este es x" << total[i][j]->x <<"este es y" << total[i][j]->y << endl;
				al_draw_bitmap(total[i][j]->picture, total[i][j]->x, total[i][j]->y, 0);
				//cout << total[i][j]->x << total[i][j]->y << endl;
				//cout << "Esto es x "<<total[i][j]->x << "Esto es y"<<total[i][j]->y << endl;
			}
		}

	}
	
//--------------------------------Destruir Para liberar memoria siglas(DPLM)-------------------------------------//
	void destruirArbolesBinarios(Jugador * jugador)
	{
		for (const auto ArbolesBinarios : jugador->listaArbolesBinarios)
			al_destroy_bitmap(ArbolesBinarios.ABImagen);
   }
	void destruirBotonesMercado(Mercado* mercado)
	{
		for (const auto Boton : mercado->listaBotones)
			al_destroy_bitmap(Boton->botonImagenV);
	}
	void destruirOvejas()
	{
		for (const auto sheep : listaSheep)
			al_destroy_bitmap(sheep->sheepImage);
	}
	void destruirCuervos()
	{
		for (const auto sheep : listaCrow)
			al_destroy_bitmap(sheep->crowImage);
	}
	void destruirWorm()
	{
		for (const auto sheep : listaWorm)
			al_destroy_bitmap(sheep->crowImage);
	}
//-------------------------------------Colisiones----------------------------------------------------------------//
	bool checkCollsion_Sheep(Jugador* jugador, Sheep * cultivo)
	{

		if (jugador->x + jugador->width >= cultivo->X &&
			jugador->x <= cultivo->X + cultivo->width &&
			jugador->y + cultivo->height >= cultivo->Y &&
			jugador->y <= cultivo->Y + cultivo->height) {
			cout << "Esto es el grosor del cultivo " << cultivo->width << endl;
			cout << "Esto es la altura del cultivo " << cultivo->height << endl;
			return true; // Colisión detectada
		}
		return false; // No hay colisión
	}
	bool checkCollsion_Crow(Jugador* jugador, Crow* cultivo)
	{

		if (jugador->x + jugador->width >= cultivo->X &&
			jugador->x <= cultivo->X + cultivo->width &&
			jugador->y + cultivo->height >= cultivo->Y &&
			jugador->y <= cultivo->Y + cultivo->height) {
			cout << "Esto es el grosor del cultivo " << cultivo->width << endl;
			cout << "Esto es la altura del cultivo " << cultivo->height << endl;
			return true; // Colisión detectada
		}
		return false; // No hay colisión
	}
	bool checkCollsion_Worm(Jugador* jugador, Worm * cultivo)
	{

		if (jugador->x + jugador->width >= cultivo->X &&
			jugador->x <= cultivo->X + cultivo->width &&
			jugador->y + cultivo->height >= cultivo->Y &&
			jugador->y <= cultivo->Y + cultivo->height) {
			cout << "Esto es el grosor del cultivo " << cultivo->width << endl;
			cout << "Esto es la altura del cultivo " << cultivo->height << endl;
			return true; // Colisión detectada
		}
		return false; // No hay colisión
	}
	bool checkCollision(Jugador * jugador,Cultivo * cultivo) {
		if (jugador->x + jugador->width >= cultivo->x &&
			jugador->x <= cultivo->x + cultivo->width &&
			jugador->y + cultivo->height >= cultivo->y &&
			jugador->y <= cultivo->y + cultivo->height) {
			cout << "Esto es el grosor del cultivo " << cultivo->width << endl;
			cout << "Esto es la altura del cultivo " << cultivo->height << endl;
			return true; // Colisión detectada
		}
		return false; // No hay colisión
	}
	bool checkCollisionBotonesMercado(int x, int y, Boton* lista)
	{
		
		
		if (x >= lista->x && x <= (lista->x + lista->width) &&
			y >= lista->y && y <= (lista->y + lista->height)) {
			return true; // Colisión detectada
		}

			return false; // No hay colisión
		
	}
	bool checkCollisionBotonesVender(int x, int y, Jugador* jugador)
	{

		for(int i=0;i<jugador->listaBotones1.size();i++)
		if (x >= jugador->listaBotones1[i].x && x <= (jugador->listaBotones1[i].x + jugador->listaBotones1[i].width) &&
			y >= jugador->listaBotones1[i].y && y <= (jugador->listaBotones1[i].y + jugador->listaBotones1[i].height)) {
			jugador->listaArbolesBinarios[i].sold++;
			jugador->listaArbolesBinarios[i].fruit--;
			jugador->money+=jugador->listaArbolesBinarios[i].root->data;

			jugador->listaArbolesBinarios[i].remove();
			return true; // Colisión detectada
		}

		for (int j = 0; j < jugador->listaBotones2.size(); j++)
			if (x >= jugador->listaBotones2[j].x && x <= (jugador->listaBotones2[j].x + jugador->listaBotones2[j].width) &&
				y >= jugador->listaBotones2[j].y && y <= (jugador->listaBotones2[j].y + jugador->listaBotones2[j].height)) {
				jugador->listaArbolesHeap[j].sold++;
				jugador->money += jugador->listaArbolesHeap[j].heap[0]->data;
				jugador->listaArbolesHeap[j].fruit--;
				jugador->listaArbolesHeap[j].removeRoot();
				return true; // Colisión detectada
			}
		for (int k = 0; k < jugador->listaBotones3.size(); k++)
			if (x >= jugador->listaBotones3[k].x && x <= (jugador->listaBotones3[k].x + jugador->listaBotones3[k].width) &&
				y >= jugador->listaBotones3[k].y && y <= (jugador->listaBotones3[k].y + jugador->listaBotones3[k].height)) {
				jugador->listaArbolesAvl[k].sold++;
				jugador->listaArbolesAvl[k].fruit--;
				jugador->money += jugador->listaArbolesAvl[k].root->data;
				jugador->listaArbolesAvl[k].remove();
				return true; // Colisión detectada
			}
		for (int l = 0; l < jugador->listaBotones4.size(); l++)
			if (x >= jugador->listaBotones4[l].x && x <= (jugador->listaBotones4[l].x + jugador->listaBotones4[l].width) &&
				y >= jugador->listaBotones4[l].y && y <= (jugador->listaBotones4[l].y + jugador->listaBotones4[l].height)) {
				jugador->listaArbolesRojinegros[l].sold++;
				jugador->money += jugador->listaArbolesRojinegros[l].root->data;
				jugador->listaArbolesRojinegros[l].fruit--;
				jugador->listaArbolesRojinegros[l].remove();
				return true; // Colisión detectada
			}

		return false; // No hay colisión

	}

	//-----------------------Inhabilitadores -----------------------------------------------//
	void inhability(Jugador * jugador)
	{
		auto listaAB = jugador->listaArbolesBinarios;
		if (jugador->listaEspantapajaros.size() > 0)
		{
			for (const auto& Espantapajaros : jugador->listaEspantapajaros)
			{
				for (int i = 0; i < listaAB.size(); i++)
				{
					
						if ((Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y == listaAB[i].Y) ||
							(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y == listaAB[i].Y) ||
							(Espantapajaros.x == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
							(Espantapajaros.x == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
							(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
							(Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
							(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
							(Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y)||
							(Espantapajaros.x  == listaAB[i].X && Espantapajaros.y == listaAB[i].Y))
						{
							listaAB[i].estado= true;

							cout << "Si lo invalido: "<< listaAB[i].estado<< "pos"<<i << endl;
						}
						//al_draw_bitmap(total[i][j]->picture, total[i][j]->x, total[i][j]->y, 0);
						//cout << "Esto es x "<<total[i][j]->x << "Esto es y"<<total[i][j]->y << endl;
					
				}
			}
		}
	}
	void inhabilityH(Jugador * jugador)
	{
		auto listaAB = jugador->listaArbolesHeap;
		if (jugador->listaEspantapajaros.size() > 0)
		{
			for (const auto& Espantapajaros : jugador->listaEspantapajaros)
			{
				for (int i = 0; i < listaAB.size(); i++)
				{

					if ((Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y == listaAB[i].Y) ||
						(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y == listaAB[i].Y) ||
						(Espantapajaros.x == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
						(Espantapajaros.x == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
						(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
						(Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
						(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
						(Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
						(Espantapajaros.x == listaAB[i].X && Espantapajaros.y == listaAB[i].Y))
					{
						listaAB[i].estado = true;

						cout << "Si lo invalido: " << listaAB[i].estado << "pos" << i << endl;
					}
					//al_draw_bitmap(total[i][j]->picture, total[i][j]->x, total[i][j]->y, 0);
					//cout << "Esto es x "<<total[i][j]->x << "Esto es y"<<total[i][j]->y << endl;

				}
			}
		}

	}
	void inhabilityA(Jugador* jugador)
	{
		auto listaAB = jugador->listaArbolesAvl;
		if (jugador->listaEspantapajaros.size() > 0)
		{
			for (const auto& Espantapajaros : jugador->listaEspantapajaros)
			{
				for (int i = 0; i < listaAB.size(); i++)
				{

					if ((Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y == listaAB[i].Y) ||
						(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y == listaAB[i].Y) ||
						(Espantapajaros.x == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
						(Espantapajaros.x == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
						(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
						(Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
						(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
						(Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
						(Espantapajaros.x == listaAB[i].X && Espantapajaros.y == listaAB[i].Y))
					{
						listaAB[i].estado = true;

						cout << "Si lo invalido: " << listaAB[i].estado << "pos" << i << endl;
					}
					//al_draw_bitmap(total[i][j]->picture, total[i][j]->x, total[i][j]->y, 0);
					//cout << "Esto es x "<<total[i][j]->x << "Esto es y"<<total[i][j]->y << endl;

				}
			}
		}
	}
	void inhabilityF(Jugador* jugador)
	{
		auto listaAB = jugador->listaArbolesRojinegros;
		if (jugador->listaEspantapajaros.size() > 0)
		{
			for (const auto& Espantapajaros : jugador->listaEspantapajaros)
			{
				for (int i = 0; i < listaAB.size(); i++)
				{

					if ((Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y == listaAB[i].Y) ||
						(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y == listaAB[i].Y) ||
						(Espantapajaros.x == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
						(Espantapajaros.x == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
						(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
						(Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
						(Espantapajaros.x - 60 == listaAB[i].X && Espantapajaros.y + 60 == listaAB[i].Y) ||
						(Espantapajaros.x + 60 == listaAB[i].X && Espantapajaros.y - 60 == listaAB[i].Y) ||
						(Espantapajaros.x == listaAB[i].X && Espantapajaros.y == listaAB[i].Y))
					{
						listaAB[i].estado = true;

						cout << "Si lo invalido: " << listaAB[i].estado << "pos" << i << endl;
					}
					//al_draw_bitmap(total[i][j]->picture, total[i][j]->x, total[i][j]->y, 0);
					//cout << "Esto es x "<<total[i][j]->x << "Esto es y"<<total[i][j]->y << endl;

				}
			}
		}
	}
	//---------------------------------Metodos de guardar y cargar puntaje-------------------------------------//
	void guardarPuntajes(Jugador* jugador)
	{
		std::ofstream archivo("puntajes.txt", std::ios_base::app); // Abre el archivo en modo adjunto (append)

		if (!archivo) {
			std::cout << "No se pudo guardar el puntaje." << std::endl;
			return;
		}

		archivo << jugador->nombre << " " << jugador->money << std::endl;

		archivo.close();
	}
	//-------------------------------- enlistar npcs---------------------------------//
	void agregarSheep()
	{
		if (listaHAB.size() > 0 || listaHAH.size() > 0 || listaHAA.size() > 0 || listaHAF.size() > 0) {
			int x;
			int y;
			int validacione = validacion();
			if (validacione >= 40)
			{
				cout << "libre " << endl;
				int z = 0;
				bool done = false;
				int aleatorio = generar_aleatorio_lista(0, 3);
				cout << "aleatorio: " <<aleatorio<< endl;
				if (aleatorio == 0 && listaHAB.size() > 0) {
					int i = generar_aleatorio_lista(0, listaHAB.size() - 1);
					cout << "aleatorio: " << i << endl;
					x = listaHAB[i].X;
					y = listaHAB[i].Y;
					listaSheep.push_back(new Sheep(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
				else if (aleatorio == 1 && listaHAH.size() > 0) {
					int i = generar_aleatorio_lista(0, listaHAH.size() - 1);
					x = listaHAH[i].X;
					y = listaHAH[i].Y;
					listaSheep.push_back(new Sheep(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
				else if (aleatorio == 2 && listaHAA.size() > 0) {
					int i = generar_aleatorio_lista(0, listaHAA.size() - 1);
					x = listaHAA[i].X;
					y = listaHAA[i].Y;
					listaSheep.push_back(new Sheep(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
				else if (aleatorio == 3 && listaHAF.size() > 0) {
					int i = generar_aleatorio_lista(0, listaHAF.size() - 1);
					x = listaHAF[i].X;
					y = listaHAF[i].Y;
					listaSheep.push_back(new Sheep(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
			}
		}
	}
	void agregarCrow()
	{
		if (listaHAB.size() > 0 || listaHAH.size() > 0 || listaHAA.size() > 0 || listaHAF.size() > 0) {
			int x;
			int y;
			int validacione = validacion();
			if (validacione >= 40)
			{
				cout << "libre " << endl;
				int z = 0;
				bool done = false;
				int aleatorio = generar_aleatorio_lista(0, 3);
				if (aleatorio == 0 && listaHAB.size() > 0) {
					int i = generar_aleatorio_lista(0, listaHAB.size() - 1);
					x = listaHAB[i].X;
					y = listaHAB[i].Y;
					listaCrow.push_back(new Crow(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
				if (aleatorio == 1 && listaHAH.size() > 0) {
					int i = generar_aleatorio_lista(0, listaHAH.size() - 1);
					x = listaHAH[i].X;
					y = listaHAH[i].Y;
					listaCrow.push_back(new Crow(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
				if (aleatorio == 2 && listaHAA.size() > 0) {
					int i = generar_aleatorio_lista(0, listaHAA.size() - 1);
					x = listaHAA[i].X;
					y = listaHAA[i].Y;
					listaCrow.push_back(new Crow(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
				if (aleatorio == 3 && listaHAF.size() > 0) {
					int i = generar_aleatorio_lista(0, listaHAF.size() - 1);
					x = listaHAF[i].X;
					y = listaHAF[i].Y;
					listaCrow.push_back(new Crow(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
			}
		}
	}
	void agregarWorm()
	{
		if (listaHAB.size() > 0||listaHAH.size()>0||listaHAA.size()>0||listaHAF.size()>0) {
			int x;
			int y;
			int validacione = validacion();
			if (validacione >= 70)
			{
				cout << "libre " << endl;
				int z = 0;
				bool done = false;
				int aleatorio = generar_aleatorio_lista(0, 3);
				if (aleatorio == 0 && listaHAB.size()>0) {
					int i = generar_aleatorio_lista(0, listaHAB.size() - 1);
					x = listaHAB[i].X;
					y = listaHAB[i].Y;
					listaWorm.push_back(new Worm(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
				if (aleatorio == 1 && listaHAH.size()>0) {
					int i = generar_aleatorio_lista(0, listaHAH.size() - 1);
					x = listaHAH[i].X;
					y = listaHAH[i].Y;
					listaWorm.push_back(new Worm(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
				if (aleatorio == 2 && listaHAA.size()>0) {
					int i = generar_aleatorio_lista(0, listaHAA.size() - 1);
					x = listaHAA[i].X;
					y = listaHAA[i].Y;
					listaWorm.push_back(new Worm(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
				if (aleatorio == 3 && listaHAF.size()>0) {
					int i = generar_aleatorio_lista(0, listaHAF.size() - 1);
					x = listaHAF[i].X;
					y = listaHAF[i].Y;
					listaWorm.push_back(new Worm(x, y));
					cout << "si agrego el gusano: " << "posicion: " << x << y << endl;
				}
			}
		}
	}
	//--------------------------generar npcs-----------------------------------------------//
	void generarSheep()
	{
		for (const auto sheeps : listaSheep)
		{
			al_draw_bitmap(sheeps->sheepImage, sheeps->X, sheeps->Y, 0);
		}
	}
	void generarCrow()
	{
		for (const auto sheeps : listaCrow)
		{
			al_draw_bitmap(sheeps->crowImage, sheeps->X, sheeps->Y, 0);
		}
	}
	void generarWorm()
	{
		for (const auto sheeps : listaWorm)
		{
			al_draw_bitmap(sheeps->crowImage, sheeps->X, sheeps->Y, 0);
		}
	}
	int validacion()
	{
		int probabilidad = randgen();
		return probabilidad;
	}
	int generar_aleatorio_lista(int minimo, int maximo) {
		return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
	}
//------------------------------Destruir manzanas y arboles-----------------------------//
	void destruirPorOveja()
	{
		for (const auto& sheeps : listaSheep) {
			for (auto arboles : listaHAB)
			{
				if (sheeps->X == arboles.X && sheeps->Y == arboles.Y)
					if (arboles.fruit > 0) {
						arboles.totalMoney -= arboles.root->data;
						arboles.miss++;
						arboles.fruit--;
						arboles.remove();
					}
			}
			for (auto arboles : listaHAH)
			{
				if (sheeps->X == arboles.X && sheeps->Y == arboles.Y)
					if (arboles.fruit > 0) 
					{
						arboles.miss++;
						arboles.fruit--;
						arboles.removeRoot();
					}
			}
			for (auto arboles : listaHAA)
			{
				if (sheeps->X == arboles.X && sheeps->Y == arboles.Y)
					if (arboles.fruit > 0) {
						arboles.totalMoney -= arboles.root->data;
						arboles.miss++;
						arboles.fruit--;
						arboles.remove();
					}
			}
			for (auto arboles : listaHAF)
			{
				if (sheeps->X == arboles.X && sheeps->Y == arboles.Y)
					if (arboles.fruit > 0) {
						arboles.totalMoney -= arboles.root->data;
						arboles.miss++;
						arboles.fruit--;
						arboles.remove();
					}
			}
		}
}
	void destruirPorCuervo()
	{
		for (const auto& sheeps : listaCrow) {
			for (auto arboles : listaHAB)
			{
				if (sheeps->X == arboles.X && sheeps->Y == arboles.Y)
					if (arboles.fruit > 0) {
						arboles.totalMoney-=arboles.root->data;
						arboles.miss++;
						arboles.fruit--;
						arboles.remove();

					}
			}
			for (auto arboles : listaHAH)
			{
				if (sheeps->X == arboles.X && sheeps->Y == arboles.Y)
					if (arboles.fruit > 0) {
						//arboles.totalMoney -= arboles.heap.data();
						arboles.removeRoot();
						arboles.fruit--;
						arboles.miss++;
					}
			}
			for (auto arboles : listaHAA)
			{
				if (sheeps->X == arboles.X && sheeps->Y == arboles.Y)
					if (arboles.fruit > 0) {
						arboles.totalMoney -= arboles.root->data;
						arboles.miss++;
						arboles.fruit--;
						arboles.remove();
					}
			}
			for (auto arboles : listaHAF)
			{
				if (sheeps->X == arboles.X && sheeps->Y == arboles.Y)
					if (arboles.fruit > 0) {
						arboles.totalMoney -= arboles.root->data;
						arboles.miss++;
						arboles.fruit--;
						arboles.remove();
					}
			}
		}
	}
	void destruirPorWorm()
	{
		for (int i = 0; i < listaWorm.size(); i++) {
			if(listaHAB.size()>0)
			for (int j = 0; j < listaHAB.size(); j++)
			{
				if (listaWorm[i]->X == listaHAB[j].X && listaWorm[i]->Y == listaHAB[j].Y)
					listaHAB.erase(listaHAB.begin() + j);
			}
			else if(listaHAH.size()>0)
			for (int K = 0; K < listaHAH.size(); K++)
			{
				if (listaWorm[i]->X == listaHAH[K].X && listaWorm[i]->Y == listaHAH[K].Y)
					listaHAH.erase(listaHAH.begin() + K);
			}
			else if(listaHAA.size()>0)
			for (int m = 0; m< listaHAA.size(); m++)
			{
				if (listaWorm[i]->X == listaHAA[m].X && listaWorm[i]->Y == listaHAA[m].Y)
					listaHAA.erase(listaHAA.begin() + m);
			}
			else if(listaHAF.size()>0)
			for (int n = 0; n < listaHAF.size(); n++)
			{
				if (listaWorm[i]->X == listaHAF[n].X && listaWorm[i]->Y == listaHAF[n].Y)
					listaHAF.erase(listaHAF.begin() + n);
			}
		}
	}
//-----------------------------Actualizar listas----------------------------------------//
	void actualizarListaAB(Jugador * jugador)
	{
		for (auto& ArbolesBinarios :jugador-> listaArbolesBinarios)
		{
			listaHAB.clear();
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			if (ArbolesBinarios.estado == false)
				listaHAB.push_back(ArbolesBinarios);
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
	void ActualizarListaAH(Jugador* jugador)
	{
		for (auto& ArbolesBinarios : jugador->listaArbolesHeap)
		{
			listaHAH.clear();
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			if (ArbolesBinarios.estado== false)
				listaHAH.push_back(ArbolesBinarios);
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
	void ActualizarListaAA(Jugador* jugador)
	{
		for (auto& ArbolesBinarios : jugador->listaArbolesAvl)
		{
			listaHAA.clear();
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			if (ArbolesBinarios.estado == false)
				listaHAA.push_back(ArbolesBinarios);
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
	void ActualizarListaAF(Jugador* jugador)
	{
		for (auto& ArbolesBinarios : jugador->listaArbolesRojinegros)
		{
			listaHAF.clear();
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			if (ArbolesBinarios.estado == false)
				listaHAF.push_back(ArbolesBinarios);
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
//------------------------------------------------------------------------------------//
	int validaX()
	{ 

		int counter = 0;
		while (true) 
		{ 
			int i = generar_aleatorio_lista(0, listaHAB.size() - 1);

			int x = listaHAB[i].X;

			for (const auto& ovejas : listaSheep)
			{
				if (ovejas->X != x)
					counter++;
			}
			if (counter == listaHAB.size())
			{
				return x;
			}
			else {
				
			}

		}
		
	}
	int validaY()
	{
		int counter = 0;
		while (true) {
			int i = generar_aleatorio_lista(0, listaHAB.size() - 1);

			int y = listaHAB[i].Y;

			for (const auto& ovejas : listaSheep)
			{
				if (ovejas->Y != y)
					counter++;
			}
			if (counter == listaHAB.size())
			{
				return y;
			}
			else {
				int i = generar_aleatorio_lista(0, listaHAB.size() - 1);

				int y = listaHAB[i].Y;
			}
		}
	}
};