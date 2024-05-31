#ifndef HOME_H
#define HOME_H
#include "game.h"
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *StageSelectBuilding;
    ALLEGRO_BITMAP *StaminaRestoreBuulding;
    ALLEGRO_BITMAP *EquipementBuilding;
    bool stageSelect;
    bool staminaRestore;
    bool equipement;
} GameScene;
Scene scene_home_create(void);
static void Init(void);
static void Step(void);
//static void StatusUpdate(void);
static void Update(void);
static void Draw(void);
static void Destroy(void);
static void On_key_down(int key_code);
static void On_key_up(int key_code);
static void Render_init_screen(void);
//static void Draw_hitboxes(void);
#endif