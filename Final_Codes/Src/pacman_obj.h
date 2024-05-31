#ifndef PACMAN_OBJ_H
#define PACMAN_OBJ_H

#include "utility.h"
#include "game.h"

// <Forward Declaration>
// forward declarations can be useful when you need to have looping struct declarations,
// but you want to (should) prevent mutually include dependency.
// Only applicable when you only need the declaration but no need the definition in you sturct,
// which means that you only used the struct as pointer(no access to struct data), param, return type in this file.
// If you have to access the data in struct ex. `A->data`, 
// you should include the corresponding header file for its definition.
// Advance reading : https://stackoverflow.com/questions/18658438/what-is-forward-declaration-and-the-difference-between-typedef-struct-x-and

typedef struct Ghost Ghost;
typedef struct Map Map;
static int basic_speed;
typedef struct Pacman{
	object objData;
	bitmapdata imgdata;
	
	int wall_hack;
	int speed;
	int beanseaten;//how many beans eaten
	int ghosteaten;//how many ghost eaten
	int score;//how mnay points did pacman score
	bool powerUp; // *important: this boolean indicates if pacman is in power bean mode now.
	ALLEGRO_TIMER* death_anim_counter;
	ALLEGRO_BITMAP* yellow_move_sprite;
	ALLEGRO_BITMAP* purple_move_sprite;
	ALLEGRO_BITMAP* yellow_die_sprite;
	ALLEGRO_BITMAP* purple_die_sprite;
} Pacman;

Pacman* pacman_create();
void pacman_destroy(Pacman* pman);

void pacman_draw(Pacman* pacman);
void pacman_move(Pacman* pacman, Map* M);
void pacman_eatItem(Pacman* pacman, const char Item);

void pacman_NextMove(Pacman* pacman, Directions next);
void pacman_die();
#endif // !PACMAN_OBJ_H
