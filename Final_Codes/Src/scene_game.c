#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "shared.h"
#include "utility.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "pacman_obj.h"
#include "scene_settings.h"
#include "ghost.h"
#include "map.h"
#include "popupbox.h"



// TODO-HACKATHON 2-0: Create one ghost
// Just modify the GHOST_NUM to 1
#define GHOST_NUM 4// ghost number 4 
// TODO-GC-ghost: create a least FOUR ghost!
/* global variables*/
extern const uint32_t GAME_TICK_CD;
extern uint32_t GAME_TICK;
extern ALLEGRO_TIMER* game_tick_timer;
int game_main_Score = 0;
bool game_over = false;

/* Internal variables*/
static ALLEGRO_TIMER* power_up_timer;
static const int power_up_duration = 9;
static Pacman* pman;

static Map* basic_map;
static Ghost** ghosts;
bool debug_mode = false;
bool cheat_mode = false;

extern highscore Highscore;
//char livescoretext[1000];
/* Declare static function prototypes */
static void init(void);
static void step(void);
static void checkItem(void);
static void status_update(void);
static void update(void);
static void draw(void);
static void printinfo(void);
static void destroy(void);
static void on_key_down(int key_code);
static void on_mouse_down(int btn, int x, int y, int dz);
static void render_init_screen(void);
static void draw_hitboxes(void);

static void init(void) {
	game_over = false;
	game_main_Score = 0;
	// create map
	//basic_map = create_map(NULL);
	// TODO-GC-read_txt: Create map from .txt file so that you can design your own map!!
	basic_map = create_map("Assets/map_nthu.txt");
	if (!basic_map) {
		game_abort("error on creating map");
	}	
	// create pacman
	pman = pacman_create();
	//game_log("pacman created");
	if (!pman) {
		game_abort("error on creating pacamn\n");
	}
	set_pacman(pman);
	// allocate ghost memory
	// TODO-HACKATHON 2-1: Allocate dynamic memory for ghosts array.
	
	ghosts = (Ghost**)malloc(sizeof(Ghost*) * GHOST_NUM);
	
	if(!ghosts){
		game_log("We haven't create any ghosts!\n");
	}
	else {
		// TODO-HACKATHON 2-2: create a ghost.
		// Try to look the definition of ghost_create in ghost.h and figure out what should be placed here.
		for (int i = 0; i < GHOST_NUM; i++) {
			
			game_log("creating ghost %d\n", i);
			ghosts[i] = ghost_create(i);  
			if (!ghosts[i])
				game_abort("error creating ghost\n");
		}
	}
	GAME_TICK = 0;

	render_init_screen();
	power_up_timer = al_create_timer(1.0f); // 1 tick per second
	if (!power_up_timer)
		game_abort("Error on create timer\n");
	return ;
}

static void step(void) {
	if (pman->objData.moveCD > 0)
		pman->objData.moveCD -= pman->speed;
	for (int i = 0; i < GHOST_NUM; i++) {
		// important for movement
		if (ghosts[i]->objData.moveCD > 0)
			ghosts[i]->objData.moveCD -= ghosts[i]->speed;
	}
}
static void checkItem(void) {
	int Grid_x = pman->objData.Coord.x, Grid_y = pman->objData.Coord.y;
	if (Grid_y >= basic_map->row_num - 1 || Grid_y <= 0 || Grid_x >= basic_map->col_num - 1 || Grid_x <= 0)
		return;
	// TODO-HACKATHON 1-3: check which item you are going to eat and use `pacman_eatItem` to deal with it.
	
	switch (basic_map->map[Grid_y][Grid_x])
	{
	case '.':
		pacman_eatItem(pman, '.');
		basic_map->map[Grid_y][Grid_x] = ' ';
		break;
	case 'P':
		// TODO-GC-PB: ease power bean
		// pacman_eatItem(...);
		pacman_eatItem(pman, 'P');
		al_stop_timer(power_up_timer);
		power_up_timer = al_create_timer(1.0f);
		al_start_timer(power_up_timer);
		// stop and reset power_up_timer value
		// start the timer
		basic_map->map[Grid_y][Grid_x] = ' ';
		break;
	default:
		break;
	}
	
	// TODO-HACKATHON 1-4: erase the item you eat from map
	// Be careful, don't erase the wall block.
	
	//basic_map->map[Grid_y][Grid_x] = ' ';

}
static void status_update(void) 
{
	// TODO-PB: check powerUp duration
	
	if (pman->powerUp)
	{
		// Check the value of power_up_timer
		// If runs out of time reset all relevant variables and ghost's status
		// hint: ghost_toggle_FLEE
		if(al_get_timer_count(power_up_timer) > power_up_duration)
		{
			pman -> powerUp = false;
			al_stop_timer(power_up_timer);
			for(int i = 0; i < GHOST_NUM; i++) ghost_toggle_FLEE(ghosts[i], false);
		}
		else
		{
			for(int i = 0; i < GHOST_NUM; i++) ghost_toggle_FLEE(ghosts[i], true);
		}
	}
	


	for (int i = 0; i < GHOST_NUM; i++) {
		if (ghosts[i]->status == GO_IN){
			continue;
		}
		else if (ghosts[i]->status == FREEDOM)
		{
			// TODO-GC-game_over: use `getDrawArea(..., GAME_TICK_CD)` and `RecAreaOverlap(..., GAME_TICK_CD)` functions to detect if pacman and ghosts collide with each other.
			// And perform corresponding operations.
			// [NOTE] You should have some if-else branch here if you want to implement power bean mode.
			// Uncomment Following Code
			const RecArea pmanarea = getDrawArea((object*)pman, GAME_TICK_CD);
			const RecArea ghostsarea = getDrawArea((object*)ghosts[i], GAME_TICK_CD);
			if(!cheat_mode && RecAreaOverlap(&pmanarea, &ghostsarea))
			{
					game_log("collide with ghost\n");
					al_rest(1.0);
					pacman_die();
					game_over = true;
					break; // animation shouldn't be trigger twice.
			}
			
		}
		else if (ghosts[i]->status == FLEE)
		{
			// TODO-GC-PB: if ghost is collided by pacman, it should go back to the cage immediately and come out after a period.
			
			const RecArea pmanarea = getDrawArea((object*)pman, GAME_TICK_CD);
			const RecArea ghostsarea = getDrawArea((object*)ghosts[i], GAME_TICK_CD);
			if(!cheat_mode && RecAreaOverlap(&pmanarea, &ghostsarea))
			{
				ghost_collided(ghosts[i]);
				pman -> ghosteaten++;
			}
			
		}
	}
}

static void update(void) {

	if(game_over)
	{
		// TODO-GC-game_over: start pman->death_anim_counter and schedule a game-over event (e.g change scene to menu) after Pacman's death animation finished
		// hint: refer al_get_timer_started(...), al_get_timer_count(...), al_stop_timer(...), al_rest(...)
		
			// start the timer if it hasn't been started.
			// check timer counter.
			// stop the timer if counter reach desired time.
		if(!al_get_timer_started(pman -> death_anim_counter))
		{
			pman -> death_anim_counter = al_create_timer(1.0f /8.0f);
			if(!pman -> death_anim_counter) game_abort("Error on create correct timer\n");
			al_start_timer(pman -> death_anim_counter);
		}
		if(al_get_timer_started(pman -> death_anim_counter) && al_get_timer_count(pman -> death_anim_counter) > 12)
		{
			al_stop_timer(pman -> death_anim_counter);
			game_change_scene(scene_popupbox_create());
		}
		return;
	
	}
	step();
	checkItem();
	status_update();
	
	pacman_move(pman, basic_map);
	for (int i = 0; i < GHOST_NUM; i++) 
		ghosts[i]->move_script(ghosts[i], basic_map, pman);
}


static void draw(void) 
{

	al_clear_to_color(al_map_rgb(0, 0, 0));

	
	// TODO-GC-scoring: Draw scoreboard, something your may need is sprinf();
	
	
	if (pman -> ghosteaten > 1)
	{
		pman -> score =  (pman -> beanseaten) * 1 + (pman -> ghosteaten) * 400 -200;
		sprintf(livescoretext, "Score = %d", pman -> score);
	}
	else
	{
		pman -> score = (pman -> beanseaten) * 1 + (pman -> ghosteaten) * 200;
		sprintf(livescoretext, "Score = %d", pman -> score);
	}
	endscore = pman -> score;
	al_draw_text(menuFont , al_map_rgb(34, 139, 34), 50, 700, 0, livescoretext);
	//Highscore.score[0] = *livescoretext;
	//draw a text to show cheat mode on or off
	if(cheat_mode)
	{
		al_draw_text(menuFont, al_map_rgb_f(1.0, 1.0, 1.0), 500, 700, 0, "Cheat Mode: On");
	}
	else
	{
		al_draw_text(menuFont, al_map_rgb_f(1.0, 1.0, 1.0), 500, 700, 0, "Cheat Mode: Off");
	}
	draw_map(basic_map);

	pacman_draw(pman);
	if (game_over)
		return;
	// no drawing below when game over
	for (int i = 0; i < GHOST_NUM; i++)
		ghost_draw(ghosts[i]);
	
	//debugging mode
	if (debug_mode) 
	{
		draw_hitboxes();
	}

}

static void draw_hitboxes(void) {
	RecArea pmanHB = getDrawArea((object *)pman, GAME_TICK_CD);
	al_draw_rectangle(
		pmanHB.x, pmanHB.y,
		pmanHB.x + pmanHB.w, pmanHB.y + pmanHB.h,
		al_map_rgb_f(1.0, 0.0, 0.0), 2
	);

	for (int i = 0; i < GHOST_NUM; i++) {
		RecArea ghostHB = getDrawArea((object *)ghosts[i], GAME_TICK_CD);
		al_draw_rectangle(
			ghostHB.x, ghostHB.y,
			ghostHB.x + ghostHB.w, ghostHB.y + ghostHB.h,
			al_map_rgb_f(1.0, 0.0, 0.0), 2
		);
	}

}

static void printinfo(void) {
	game_log("pacman:\n");
	game_log("coord: %d, %d\n", pman->objData.Coord.x, pman->objData.Coord.y);
	game_log("PreMove: %d\n", pman->objData.preMove);
	game_log("NextTryMove: %d\n", pman->objData.nextTryMove);
	game_log("Speed: %f\n", pman->speed);
}


static void destroy(void) {
	// TODO-GC-memory: free map array, Pacman and ghosts
	///*	
	pacman_destroy(pman);
	for(int i = 0; i < GHOST_NUM; i++) ghost_destory(ghosts[i]);
	delete_map(basic_map);
	//*/
}

static void on_key_down(int key_code) {
	printf("hi");
	if (downchange == false && upchange == false && leftchange == false && rightchange == false)
	{
	switch (key_code)
	{
		// TODO-HACKATHON 1-1: Use allegro pre-defined enum ALLEGRO_KEY_<KEYNAME> to controll pacman movement
		// we provided you a function `pacman_NextMove` to set the pacman's next move direction.	
		case ALLEGRO_KEY_W:
			pacman_NextMove(pman, UP);
			break;
		case ALLEGRO_KEY_A:
			pacman_NextMove(pman, LEFT);
			break;
		case ALLEGRO_KEY_S:
			pacman_NextMove(pman, DOWN);
			break;
		case ALLEGRO_KEY_D:
			pacman_NextMove(pman, RIGHT);
			break;
		
		case ALLEGRO_KEY_C:
			cheat_mode = !cheat_mode;
			if (cheat_mode)
				printf("cheat mode on\n");
			else 
				printf("cheat mode off\n");
			break;
		
		int currentX =  pman->objData.Coord.x, currentY = pman->objData.Coord.y;
		
		
		case ALLEGRO_KEY_G:
			debug_mode = !debug_mode;
			break;
		
		default:
			break;
	}
	if (cheat_mode)
	{
		switch (key_code)
		{
			case ALLEGRO_KEY_T:
				game_over = true;
			case ALLEGRO_KEY_K:
				for (int i = 0; i < GHOST_NUM; i++)
				{
					if (ghosts[i] -> status == FREEDOM)	
					{
						ghosts[i] -> status = GO_IN;
						ghosts[i] -> speed = 4;
					}
					else if (ghosts[i] ->status == FLEE)
					{
						ghosts[i] -> status = GO_IN;
						ghosts[i] -> speed = 4;
					}
					else if (ghosts[i] -> status == GO_IN) 
					{
						ghosts[i] -> status = FREEDOM;
						ghosts[i] -> speed = 2;
					}
				}
				break;
			case ALLEGRO_KEY_S:
				if (ctrl_state && ghosts[0] -> speed == 2) 
				{
					game_log("STOP");
					for (int i = 0; i < GHOST_NUM; i++)
					{
						ghosts[i] -> speed = 0;
					}
					
				}
				else if (ctrl_state && ghosts[0] -> speed == 0)
				{
					for (int i = 0; i < GHOST_NUM; i++)
					{
						ghosts[i] -> speed = 2;
					}
				}
				else if (cheat_mode && ctrl_state == false) pacman_NextMove(pman, DOWN);
				break;
			case ALLEGRO_KEY_L:
				if(ctrl_state && pman -> wall_hack == 0)
				{
					pman -> wall_hack = 1;
				}
				else if(ctrl_state && pman -> wall_hack == 1)
				{
					pman -> wall_hack = 0;
				}
				break;
			default:
				break;
		}
	}
	}
	else if(key_code)
	{
		char key_pressed = key_code - 1 + 'A';
		if (key_pressed == upbutton[0]) pacman_NextMove(pman, UP);
		else if (key_pressed == leftbutton[0]) pacman_NextMove(pman, LEFT);
		else if (key_pressed == rightbutton[0]) pacman_NextMove(pman, RIGHT);
		else if (key_pressed == downbutton[0]) pacman_NextMove(pman, DOWN);
	}
}

static void on_mouse_down(int btn, int x, int y, int dz) {

	// nothing here

}

static void render_init_screen(void) {
	al_clear_to_color(al_map_rgb(0, 0, 0));

	draw_map(basic_map);
	pacman_draw(pman);
	for (int i = 0; i < GHOST_NUM; i++) {
		ghost_draw(ghosts[i]);
	}

	al_draw_text(
		minecraftFont,
		al_map_rgb(255, 255, 0),
		400, 400,
		ALLEGRO_ALIGN_CENTER,
		"READY!"
	);

	al_flip_display();
	al_rest(2.0);

}



// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_main_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Start";
	scene.initialize = &init;
	scene.update = &update;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_down = &on_mouse_down;
	// TODO-IF: Register more event callback functions such as keyboard, mouse, ...
	game_log("Start scene created");
	return scene;
}

int64_t get_power_up_timer_tick()
{
	return al_get_timer_count(power_up_timer);
}
int64_t get_power_up_duration()
{
	return power_up_duration;
}