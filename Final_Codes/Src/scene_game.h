// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

#ifndef SCENE_GAME_H
#define SCENE_GAME_H
#include "game.h"

Scene scene_main_create(void);
bool cheat_mode;
typedef struct highscore
{
    char score[30];
    char name[30];
}highscore;

static highscore Highscore;
char livescoretext[1000];
int endscore;

int64_t get_power_up_timer_tick();
int64_t get_power_up_duration();


#endif
