#ifndef STAGESELECT_H
#define STAGESELECT_H
#include "game.h"
typedef struct _StageSelectScene
{
    ALLEGRO_BITMAP *background;
    int slidervalue;
    int stage[3];
} StageSelectScene;
Scene scene_stageselect_create(void);
static void Init(void);
static void Update(void);
static void Draw(void);
static void Destroy(void);
static void On_key_down(int key_code);
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f);
static void On_mouse_down();
static void On_mouse_scroll(int a, int mouse_x, int mouse_y, int dz);
static void On_mouse_up();
static void Render_init_screen(void);
#endif