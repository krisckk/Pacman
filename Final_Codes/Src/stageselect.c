#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/events.h>
#include <allegro5/allegro.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Home.h"
#include "game.h"
#include "shared.h"
#include "utility.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "scene_settings.h"
#include "scene_menu_object.h"
#include "MainCharacter.h"
#include "stageselect.h"
StageSelectScene* stageselect;
static Button Firstsong;
static Button Secondsong;
static Button Thirdsong;
static Button Back;
ALLEGRO_EVENT* ev;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
static void Init(void){
	stageselect = (StageSelectScene*)malloc(sizeof(StageSelectScene));
	stageselect -> background = load_bitmap("Assets/Images/stageselectbackground.jpg");
	stageselect -> slidervalue = 0;
	Firstsong = button_create(400 , 200 , 1000, 200, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
	Secondsong = button_create(400, 500 , 1000, 200, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
	Thirdsong = button_create(400, 800 , 1000, 200, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
	Back = button_create(800, 1050, 200, 100, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
}
static void Update(void){
	Draw();
}
static void Draw(void){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_scaled_bitmap(stageselect -> background, 0, 0, 3840, 2160, 0, 0, SCREEN_W, SCREEN_H, 0);
	// Music stage selection
	drawButton(Firstsong);
	drawButton(Secondsong);
	drawButton(Thirdsong);
	drawButton(Back);
	al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 275, ALLEGRO_ALIGN_CENTER, "Unstoppable - Sia");
	al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 575, ALLEGRO_ALIGN_CENTER, "Dance Monkey - Tones and I");
	al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 875, ALLEGRO_ALIGN_CENTER, "Vois sur ton chemin - BENNETT");
	al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 1065, ALLEGRO_ALIGN_CENTER, "Back");
}
static void Destroy(void){
	al_destroy_bitmap(stageselect -> background);
}
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f){
	Firstsong.hovered = buttonHover(Firstsong, mouse_x, mouse_y);
	Secondsong.hovered = buttonHover(Secondsong, mouse_x, mouse_y);
	Thirdsong.hovered = buttonHover(Thirdsong, mouse_x, mouse_y);
	Back.hovered = buttonHover(Back, mouse_x, mouse_y);
}
static void On_mouse_down(){
	if(Firstsong.hovered){
		Firstsong.clicked = true;
		Secondsong.clicked = false;
		Thirdsong.clicked = false;
		Back.clicked = false;
		game_log("you choose first song");
	
	}
	if(Secondsong.hovered){
		Firstsong.clicked = false;
		Secondsong.clicked = true;
		Thirdsong.clicked = false;
		Back.clicked = false;
		game_log("you choose second song");
	}
	if(Thirdsong.hovered){
		Firstsong.clicked = false;
		Secondsong.clicked = false;
		Thirdsong.clicked = true;
		Back.clicked = false;
		game_log("you choose third song");
	}
	if(Back.hovered){
		Firstsong.clicked = false;
		Secondsong.clicked = false;
		Thirdsong.clicked = false;
		Back.clicked = true;
		game_log("you choose back");
		game_change_scene(scene_home_create());
	}
}
static void On_mouse_scroll(int a, int mouse_x, int mouse_y, int dz) {
    stageselect->slidervalue += dz;
    if (stageselect->slidervalue < 0) stageselect->slidervalue = 0;
    if (stageselect->slidervalue > 180) stageselect->slidervalue = 180;
}

static void On_mouse_up(){
	
}

static void On_key_down(int key_code){
	if(key_code == ALLEGRO_KEY_9){
		stageselect -> slidervalue = stageselect -> slidervalue + 5;
		if(stageselect -> slidervalue < 0) stageselect -> slidervalue = 0;
		if(stageselect -> slidervalue > 180) stageselect -> slidervalue = 180;
	}
}

Scene scene_stageselect_create(void){
    Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &Init;
    scene.update = &Update;
	scene.draw = &Draw;
    //scene.destroy = &Destroy;
	scene.on_key_down = &On_key_down;
	scene.on_mouse_move = &On_mouse_move;
	scene.on_mouse_down = &On_mouse_down;
	scene.on_mouse_scroll = &On_mouse_scroll;
	scene.on_mouse_up = &On_mouse_up;
	game_log("Settings scene created");
	return scene;
}