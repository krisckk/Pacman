#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
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
#include "MainCharacter.h"
#include "stageselect.h"
GameScene *Home;
Maincharacter *MC;
bool key_pressed = false;


static void Init(void){
    Home = (GameScene*)malloc(sizeof (GameScene));
    Home -> background = load_bitmap("Assets/Images/Mars.jpg");
    Home -> StageSelectBuilding = load_bitmap("Assets/Images/JapanBuilding.png");
    Home -> StaminaRestoreBuulding = load_bitmap("Assets/Images/StaminaRestoreBuilding.png");
    Home -> EquipementBuilding = load_bitmap("Assets/Images/EquipmentBuilding.png");
    Home -> stageSelect = false;
    Home -> staminaRestore = false;
    Home -> equipement = false;
    MC = MCCreate(); // Initialize the MC object
    if (!MC) {
        // Handle the case where MCCreate fails (e.g., out of memory)
        game_abort("Failed to create MainCharacter object");
    }
    Render_init_screen();
    /*
    GAME_TICK = 0;
	render_init_screen();
	power_up_timer = al_create_timer(1.0f); // 1 tick per second
	if (!power_up_timer)
		game_abort("Error on create timer\n");
    */
	return ;
}

static void Step(void){
    if (MC -> objData.moveCD > 0)
		MC -> objData.moveCD -= MC -> speed;
}


static void Update(void){
    Step();
    MCDraw(MC);
    if(key_pressed) MCMove(MC);
    if (MC -> currentX >= 200 && MC -> currentX <= 600) Home -> stageSelect = true;
    else Home -> stageSelect = false;
    if (MC -> currentX >= 780 && MC -> currentX <= 1280) Home -> staminaRestore = true;
    else Home -> staminaRestore = false;
    if (MC -> currentX >= 1350 && MC -> currentX <= 1750) Home -> equipement = true;
    else Home -> equipement = false;
    
}

static void Draw(void){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(Home -> background, 0, 0, 5250, 3500, 0, 0, SCREEN_W, SCREEN_H, 0);
    al_draw_scaled_bitmap(Home -> StageSelectBuilding, 0, 0, 1200, 1200, 200, 350, 400, 700, 0);
    al_draw_scaled_bitmap(Home -> StaminaRestoreBuulding, 0, 0, 5000, 5000, 780, 320, 400, 700, 0);
    al_draw_scaled_bitmap(Home -> EquipementBuilding, 0, 0, 3250, 3653, 1350, 190, 400, 700, 0);
    if(Home -> stageSelect) {
        al_draw_filled_triangle(MC -> currentX + 200, 950, MC -> currentX + 250, 900, MC -> currentX + 250, 1000, al_map_rgb(255, 255, 255));
        al_draw_filled_rounded_rectangle(MC -> currentX + 250, 850, MC -> currentX + 550, 1050, 10, 10, al_map_rgb(255, 255, 255));
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX + 275, 865, 0, "This is the Stage");
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX + 275, 905, 0, "select building");
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX + 275, 945, 0, "Press ");
        al_draw_text(FFF_Font, al_map_rgb(134, 4, 4), MC -> currentX + 375, 945, 0, "E");
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX + 275, 985, 0, "to enter");
    }
    if(Home -> staminaRestore) {
        al_draw_filled_triangle(MC -> currentX + 200, 950, MC -> currentX + 250, 900, MC -> currentX + 250, 1000, al_map_rgb(255, 255, 255));
        al_draw_filled_rounded_rectangle(MC -> currentX + 250, 850, MC -> currentX + 575, 1050, 10, 10, al_map_rgb(255, 255, 255));
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX + 275, 865, 0, "This is the Stamina");
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX + 275, 905, 0, "restore building");
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX + 275, 945, 0, "Press ");
        al_draw_text(FFF_Font, al_map_rgb(134, 4, 4), MC -> currentX + 375, 945, 0, "E");
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX + 275, 985, 0, "to enter");
    }
    if(Home -> equipement) {
        al_draw_filled_triangle(MC -> currentX - 200, 950, MC -> currentX - 250, 900, MC -> currentX - 250, 1000, al_map_rgb(255, 255, 255));
        al_draw_filled_rounded_rectangle(MC -> currentX - 250, 850, MC -> currentX - 550, 1050, 10, 10, al_map_rgb(255, 255, 255));
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX - 545, 865, 0, "This is the ");
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX - 545, 905, 0, "equipment building");
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX - 545, 945, 0, "Press ");
        al_draw_text(FFF_Font, al_map_rgb(134, 4, 4), MC -> currentX - 445, 945, 0, "E");
        al_draw_text(FFF_Font, al_map_rgb(0, 0, 0), MC -> currentX - 545, 985, 0, "to enter");
    }
    MCDraw(MC);
}

static void Destroy(void){
    al_destroy_bitmap(Home -> background);
    al_destroy_bitmap(Home -> StageSelectBuilding);
    al_destroy_bitmap(Home -> StaminaRestoreBuulding);
    al_destroy_bitmap(Home -> EquipementBuilding);
    MCDestroy(MC);
    //al_destroy_timer(power_up_timer);
}

static void On_key_down(int key_code) {
    if (!key_pressed) {
        switch (key_code) {
            case ALLEGRO_KEY_W:
                MCNextMove(MC, UP);
                key_pressed = true;
                break;
            case ALLEGRO_KEY_A:
                MCNextMove(MC, LEFT);
                key_pressed = true;
                break;
            case ALLEGRO_KEY_S:
                MCNextMove(MC, DOWN);
                key_pressed = true;
                break;
            case ALLEGRO_KEY_D:
                MCNextMove(MC, RIGHT);
                key_pressed = true;
                break;
            default:
                break;
        }
    }
    if (Home -> stageSelect){
        if(key_code == ALLEGRO_KEY_E){
            game_change_scene(scene_stageselect_create());
        }
    }
}

static void On_key_up(int key_code) {
    switch (key_code) {
        case ALLEGRO_KEY_W:
        case ALLEGRO_KEY_A:
        case ALLEGRO_KEY_S:
        case ALLEGRO_KEY_D:
            MCNextMove(MC, NONE);
            break;
        default:
            break;
    }
}

static void Render_init_screen(void){
    al_clear_to_color(al_map_rgb(0, 0, 0));
	MCDraw(MC);
}


Scene scene_home_create(void){
    Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Start";
	scene.initialize = &Init;
	scene.update = &Update;
	scene.draw = &Draw;
	scene.destroy = &Destroy;
	scene.on_key_down = &On_key_down;
    scene.on_key_up = &On_key_up;
	game_log("Start scene created");
	return scene;
}
