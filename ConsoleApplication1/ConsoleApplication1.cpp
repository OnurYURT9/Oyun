#include "pch.h"
#include <iostream>
#include <allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
size_t my_itoa(char *s, unsigned int n)
{
	const unsigned base = 10;
	unsigned digit = n % base;
	size_t i = 0;
	if (n /= base) i += my_itoa(s, n);
	s[i++] = digit + '0';
	return i;
}
int main()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	ALLEGRO_DISPLAY * display = al_create_display(700, 640);
	ALLEGRO_FONT * font = al_load_ttf_font("yazitipi.ttf", 64, 0);		//yazi tipi
	ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();
	double x = 0, y = 0;
	bool done = false;
	bool islem = true;
	double inc_size = 0.3;				//yazi kalinliği
	bool success = false;

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	char message[] = "Beni Tikla    ";
	
	while (!done)
	{
		ALLEGRO_EVENT evt;
		al_wait_for_event_timed(event_queue, &evt, 0.001);				//yazinin akma hizi

		if (evt.type == ALLEGRO_EVENT_DISPLAY_CLOSE) done = true;
		else if (evt.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			//
			//mesaj =  evt.mouse.x;
			//done = t rue;
			int dist_x = evt.mouse.x - x;
			int dist_y = evt.mouse.y - y;
			//my_itoa(mesaj, dist_x);
			if (dist_x > 0 && dist_y > 0)
			{
				if (dist_x < 250 && dist_y < 50)
				{
					char new_message[] = "Basari ile tikladiniz!";
					strcpy_s(message, strlen(new_message) + 1, new_message);
					success = true;
					x = 150;
					y = 250;
				}
			}
		}

		al_clear_to_color(al_map_rgb(255, 255, 255));			//renk kodları
		al_draw_text(font, al_map_rgb(0, 0, 0), x, y, 0, message);
		al_flip_display();

		if (!success)
		{
			if (islem)
			{
				x = x + inc_size;
				y = y + inc_size;
			}
			else
			{
				x = x - inc_size;
				y = y - inc_size;
			}

			if (x < 0) islem = true;
			else if (x > 600) islem = false;
		}
	}

	al_destroy_display(display);
	al_destroy_font(font);
}

