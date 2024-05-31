#ifndef SCENE_SETTINGS_H
#define SCENE_SETTINGS_H
#include "game.h"
#include "shared.h"
#include "scene_menu.h"

Scene scene_settings_create(void);
void set_pacman(Pacman* pacman);
int yellowpman;
int purplepman;
int originaltheme;
int intermission;

typedef struct {
  int x, y;
  int width, height;
  int min, max; 
  int value;
  bool dragging;
} Slider;

bool upchange, leftchange, downchange, rightchange;
char upbutton[2], leftbutton[2], downbutton[2], rightbutton[2];

#endif
