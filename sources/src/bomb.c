#include <SDL/SDL_image.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <constant.h>
#include <misc.h>
#include <sprite.h>
#include <window.h>

#include <map.h>
#include <bomb.h>
#include <player.h>

struct bomb{
    int x;
    int y;
    int bomb_timer;
    int dropped; // 0 (the bomb is not droped)
                // 1 (the bomb is droped)
};

struct player {
	int x, y;
	enum direction direction;
	int bombs;
};

void drop_bomb(struct map *map, struct player *player){

    
    player->bombs = player_get_nb_bomb(player) - 1;
    int stock_bombs = player->bombs;
    struct bomb *tab_bomb = map_get_tab_bomb(map);
    (&tab_bomb[stock_bombs])->dropped = 1;

    int x = player_get_x(player);
    int y = player_get_y(player);

    (&tab_bomb[stock_bombs])->x = x;
    (&tab_bomb[stock_bombs])->y = y;
    //printf("%d\n",(&tab_bombs[stock_bombs])->y );

    map_set_cell_type(map, x, y, CELL_BOMB_4);
}

void set_bomb(struct bomb*bomb){
    assert(bomb);
    bomb->bomb_timer = 400000 + SDL_GetTicks();
    bomb->dropped = 0;
}

void bomb_init_tab(struct bomb* bomb_tab){
    for (int i = 0; i < 9; i++){
		//bomb* bomb_init(int x, int y)
        set_bomb(&bomb_tab[i]);
    }
}

/*
int bomb_get_x(struct bomb *bomb){
    assert(bomb);
    return bomb->x;
}

int bomb_get_y(struct bomb *bomb){
    assert(bomb);
    return bomb->y;
}
*/

int get_bomb_timer(struct bomb *bomb){
    assert(bomb);
    return bomb->bomb_timer;
}

void bomb_update(struct map* map, struct player* player){ //update all the bombs
	struct bomb* tab_bombs = map_get_tab_bomb(map);
    
    for (int i = 0; i < 9; i++){
		
        if ((&tab_bombs[i])->bomb_timer > 0 && (&tab_bombs[i])->dropped == 1){
			bomb_update_aux(&tab_bombs[i], map, player);
		}
	}
}

void bomb_update_aux(struct bomb *bomb, struct map* map, struct player* player){

        int x = bomb->x;
        int y = bomb->y;

        int time = get_bomb_timer(bomb);
        //printf("%d\n", time);
        bomb->bomb_timer = time - SDL_GetTicks();
        //printf("%d", time);
        //printf("%d %d %d\n", (&tab_bombs[0])->bomb_timer, (&tab_bombs[1])->bomb_timer, (&tab_bombs[2])->bomb_timer);
        time = get_bomb_timer(bomb);
        
        if((time < 0)){
            //free(bomb);
            //map_set_cell_type(map, x, y, CELL_EXPLOSION);
        }
        if((time <= 100000)&&(time > 0)){
            //printf("%d\n", SDL_GetTicks());
            map_set_cell_type(map, x, y, CELL_BOMB_1);
        }
        if((time <= 200000)&&(time > 100000)){
            map_set_cell_type(map, x, y, CELL_BOMB_2);
        }
        if((time <= 300000)&&(time > 200000)){
            map_set_cell_type(map, x, y, CELL_BOMB_3);
        }
        if((time <= 400000)&&(time > 300000)){
            map_set_cell_type(map, x, y, CELL_BOMB_4);
        }
}

