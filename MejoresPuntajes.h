#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Mercado.h"
struct Puntaje {
    std::string nombreUsuario;
    int puntaje;
};

bool CompararPorPuntaje(const Puntaje& a, const Puntaje& b) {
    return a.puntaje > b.puntaje;
}

void GuardarPuntaje(const Puntaje& puntaje) {
    std::ofstream archivo("puntajes.txt", std::ios_base::app);

    if (!archivo) {
        al_show_native_message_box(NULL, "Error", "Error", "No se pudo guardar el puntaje.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return;
    }

    archivo << puntaje.nombreUsuario << " " << puntaje.puntaje << std::endl;

    archivo.close();
}

std::vector<Puntaje> CargarPuntajes() {
    std::ifstream archivo("puntajes.txt");
    std::vector<Puntaje> puntajes;

    if (!archivo) {
        al_show_native_message_box(NULL, "Error", "Error", "No se pudo cargar los puntajes.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return puntajes;
    }

    Puntaje puntaje;
    while (archivo >> puntaje.nombreUsuario >> puntaje.puntaje) {
        puntajes.push_back(puntaje);
    }

    archivo.close();

    std::sort(puntajes.begin(), puntajes.end(), CompararPorPuntaje);

    return puntajes;
}
struct mainli {
    int main() {
        ALLEGRO_DISPLAY* display = NULL;
        ALLEGRO_FONT* font = NULL;

        if (!al_init()) {
            al_show_native_message_box(NULL, "Error", "Error", "No se pudo inicializar Allegro.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }

        display = al_create_display(800, 600);
        if (!display) {
            al_show_native_message_box(NULL, "Error", "Error", "No se pudo crear la ventana.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }

        al_init_font_addon();
        al_init_ttf_addon();
        al_install_keyboard();

        font = al_load_font("Macaroni.ttf", 24, 0);
        if (!font) {
            al_show_native_message_box(NULL, "Error", "Error", "No se pudo cargar la fuente.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }

        std::vector<Puntaje> puntajes = CargarPuntajes();
        ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
        al_register_event_source(event_queue, al_get_display_event_source(display));

        // Dibujar los puntajes en la ventana utilizando Allegro 5
       
        bool done = true;
         
              int y = 50;
             /* ALLEGRO_EVENT Evento;
              al_wait_for_event(event_queue, &Evento);
             
              if (Evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
              {
                  done = false;
              }
             // al_clear_to_color(al_map_rgb(0, 0, 0));*/
            for (const auto& puntaje : puntajes) 
            {
                al_draw_textf(font, al_map_rgb(255, 255, 255), 400, y, 0, "%s - %d", puntaje.nombreUsuario.c_str(), puntaje.puntaje);
                y += 30;
            }

            al_flip_display();

           al_rest(5.0);

          
        al_destroy_font(font);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        return 0;
    }

};