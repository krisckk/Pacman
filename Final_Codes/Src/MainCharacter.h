#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include "utility.h"
#include "game.h"
static int basic_speed;
typedef struct Maincharacter{
	object objData;
	bitmapdata imgdata;
	int currentX;
	int speed;
    ALLEGRO_BITMAP *MCMoveSprite;
} Maincharacter;

Maincharacter* MCCreate();
void MCDestroy(Maincharacter* MC);
void MCDraw(Maincharacter* MC);
void MCMove(Maincharacter* MC);
void MCNextMove(Maincharacter* MC, Directions next);
#endif // !PACMAN_OBJ_H
