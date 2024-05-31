#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"
#include "popupbox.h"
#include "game.h"
extern highscore Highscore;
//static player players;
static Button namebutton;
char namearray[30];
int n = 0;
player players[30];
player top10players[10];
static void init()
{
    namebutton = button_create(300, 70, 400, 50, "Assets/namebutton.png", "Assets/namebutton_hovered.png");
}
static void on_mouse_move(int a, int mouse_x, int mouse_y, int f)
{
    namebutton.hovered = buttonHover(namebutton, mouse_x, mouse_y);
}
static void on_mouse_down()
{
    if(namebutton.hovered) namebutton.clicked = true;
}
static void draw(void)
{
	FILE *FL = fopen("player.txt", "r");
	if(FL != NULL)
	{
		for(int i=0; i<10; i++)
		{
			fscanf(FL, "%s %d", top10players[i].name, &top10players[i].score);
		}
	}
	fclose(FL);
	char scorestr[10];
	int count = 0;
	for(int i = 0; i < 10; i++)
	{
		if(strlen(top10players[i].name) > 0) sprintf(&scorestr[count], "%d", top10players[i].score);	
		count++;
	}
	
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 20, 83, 0, "Enter your name");
    drawButton(namebutton);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 310 , 83, 0, namearray);
	al_draw_rectangle(40, 200, 300, 650, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 220, 0, top10players[0].name);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 175, 220, 0, &scorestr[0]);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 210, 0, "1");
	al_draw_line(40, 245, 300, 245, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 265, 0, top10players[1].name);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 175, 265, 0, &scorestr[1]);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 255, 0, "2");
	al_draw_line(40, 290, 300, 290, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 310, 0, top10players[2].name);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 175, 310, 0, &scorestr[2]);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 305, 0, "3");
	al_draw_line(40, 335, 300, 335, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 355, 0, top10players[3].name);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 175, 355, 0, &scorestr[3]);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 350, 0, "4");
	al_draw_line(40, 380, 300, 380, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 400, 0, top10players[4].name);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 175, 400, 0, &scorestr[4]);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 395, 0, "5");
	al_draw_line(40, 425, 300, 425, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 445, 0, top10players[5].name);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 440, 0, "6");
	al_draw_line(40, 470, 300, 470, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 490, 0, top10players[6].name);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 485, 0, "7");
	al_draw_line(40, 515, 300, 515, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 535, 0, top10players[7].name);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 530, 0, "8");
	al_draw_line(40, 560, 300, 560, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 580, 0, top10players[8].name);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 575, 0, "9");
	al_draw_line(40, 605, 300, 605, al_map_rgb(0, 0, 0), 8);
	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 625, 0, top10players[9].name);
	al_draw_text(minecraftFont, al_map_rgb(0, 0, 0), 330, 620, 0, "10");
	
	
    //al_draw_text(menuFont, al_map_rgb(0, 0, 0), 400, 83, 0, livescoretext);
	al_draw_text(
		menuFont,
		al_map_rgb(0, 0, 0),
		SCREEN_W/2,
		SCREEN_H - 100,
		ALLEGRO_ALIGN_CENTER,
		"<LCTRL> Back to menu"
	);
}


static void on_key_down(int keycode) {
	if(keycode == 217)
	{
		
		for(int i = 0; i < 30; i++)
		{
			players[0].name[i] = namearray[i];
		}
		players[0].name[n] = '\0';
		if(!namebutton.clicked)
		{
			
			players[0].score = endscore;
			FILE *pfile = fopen("player.txt", "r");
			if(pfile)
			{
				for(int i=1; i<30;i++){
					fscanf(pfile,"%s %d", players[i].name, &players[i].score);
					if(players[i].score==0) break;
				}
				for(int i=0; i<30; i++){
					if(players[i].score==0) break;
					for(int j=i+1; j<30; j++){
						if(players[i].score < players[j].score){
							player temp = players[i];
							players[i]=players[j];
							players[j]=temp;
						}
					}
				}
				fclose(pfile);
			}

			pfile = fopen("player.txt", "w");
			if(pfile){
				for(int i=0; i<30; i++){
					game_log("index here: %s %d\n",players[i].name, players[i].score );
					if(players[i].score==0) break;
					fprintf(pfile,"%s %d\n", players[i].name, players[i].score);
				}
				fclose(pfile);
			}
		}
		game_change_scene(scene_menu_create());
		namearray[0]='\0';
		n=0;
	}
	else if(namebutton.clicked)
	{
		if(keycode == 67)
		{
			namebutton.clicked = false;
		}
		else
		{
			namearray[n++] = keycode - 1 + 'A';	
		}
	}
}


Scene scene_popupbox_create(void) {

	Scene scene;
	
	memset(&scene, 0, sizeof(Scene));
	scene.name = "popupbox";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	//scene.on_mouse_up = &on_mouse_up;
	game_log("popupbox scene created");
	return scene;
}