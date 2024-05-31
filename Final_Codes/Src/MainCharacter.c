#include <allegro5/allegro_primitives.h>
#include "scene_settings.h"
#include "MainCharacter.h"
#include "map.h"
static const int start_grid_x = 25, start_grid_y = 25;		// where to put pacman at the beginning
static const int fix_draw_pixel_offset_x = -575, fix_draw_pixel_offset_y = 250;  // draw offset 
extern int basic_speed = 12;
static const int draw_region = 256;
extern uint32_t GAME_TICK_CD;

Maincharacter* MCCreate(){
    game_log("MC create");
    Maincharacter* MC = (Maincharacter*)malloc(sizeof(Maincharacter));
    if(!MC) return NULL;
    MC -> objData.Coord.x = 24;
    MC -> objData.Coord.y = 24;
	MC -> objData.Size.x = block_width;
	MC -> objData.Size.y = block_height;
	MC -> objData.preMove = NONE;
	MC -> objData.nextTryMove = NONE;
	MC -> speed = basic_speed;
	MC -> MCMoveSprite = load_bitmap("Assets/Images/MainCharacter.png");
    return MC;
}
void MCDestroy(Maincharacter* MC){
    al_destroy_bitmap(MC -> MCMoveSprite);
    free(MC);
}
void MCDraw(Maincharacter* MC){        

    RecArea drawArea = getDrawArea((object *)MC, GAME_TICK_CD);
    MC -> currentX = drawArea.x + fix_draw_pixel_offset_x;
	int offset = 0;
    if(MC->objData.moveCD % 256 < 128)	offset = 0;
    else if(MC->objData.moveCD % 256 >= 128)	offset = 64;
    switch(MC->objData.facing)
    {
        
        case LEFT:

            al_draw_scaled_bitmap(MC -> MCMoveSprite, 0 + offset, 64,
                64, 64,
                drawArea.x + fix_draw_pixel_offset_x, drawArea.y + fix_draw_pixel_offset_y,
                draw_region, draw_region, 0
            );
            break;
        case RIGHT:
            al_draw_scaled_bitmap(MC -> MCMoveSprite, 0 + offset, 128,
                64, 64,
                drawArea.x + fix_draw_pixel_offset_x, drawArea.y + fix_draw_pixel_offset_y,
                draw_region, draw_region, 0
            );
            break;
        case UP:
            al_draw_scaled_bitmap(MC -> MCMoveSprite, 0 + offset, 192,
                64, 64,
                drawArea.x + fix_draw_pixel_offset_x, drawArea.y + fix_draw_pixel_offset_y,
                draw_region, draw_region, 0
            );
            break;
        case DOWN:
            al_draw_scaled_bitmap(MC -> MCMoveSprite, 0 + offset, 0,
                64, 64,
                drawArea.x + fix_draw_pixel_offset_x, drawArea.y + fix_draw_pixel_offset_y,
                draw_region, draw_region, 0
            );
            break;
        case NONE:
            al_draw_scaled_bitmap(MC -> MCMoveSprite, 0, 0,
                64, 64,
                drawArea.x + fix_draw_pixel_offset_x, drawArea.y + fix_draw_pixel_offset_y,
                draw_region, draw_region, 0
            );
            break;
        default:
            al_draw_scaled_bitmap(MC -> MCMoveSprite, 0, 0,
                64, 64,
                drawArea.x + fix_draw_pixel_offset_x, drawArea.y + fix_draw_pixel_offset_y,
                draw_region, draw_region, 0
            );
            break;
    }
}
void MCMove(Maincharacter* MC){
    if (!movetime(MC->speed))
		return;

	int probe_x = MC->objData.Coord.x, probe_y = MC->objData.Coord.y;
    MC->objData.preMove = MC->objData.nextTryMove;
	switch (MC->objData.preMove)
	{
    game_log("MC Move");
	case UP:
		MC->objData.Coord.y -= 1;
		MC->objData.preMove = UP;
		break;
	case DOWN:
		MC->objData.Coord.y += 1;
		MC->objData.preMove = DOWN;
		break;
	case LEFT:
		MC->objData.Coord.x -= 1;
		MC->objData.preMove = LEFT;
		break;
	case RIGHT:
		MC->objData.Coord.x += 1;
		MC->objData.preMove = RIGHT;
		break;
	default:
		break;
	}
	MC->objData.facing = MC->objData.preMove;
	MC->objData.moveCD = MC -> speed;
}
void MCNextMove(Maincharacter* MC, Directions next){
    MC -> objData.nextTryMove = next;
}