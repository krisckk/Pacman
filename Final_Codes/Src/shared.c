// [shared.c]
// you should define the shared variable declared in the header here.
#include "scene_settings.h"
#include "shared.h"
#include "utility.h"
#include "game.h"
// #include "scene_menu.h"

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
ALLEGRO_SAMPLE* themeMusicoriginal = NULL;
ALLEGRO_SAMPLE* themeMusicintermission = NULL;
ALLEGRO_SAMPLE* PACMAN_MOVESOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_DEATH_SOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_POWERUPSOUND = NULL;
ALLEGRO_FONT* menuFont = NULL;
ALLEGRO_FONT* minecraftFont = NULL;
ALLEGRO_FONT* darkknightFont = NULL;
ALLEGRO_FONT* FFF_Font = NULL;
ALLEGRO_FONT* PoetFont = NULL;
int fontSize = 30;
float music_volume = 0.5;
float effect_volume = 0.5;
bool gameDone = false;

/*
	A way to accelerate is load assets once.
	And delete them at the end.
	This method does provide you better management of memory.
	
*/
void shared_init(void) {
	
	menuFont = load_font("Assets/Minecraft.ttf", fontSize);
	minecraftFont = load_font("Assets/special_minecraft_font.ttf", 48);
	FFF_Font = load_font("Assets/FFF.ttf", fontSize);
	darkknightFont = load_font("Assets/DeadKnight.otf", 40);
	PoetFont = load_font("Assets/PoetsenOne.ttf", 45);
	themeMusicoriginal = load_audio("Assets/Music/original_theme.ogg");
	themeMusicintermission = load_audio("Assets/Music/pacman_intermission.ogg");
	PACMAN_MOVESOUND = load_audio("Assets/Music/pacman-chomp.ogg");
	PACMAN_POWERUPSOUND = load_audio("Assets/Music/pacman_eatfruit.ogg");
	PACMAN_DEATH_SOUND = load_audio("Assets/Music/pacman_death.ogg");
}

void shared_destroy(void) {

	al_destroy_font(menuFont);
	al_destroy_font(minecraftFont);
	al_destroy_font(FFF_Font);
	al_destroy_font(darkknightFont);
	al_destroy_font(PoetFont);
	al_destroy_sample(themeMusicoriginal);
	al_destroy_sample(themeMusicintermission);
	al_destroy_sample(PACMAN_MOVESOUND);
	al_destroy_sample(PACMAN_POWERUPSOUND);
	al_destroy_sample(PACMAN_DEATH_SOUND);
}