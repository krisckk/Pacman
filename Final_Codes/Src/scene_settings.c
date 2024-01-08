// TODO-HACKATHON 3-9: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"
#include "scene_game.h"
#include "pacman_obj.h"
#include "scene_menu.h"
#include "scene_menu_object.h"
#include <allegro5/allegro_primitives.h>
// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO-IF: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
extern Pacman *pman1;
//static Pacman *pman;
static Button yellow_pacman_button;
static Button purple_pacman_button;

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) 
{
	yellow_pacman_button.hovered = buttonHover(yellow_pacman_button, mouse_x, mouse_y);
	purple_pacman_button.hovered = buttonHover(purple_pacman_button, mouse_x, mouse_y);

}
static void on_mouse_down() {
	if(pman1 == NULL)
	{
		game_log("pamn1 is NULL");
	}
	if (yellow_pacman_button.hovered)
	{
		yellow_pacman_button.clicked = true;
		purple_pacman_button.clicked = false;
		pman1 -> yellow = true;
		pman1 -> purple = false;
		game_log("yellow is true");
	}
	if (purple_pacman_button.hovered) 
	{
		purple_pacman_button.clicked = true;
		yellow_pacman_button.clicked = false;
		pman1 -> purple = true;
		pman1 -> yellow = false;
		game_log("purple is true");
	}
}

static void init()
{
	yellow_pacman_button = button_create(55, 70, 100, 100, "Assets/pacman_yellow_button_default_image.png", "Assets/pacman_yellow_button_hovered_image.png");
	purple_pacman_button = button_create(55, 170, 100, 100, "Assets/pacman_purple_button_default_image.png", "Assets/pacman_purple_button_hovered_image.png");

	yellow_pacman_button.clicked = false;
	purple_pacman_button.clicked = false;
}

static const int draw_region = 30;
static void draw(void )
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2,
		SCREEN_H - 150,
		ALLEGRO_ALIGN_CENTER,
		"<ENTER> Back to menu"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2,
		SCREEN_H - 75,
		ALLEGRO_ALIGN_CENTER,
		"Settings"
	);
	al_draw_rectangle(10, 10, 380, 600, al_map_rgb(255, 255, 255), 10);
	al_draw_rectangle(420, 10, 790, 600, al_map_rgb(255, 255, 255), 10);
	al_draw_text(menuFont, al_map_rgb(255, 255, 255), 525, 30, 0, "Key Settings");
	al_draw_text(menuFont, al_map_rgb(255, 255, 255), 110, 30, 0, "Character");
	drawButton(yellow_pacman_button);	
	drawButton(purple_pacman_button); 
	if(yellow_pacman_button.clicked == false) 
	{
		al_draw_rectangle(300, 80, 350, 150, al_map_rgb(255, 255, 255), 8);
		al_draw_text(menuFont, al_map_rgb(255, 255, 255), 160, 80, 0, "Origin");
		al_draw_text(menuFont, al_map_rgb(255, 255, 255), 160, 130, 0, "Pacman");
	}
	else if (yellow_pacman_button.clicked == true) 
	{
		al_draw_filled_rectangle(300, 80, 350, 150, al_map_rgb(255, 255, 0));
		al_draw_text(menuFont, al_map_rgb(255, 255, 0), 160, 80, 0, "Origin");
		al_draw_text(menuFont, al_map_rgb(255, 255, 0), 160, 130, 0, "Pacman");
	}
	if(purple_pacman_button.clicked == false)
	{
		al_draw_rectangle(300, 180, 350, 250, al_map_rgb(255, 255, 255), 8);	
		al_draw_text(menuFont, al_map_rgb(255, 255, 255), 160, 180, 0, "Purple");
		al_draw_text(menuFont, al_map_rgb(255, 255, 255), 160, 230, 0, "Pacman");
	}
	else if(purple_pacman_button.clicked == true)
	{
		al_draw_filled_rectangle(300, 180, 350, 250, al_map_rgb(160, 32, 240));
		al_draw_text(menuFont, al_map_rgb(160, 32, 240), 160, 180, 0, "Purple");
		al_draw_text(menuFont, al_map_rgb(160, 32, 240), 160, 230, 0, "Pacman");
	}
}

static void on_key_down(int keycode) {
	switch (keycode) {
		case ALLEGRO_KEY_ENTER:
			game_change_scene(scene_menu_create());
			break;
		default:
			break;
	}
}

// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	// TODO-IF: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}

// TODO-Graphical_Widget:
// Just suggestions, you can create your own usage.
	// Selecting BGM:
	// 1. Declare global variables for storing the BGM. (see `shared.h`, `shared.c`)
	// 2. Load the BGM in `shared.c`.
	// 3. Create dropdown menu for selecting BGM in setting scene, involving `scene_settings.c` and `scene_setting.h.
	// 4. Switch and play the BGM if the corresponding option is selected.

	// Adjusting Volume:
	// 1. Declare global variables for storing the volume. (see `shared.h`, `shared.c`)
	// 2. Create a slider for adjusting volume in setting scene, involving `scene_settings.c` and `scene_setting.h.
		// 2.1. You may use checkbox to switch between mute and unmute.
	// 3. Adjust the volume and play when the button is pressed.

	// Selecting Map:
	// 1. Preload the map to `shared.c`.
	// 2. Create buttons(or dropdown menu) for selecting map in setting scene, involving `scene_settings.c` and `scene_setting.h.
		// 2.1. For player experience, you may also create another scene between menu scene and game scene for selecting map.
	// 3. Create buttons(or dropdown menu) for selecting map in setting scene, involving `scene_settings.c` and `scene_setting.h.
	// 4. Switch and draw the map if the corresponding option is selected.
		// 4.1. Suggestions: You may use `al_draw_bitmap` to draw the map for previewing. 
							// But the map is too large to be drawn in original size. 
							// You might want to modify the function to allow scaling.