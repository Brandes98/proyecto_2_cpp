
#pragma once
#include"ArbolBinario.h"
#include<vector>
#include<thread>
#include<chrono>
using namespace std;

struct Jugador
{
	vector<Espantapajaros> listaEspantapajaros;
	vector<TreeO> listaArbolesBinarios;
	vector<TreeH>	listaArbolesHeap;
	vector<TreeA> listaArbolesAvl;
	vector<TreeF>listaArbolesRojinegros;
	vector<Boton> listaBotones1;
	vector<Boton> listaBotones2;
	vector<Boton> listaBotones3;
	vector<Boton> listaBotones4;
	
	float x = 10.0f;
	float y = 3.0f;
	std::string nombre;
	ALLEGRO_BITMAP * imagen = al_load_bitmap("granjero.png");
	float height = al_get_bitmap_height(imagen);
	float width = al_get_bitmap_width(imagen);
	ALLEGRO_FONT* hello_honey = al_load_font("Super_Comic.ttf", 20, 0);
	float velocidad = 60;
	double money = 10000;
	int limite = 2;
	int ArbolBinario = 1;
	int ArbolHeap = 1;
	int ArbolAvl = 1;
	int ArbolSplay = 1;
	int espantapajaros = 1;
	ALLEGRO_EVENT_QUEUE* cola = al_create_event_queue();
	//---------------------------------------------------//
	float growBI = 2;
	float bufferBI = 1;
	//Espantapajaros* espanta1 = new Espantapajaros(x, y);
	//Espantapajaros* espanta2 = new Espantapajaros(x, y);
	Jugador()
	{
		
	}
	Jugador(string nom)
	{
		nombre = nom;
		
	}

	void moverDerecha()
	{
		x += velocidad;
	}
	void moverAbajo()
	{
		y += velocidad;
	}
	void moverIzquierda()
	{
		x -= velocidad;
	}
	void moverArriba()
	{
		y -= velocidad;
	}
	
	void agregarEspantapajaros()
	{
		if (limite >= listaEspantapajaros.size() && listaEspantapajaros.size()<1)
		{
			listaEspantapajaros.push_back(Espantapajaros(x, y));
		}
		else if (limite >= listaEspantapajaros.size() && listaEspantapajaros.size() >0)
		{
			if (listaEspantapajaros[0].x == (x-10) && listaEspantapajaros[0].y == (y-3))
			{
				//al_show_native_message_box(0, "Lo sentimos", "Celda ocupada", "Selecciona otra celda", 0, ALLEGRO_MESSAGEBOX_WARN);
				cout << "erorr" << endl;
			}
			else 
			{
				listaEspantapajaros.push_back(Espantapajaros(x, y));
			}
		}
	}
	void agregarArbolesBinarios()

	{
		listaArbolesBinarios.push_back(TreeO(x, y));
		listaBotones1.push_back(Boton());
	}

	
	void generarArbolesBinarios()
	{
		

				for ( auto& ArbolesBinarios : listaArbolesBinarios)
				{
					//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
					al_draw_bitmap(ArbolesBinarios.ABImagen, ArbolesBinarios.X, ArbolesBinarios.Y, 0);
					//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				}
			
	}
	void verCantidadFrutosB(bool valor)
	{
		al_draw_text(hello_honey, al_map_rgb(0, 0, 0), 620, 175 , 0,"Arbol-Ubicacion-Cantidad-total-vendidos-perdidos");

		for (int i=0;i<listaArbolesBinarios.size();i++)
		{
			
				std::string text = "| Binario ----" + std::to_string(listaArbolesBinarios[i].X/60) + " " +
					std::to_string(listaArbolesBinarios[i].Y/60) + " --- " +
					std::to_string(listaArbolesBinarios[i].fruit) + " ---------- " +
					std::to_string(listaArbolesBinarios[i].totalMoney) + " ---- " +
					std::to_string(listaArbolesBinarios[i].sold) + " --------- " +
					std::to_string(listaArbolesBinarios[i].miss)+ " |";

				al_draw_text(hello_honey, al_map_rgb(0, 0, 0), 620, 175 + ((i + 1) * 20), 0, text.c_str());
				listaBotones1[i].x = 1400;
				listaBotones1[i].y = 175 + ((i + 1) * 20);
				if(valor==true)
				al_draw_bitmap(listaBotones1[i].botonImagenV, listaBotones1[i].x, listaBotones1[i].y, 0);
				
		}
		for (int j = 0; j < listaArbolesHeap.size(); j++)
		{

			std::string text = "| Heap -------" + std::to_string(listaArbolesHeap[j].X / 60) + " " +
				std::to_string(listaArbolesHeap[j].Y / 60) + " --- " +
				std::to_string(listaArbolesHeap[j].fruit) + " ---------- " +
				std::to_string(listaArbolesHeap[j].totalMoney) + " ---- " +
				std::to_string(listaArbolesHeap[j].sold) + " --------- " +
				std::to_string(listaArbolesHeap[j].miss) + " |";

			al_draw_text(hello_honey, al_map_rgb(0, 0, 0), 620,175+ ((listaArbolesBinarios.size()+ j+1) * 20), 0, text.c_str());
			listaBotones2[j].x = 1400;
			listaBotones2[j].y = 175 + ((listaArbolesBinarios.size() + j + 1) * 20);
			if (valor == true)
			al_draw_bitmap(listaBotones2[j].botonImagenV, listaBotones2[j].x, listaBotones2[j].y, 0);


		}
		for (int k = 0; k < listaArbolesAvl.size(); k++)
		{

			std::string text = "| Avl --------" + std::to_string(listaArbolesAvl[k].X / 60) + " " +
				std::to_string(listaArbolesAvl[k].Y / 60) + " --- " +
				std::to_string(listaArbolesAvl[k].fruit) + " ---------- " +
				std::to_string(listaArbolesAvl[k].totalMoney) + " ---- " +
				std::to_string(listaArbolesAvl[k].sold) + " --------- " +
				std::to_string(listaArbolesAvl[k].miss) + " |";

			al_draw_text(hello_honey, al_map_rgb(0, 0, 0), 620, 165+  ((listaArbolesHeap.size()+k+1) * 40), 0, text.c_str());
			listaBotones3[k].x = 1400;
			listaBotones3[k].y = 165 + ((listaArbolesHeap.size() + k + 1) * 40);
			if (valor == true)
			al_draw_bitmap(listaBotones3[k].botonImagenV, listaBotones3[k].x, listaBotones3[k].y, 0);

		}
		for (int l = 0; l < listaArbolesRojinegros.size(); l++)
		{

			std::string text = "| Rojinegros -" + std::to_string(listaArbolesRojinegros[l].X / 60) + " " +
				std::to_string(listaArbolesRojinegros[l].Y / 60) + " --- " +
				std::to_string(listaArbolesRojinegros[l].fruit) + " ---------- " +
				std::to_string(listaArbolesRojinegros[l].totalMoney) + " ---- " +
				std::to_string(listaArbolesRojinegros[l].sold) + " --------- " +
				std::to_string(listaArbolesRojinegros[l].miss) + " |";

			al_draw_text(hello_honey, al_map_rgb(0, 0, 0), 620,175+ ((listaArbolesAvl.size()+1 +l) * 60), 0, text.c_str());
			listaBotones4[l].x = 1400;
			listaBotones4[l].y = 175 + ((listaArbolesAvl.size() + 1 + l) * 60);
			if (valor == true)
			al_draw_bitmap(listaBotones4[l].botonImagenV, listaBotones4[l].x, listaBotones4[l].y, 0);
		}
		
	}

	void agregarArbolesHeap()
	{
		listaArbolesHeap.push_back(TreeH(x, y));
		listaBotones2.push_back(Boton());
	}
	void generarArbolesHeap()
	{
		for (auto& ArbolesHeap : listaArbolesHeap)
		{
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			al_draw_bitmap(ArbolesHeap.ABImagen, ArbolesHeap.X, ArbolesHeap.Y, 0);
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
	void agregarArbolesAvl()
	{
		listaArbolesAvl.push_back(TreeA(x, y));
		listaBotones3.push_back(Boton());
	}
	void generarArbolesAvl()
	{
		for (auto& ArbolesAvl : listaArbolesAvl)
		{
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			al_draw_bitmap(ArbolesAvl.ABImagen, ArbolesAvl.X, ArbolesAvl.Y, 0);
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
	void agregarArbolesF()
	{
		
		listaArbolesRojinegros.push_back(TreeF(x, y));
		listaBotones4.push_back(Boton());
	}
	void generarArbolesF()
	{
		for (auto& ArbolesF : listaArbolesRojinegros)
		{
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			al_draw_bitmap(ArbolesF.ABImagen, ArbolesF.X, ArbolesF.Y, 0);
			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
	
	void generarEspantapajaros()
	{
		for (const auto& Espantapajaros : listaEspantapajaros)
			al_draw_bitmap(Espantapajaros.espantaImagen, Espantapajaros.x, Espantapajaros.y, 0);
	}
	void inhabilitar()
	{
		for (const auto& Espantapajaros : listaEspantapajaros)
		{

		}
	}
};