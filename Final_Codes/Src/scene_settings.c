// TODO-HACKATHON 3-9: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"
#include "scene_game.h"
#include "pacman_obj.h"
#include "scene_menu.h"
#include "scene_menu_object.h"
#include "shared.h"
#include <allegro5/allegro_primitives.h>
// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO-IF: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix. Pacman* pman;
//pacman selection

static  Pacman *pman;
static Button yellow_pacman_button;
static Button purple_pacman_button;
int yellowpman = 1;
int purplepman = 0;
//theme music selction
static Button thememusic_button;
static Button original_theme_button;
static Button intermission_button;
int originaltheme = 1;
int intermission = 0;
//music volume slider
Slider volume_slider;
//key settings
static Button UP_key_settings_button;
static Button LEFT_key_settings_button;
static Button RIGHT_key_settings_button;
static Button DOWN_key_settings_button;
char upbutton[2] = {'W'}, leftbutton[2] = {'A'}, downbutton[2] = {'S'}, rightbutton[2] = {'D'};
bool upchange = false, leftchange = false, downchange = false, rightchange = false;
static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) 
{
	yellow_pacman_button.hovered = buttonHover(yellow_pacman_button, mouse_x, mouse_y);
	purple_pacman_button.hovered = buttonHover(purple_pacman_button, mouse_x, mouse_y);
	thememusic_button.hovered = buttonHover(thememusic_button, mouse_x, mouse_y);
	original_theme_button.hovered = buttonHover(original_theme_button, mouse_x, mouse_y);
	intermission_button.hovered = buttonHover(intermission_button, mouse_x, mouse_y);
	if (volume_slider.dragging)
	{
		volume_slider.value = (mouse_x - volume_slider.x) * (volume_slider.max - volume_slider.min) / volume_slider.width;
	}
	if (volume_slider.value < volume_slider.min) volume_slider.value = volume_slider.min;
	else if (volume_slider.value > volume_slider.max) volume_slider.value = volume_slider.max;
	float fill_width = (volume_slider.value - volume_slider.min) * volume_slider.width /  
				(volume_slider.max - volume_slider.min);
	music_volume = (fill_width * 0.5 / 50);
	UP_key_settings_button.hovered = buttonHover(UP_key_settings_button, mouse_x, mouse_y);
	LEFT_key_settings_button.hovered = buttonHover(LEFT_key_settings_button, mouse_x, mouse_y);
	RIGHT_key_settings_button.hovered = buttonHover(RIGHT_key_settings_button, mouse_x, mouse_y);
	DOWN_key_settings_button.hovered = buttonHover(DOWN_key_settings_button, mouse_x, mouse_y);
}
void set_pacman(Pacman* pacman)
{
	pman = pacman;
}
static void on_mouse_down() 
{
	if(pman == NULL)
	{
		game_log("pamn is NULL");
	}
	if (yellow_pacman_button.hovered)
	{
		yellow_pacman_button.clicked = true;
		purple_pacman_button.clicked = false;
		yellowpman = 1;
		purplepman = 0;
		if(yellowpman == 1)	game_log("you choose yellow pacman");
	}
	if (purple_pacman_button.hovered) 
	{
		purple_pacman_button.clicked = true;
		yellow_pacman_button.clicked = false;
		purplepman = 1;
		yellowpman = 0;
		if(purplepman == 1) game_log("you choose purple pacman");
	}
	if(thememusic_button.hovered)
	{
		thememusic_button.clicked = true;
	}
	if (original_theme_button.hovered)
	{
		original_theme_button.clicked = true;
		intermission_button.clicked = false;
		originaltheme = 1;
		intermission = 0;
		if(originaltheme == 1)	game_log("you choose original theme");
	}
	if (intermission_button.hovered) 
	{
		intermission_button.clicked = true;
		original_theme_button.clicked = false;
		intermission = 1;
		originaltheme = 0;
		if(intermission == 1) game_log("you choose intermission");
	}
	// Check if mouse is on slider
 	if(mouse_x > volume_slider.x && mouse_x < volume_slider.x + volume_slider.width
	&& mouse_y > volume_slider.y && mouse_y < volume_slider.y + volume_slider.height) 
	{
		volume_slider.dragging = true; 
  	}
	//ky settings
	if(UP_key_settings_button.hovered)
	{
		UP_key_settings_button.clicked = true;
		LEFT_key_settings_button.clicked = false;
		RIGHT_key_settings_button.clicked = false;
		DOWN_key_settings_button.clicked = false;
	}
	if(LEFT_key_settings_button.hovered)
	{
		UP_key_settings_button.clicked = false;
		LEFT_key_settings_button.clicked = true;
		RIGHT_key_settings_button.clicked = false;
		DOWN_key_settings_button.clicked = false;
	}
	if(RIGHT_key_settings_button.hovered)
	{
		UP_key_settings_button.clicked = false;
		LEFT_key_settings_button.clicked = false;
		RIGHT_key_settings_button.clicked = true;
		DOWN_key_settings_button.clicked = false;
	}
	if(DOWN_key_settings_button.hovered)
	{
		UP_key_settings_button.clicked = false;
		LEFT_key_settings_button.clicked = false;
		RIGHT_key_settings_button.clicked = false;
		DOWN_key_settings_button.clicked = true;
	}

}
static void on_mouse_up()
{
	volume_slider.dragging = false;
}

static void init()
{
	yellow_pacman_button = button_create(45, 70, 90, 100, "Assets/pacman_yellow_button_default_image.png", "Assets/pacman_yellow_button_hovered_image.png");
	purple_pacman_button = button_create(45, 170, 90, 100, "Assets/pacman_purple_button_default_image.png", "Assets/pacman_purple_button_hovered_image.png");
	thememusic_button = button_create(20, 400, 300, 40, "Assets/theme_music_button.png", "Assets/theme_music_button_hovered.png");
	original_theme_button = button_create(340, 445, 20, 50,  "Assets/theme_music_button.png", "Assets/theme_music_button_hovered.png");
	intermission_button = button_create(340, 505, 20, 50,  "Assets/theme_music_button.png", "Assets/theme_music_button_hovered.png");
	pman = pacman_create();
	yellow_pacman_button.clicked = false;
	purple_pacman_button.clicked = false;
	thememusic_button.clicked = false;
	//Initialize game music volume slider
	volume_slider.x = 110;
  	volume_slider.y = 325; 
  	volume_slider.width = 200;
 	volume_slider.height = 20;
  	volume_slider.min = 0;
  	volume_slider.max = 100;
  	volume_slider.value = 50;
  	volume_slider.dragging = false;
	//key settings
	UP_key_settings_button = button_create(570, 80, 160, 110, "Assets/UP_key_settings_button.png", "Assets/UP_key-settings_buttons_hovered.png");
	LEFT_key_settings_button = button_create(570, 190, 160, 110, "Assets/UP_key_settings_button.png", "Assets/UP_key-settings_buttons_hovered.png");
	RIGHT_key_settings_button = button_create(570, 310, 160, 110, "Assets/UP_key_settings_button.png", "Assets/UP_key-settings_buttons_hovered.png");
	DOWN_key_settings_button = button_create(570, 420, 160, 110, "Assets/UP_key_settings_button.png", "Assets/UP_key-settings_buttons_hovered.png");
	UP_key_settings_button.clicked = false;
	LEFT_key_settings_button.clicked = false;
	RIGHT_key_settings_button.clicked = false;
	DOWN_key_settings_button.clicked = false;
}

//static const int draw_region = 30;
static void draw(void )
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(
		menuFont,
		al_map_rgb(34, 139, 34),
		SCREEN_W/2,
		SCREEN_H - 150,
		ALLEGRO_ALIGN_CENTER,
		"<ENTER> Back to menu"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(34, 139, 34),
		SCREEN_W/2,
		SCREEN_H - 75,
		ALLEGRO_ALIGN_CENTER,
		"Settings"
	);
	//draw the charcter settings
	al_draw_rounded_rectangle(10, 10, 380, 600, 15, 15, al_map_rgb(0, 0, 205), 10);
	al_draw_text(menuFont, al_map_rgb(34, 139, 34), 110, 30, 0, "Character");
	drawButton(yellow_pacman_button);	
	drawButton(purple_pacman_button); 
	if(yellow_pacman_button.clicked == false) 
	{
		al_draw_rounded_rectangle(300, 80, 350, 150, 10, 10, al_map_rgb(205, 0, 0), 8);
		al_draw_text(menuFont, al_map_rgb(205, 0, 0), 160, 80, 0, "Origin");
		al_draw_text(menuFont, al_map_rgb(205, 0, 0), 160, 130, 0, "Pacman");
	}
	else if (yellow_pacman_button.clicked == true)
	{
		al_draw_filled_rounded_rectangle(300, 80, 350, 150, 10, 10, al_map_rgb(255, 255, 0));
		al_draw_text(menuFont, al_map_rgb(255, 255, 0), 160, 80, 0, "Origin");
		al_draw_text(menuFont, al_map_rgb(255, 255, 0), 160, 130, 0, "Pacman");
	}
	if(purple_pacman_button.clicked == false)
	{
		al_draw_rounded_rectangle(300, 180, 350, 250, 10, 10, al_map_rgb(205, 0, 0), 8);	
		al_draw_text(menuFont, al_map_rgb(205, 0, 0), 160, 180, 0, "Purple");
		al_draw_text(menuFont, al_map_rgb(205, 0, 0), 160, 230, 0, "Pacman");
	}
	else if(purple_pacman_button.clicked == true)
	{
		al_draw_filled_rounded_rectangle(300, 180, 350, 250, 10, 10, al_map_rgb(160, 32, 240));
		al_draw_text(menuFont, al_map_rgb(160, 32, 240), 160, 180, 0, "Purple");
		al_draw_text(menuFont, al_map_rgb(160, 32, 240), 160, 230, 0, "Pacman");
	}
	al_draw_line(10, 265, 380, 265, al_map_rgb(0, 0, 205), 10);
	al_draw_text(menuFont, al_map_rgb(34, 139, 34), 80, 275, 0, "Volume Settings");
	//draw music volume slider
	al_draw_text(menuFont, al_map_rgb(255, 215, 0), 25, 323, 0, "Music");
	int fill_width = (volume_slider.value - volume_slider.min) * volume_slider.width / 
                   (volume_slider.max - volume_slider.min);
	al_draw_filled_rectangle(volume_slider.x, volume_slider.y, 
                           volume_slider.x + fill_width, 
                           volume_slider.y + volume_slider.height,
                           al_map_rgb(255, 215, 0));
	al_draw_rectangle(volume_slider.x, volume_slider.y,
                   volume_slider.x + volume_slider.width, 
                   volume_slider.y + volume_slider.height,
                   al_map_rgb(255, 215, 0), 2);
	char musicvolume[50];
	sprintf(musicvolume, "%d", fill_width);
	al_draw_text(menuFont, al_map_rgb(255, 215, 0), 330, 323, 0, musicvolume);
	al_draw_line(10, 355, 380, 355, al_map_rgb(0, 0, 205), 10);
	//theme music settings
	al_draw_text(menuFont, al_map_rgb(34, 139, 34), 100, 370, 0, "Theme Music");
	drawButton(thememusic_button);
	if (thememusic_button.clicked == true)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 50, 409, 0, "Theme selection");
		al_draw_rounded_rectangle(20, 440, 320, 500, 15, 15, al_map_rgb(255, 215, 0), 5);
		al_draw_text(menuFont, al_map_rgb(255, 215, 0), 105, 457, 0, "Original");
		drawButton(original_theme_button);
		al_draw_rounded_rectangle(20, 500, 320, 560, 15, 15, al_map_rgb(255, 215, 0), 5);
		al_draw_text(menuFont, al_map_rgb(255, 215, 0), 75, 517, 0, "Intermission");
		drawButton(intermission_button);
	}
	else
	{
		al_draw_text(menuFont, al_map_rgb(255, 255, 0), 50, 409, 0, "Theme selection");
	}
	//draw the key settings
	al_draw_rounded_rectangle(420, 10, 790, 600, 15, 15, al_map_rgb(0, 0, 205), 10);
	al_draw_text(menuFont, al_map_rgb(34, 139, 34), 525, 30, 0, "Key Settings");
	al_draw_text(menuFont, al_map_rgb(205, 0, 0), 485, 120, 0, "UP");
	drawButton(UP_key_settings_button);
	if (UP_key_settings_button.arrow_key_up)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 115, 0, "^");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 125, 0, "|");
	}
	else if(UP_key_settings_button.arrow_key_left)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 585, 120, 0, "<");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 115, 0, "-");
	}
	else if(UP_key_settings_button.arrow_key_right)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 585, 115, 0, "-");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 120, 0, ">");
	}
	else if(UP_key_settings_button.arrow_key_down)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 115, 0, "|");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 125, 0, "v");
	}
	else
	{
		if (upchange)	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 120, 0, upbutton);
		else	al_draw_text(menuFont, al_map_rgb(255, 255, 255), 590, 120, 0, upbutton);
	}
	
	al_draw_text(menuFont, al_map_rgb(205, 0, 0), 465, 230, 0, "LEFT");
	drawButton(LEFT_key_settings_button);
	if (LEFT_key_settings_button.arrow_key_up)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 225, 0, "^");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 235, 0, "|");
	}
	else if(LEFT_key_settings_button.arrow_key_left)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 585, 230, 0, "<");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 225, 0, "-");
	}
	else if(LEFT_key_settings_button.arrow_key_right)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 585, 225, 0, "-");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 230, 0, ">");
	}
	else if(LEFT_key_settings_button.arrow_key_down)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 225, 0, "|");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 235, 0, "v");
	}
	else
	{
		if (leftchange)	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 230, 0, leftbutton);
		else	al_draw_text(menuFont, al_map_rgb(255, 255, 255), 590, 230, 0, leftbutton);
	}

	al_draw_text(menuFont, al_map_rgb(205, 0, 0), 463, 350, 0, "RIGHT");
	drawButton(RIGHT_key_settings_button);
	if (RIGHT_key_settings_button.arrow_key_up)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 345, 0, "^");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 355, 0, "|");
	}
	else if(RIGHT_key_settings_button.arrow_key_left)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 585, 350, 0, "<");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 345, 0, "-");
	}
	else if(RIGHT_key_settings_button.arrow_key_right)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 585, 345, 0, "-");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 350, 0, ">");
	}
	else if(RIGHT_key_settings_button.arrow_key_down)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 345, 0, "|");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 355, 0, "v");
	}
	else
	{
		if (rightchange)	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 350, 0, rightbutton);
		else	al_draw_text(menuFont, al_map_rgb(255, 255, 255), 590, 350, 0, rightbutton);
	}
	al_draw_text(menuFont, al_map_rgb(205, 0, 0), 465, 460, 0, "DOWN");
	drawButton(DOWN_key_settings_button);
	if (DOWN_key_settings_button.arrow_key_up)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 455, 0, "^");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 465, 0, "|");
	}
	else if(DOWN_key_settings_button.arrow_key_left)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 585, 460, 0, "<");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 455, 0, "-");
	}
	else if(DOWN_key_settings_button.arrow_key_right)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 585, 455, 0, "-");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 460, 0, ">");
	}
	else if(DOWN_key_settings_button.arrow_key_down)
	{
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 595, 455, 0, "|");
		al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 465, 0, "v");
	}
	else
	{
		if (downchange)	al_draw_text(menuFont, al_map_rgb(0, 0, 0), 590, 460, 0, downbutton);
		else	al_draw_text(menuFont, al_map_rgb(255, 255, 255), 590, 460, 0, downbutton);
	}
}


static void on_key_down(int keycode) 
{
	switch (keycode) 
	{
		case ALLEGRO_KEY_ENTER:
			game_change_scene(scene_menu_create());
			break;
		default:
			break;
	}
	if(UP_key_settings_button.clicked)
	{
		if(keycode == 67) {}
		else if(keycode == 84)
		{
			UP_key_settings_button.arrow_key_up = true;
			UP_key_settings_button.arrow_key_down = false;
			UP_key_settings_button.arrow_key_left = false;
			UP_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 85)
		{
			UP_key_settings_button.arrow_key_up = false;
			UP_key_settings_button.arrow_key_down = true;
			UP_key_settings_button.arrow_key_left = false;
			UP_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 82)
		{
			UP_key_settings_button.arrow_key_up = false;
			UP_key_settings_button.arrow_key_down = false;
			UP_key_settings_button.arrow_key_left = true;
			UP_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 83)
		{
			UP_key_settings_button.arrow_key_up = false;
			UP_key_settings_button.arrow_key_down = false;
			UP_key_settings_button.arrow_key_left = false;
			UP_key_settings_button.arrow_key_right = true;
		}
		else
		{
			char upmodification = keycode - 1 + 'A';
			sprintf(upbutton, "%c", upmodification);
			upchange = true;
			leftchange = false;
			downchange = false;
			rightchange = false;
		}
	}
	if(LEFT_key_settings_button.clicked)
	{
		if(keycode == 67) {}
		else if(keycode == 84)
		{
			LEFT_key_settings_button.arrow_key_up = true;
			LEFT_key_settings_button.arrow_key_down = false;
			LEFT_key_settings_button.arrow_key_left = false;
			LEFT_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 85)
		{
			LEFT_key_settings_button.arrow_key_up = false;
			LEFT_key_settings_button.arrow_key_down = true;
			LEFT_key_settings_button.arrow_key_left = false;
			LEFT_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 82)
		{
			LEFT_key_settings_button.arrow_key_up = false;
			LEFT_key_settings_button.arrow_key_down = false;
			LEFT_key_settings_button.arrow_key_left = true;
			LEFT_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 83)
		{
			LEFT_key_settings_button.arrow_key_up = false;
			LEFT_key_settings_button.arrow_key_down = false;
			LEFT_key_settings_button.arrow_key_left = false;
			LEFT_key_settings_button.arrow_key_right = true;
		}
		else
		{
			char leftmodification = keycode - 1 + 'A';
			sprintf(leftbutton, "%c", leftmodification);
			leftchange = true;
			upchange = false;
			downchange = false;
			rightchange = false;
		}
	}
	if(DOWN_key_settings_button.clicked)
	{
		if(keycode == 67) {}
		else if(keycode == 84)
		{
			DOWN_key_settings_button.arrow_key_up = true;
			DOWN_key_settings_button.arrow_key_down = false;
			DOWN_key_settings_button.arrow_key_left = false;
			DOWN_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 85)
		{
			DOWN_key_settings_button.arrow_key_up = false;
			DOWN_key_settings_button.arrow_key_down = true;
			DOWN_key_settings_button.arrow_key_left = false;
			DOWN_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 82)
		{
			DOWN_key_settings_button.arrow_key_up = false;
			DOWN_key_settings_button.arrow_key_down = false;
			DOWN_key_settings_button.arrow_key_left = true;
			DOWN_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 83)
		{
			DOWN_key_settings_button.arrow_key_up = false;
			DOWN_key_settings_button.arrow_key_down = false;
			DOWN_key_settings_button.arrow_key_left = false;
			DOWN_key_settings_button.arrow_key_right = true;
		}
		else
		{
			char downmodification = keycode - 1 + 'A';
			sprintf(downbutton, "%c", downmodification);
			downchange = true;
			upchange = false;
			leftchange = false;
			rightchange = false; 
		}
	}
	if(RIGHT_key_settings_button.clicked)
	{
		if(keycode == 67) {}
		else if(keycode == 84)
		{
			RIGHT_key_settings_button.arrow_key_up = true;
			RIGHT_key_settings_button.arrow_key_down = false;
			RIGHT_key_settings_button.arrow_key_left = false;
			RIGHT_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 85)
		{
			RIGHT_key_settings_button.arrow_key_up = false;
			RIGHT_key_settings_button.arrow_key_down = true;
			RIGHT_key_settings_button.arrow_key_left = false;
			RIGHT_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 82)
		{
			RIGHT_key_settings_button.arrow_key_up = false;
			RIGHT_key_settings_button.arrow_key_down = false;
			RIGHT_key_settings_button.arrow_key_left = true;
			RIGHT_key_settings_button.arrow_key_right = false;
		}
		else if(keycode == 83)
		{
			RIGHT_key_settings_button.arrow_key_up = false;
			RIGHT_key_settings_button.arrow_key_down = false;
			RIGHT_key_settings_button.arrow_key_left = false;
			RIGHT_key_settings_button.arrow_key_right = true;
		}
		else
		{
			char rightmodification = keycode - 1 + 'A';
			sprintf(rightbutton, "%c", rightmodification);
			rightchange = true;
			upchange = false;
			leftchange = false;
			downchange = false;
		}
	}
}
// The only function that is shared across files.
Scene scene_settings_create(void) 
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	scene.on_mouse_up = &on_mouse_up;
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