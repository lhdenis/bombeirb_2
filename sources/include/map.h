/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
#ifndef MAP_H_
#define MAP_H_

#include <game.h>
#include <player.h>
#include <bomb.h>
#include <map.h>

struct map;

enum cell_type {
	CELL_EMPTY=0x00,   		//  0000 0000
	CELL_SCENERY=0x10, 		//  0001 0000
	CELL_BOX=0x20,   		//  0010 0000
	CELL_DOOR=0x30,      	//  0011 0000
	CELL_KEY=0x40,       	//  0100 0000
	CELL_BONUS=0x50, 		// 	0101 0000
	CELL_MONSTER=0x60, 		// 	0110 0000
	CELL_BOMB=0x70 	   		// 	0111 0000

};

enum bomb_type {
	BOMB_1 = 1, // 0001
	BOMB_2 = 2, // 0010
	BOMB_3 = 4, // 0100
	BOMB_4 = 8, // 1000
	BOMB_EXPLOSION = 9 // 1001
};

enum bonus_type {
	BONUS_BOMB_RANGE_DEC=1,
	BONUS_BOMB_RANGE_INC,
	BONUS_BOMB_NB_DEC,
	BONUS_BOMB_NB_INC,
	BONUS_MONSTER,
	BONUS_LIFE
};

enum scenery_type {
	SCENERY_STONE = 1,    // 0001 
	SCENERY_TREE  = 2,    // 0010 
	SCENERY_PRINCESS = 4  // 0100 
};

enum compose_type {
	CELL_TREE     = CELL_SCENERY | SCENERY_TREE,
	CELL_STONE    = CELL_SCENERY | SCENERY_STONE,
	CELL_PRINCESS = CELL_SCENERY | SCENERY_PRINCESS,

    CELL_BOX_RANGEINC = CELL_BOX | BONUS_BOMB_RANGE_DEC,
    CELL_BOX_RANGEDEC = CELL_BOX | BONUS_BOMB_RANGE_INC,
	CELL_BOX_BOMBINC  = CELL_BOX | BONUS_BOMB_NB_DEC,
    CELL_BOX_BOMBDEC  = CELL_BOX | BONUS_BOMB_NB_INC,
    CELL_BOX_LIFE     = CELL_BOX | BONUS_MONSTER,
    CELL_BOX_MONSTER  = CELL_BOX | BONUS_LIFE,

	CELL_BOMB_1 = CELL_BOMB | BOMB_1,
	CELL_BOMB_2 = CELL_BOMB | BOMB_2,
	CELL_BOMB_3 = CELL_BOMB | BOMB_3,
	CELL_BOMB_4 = CELL_BOMB | BOMB_4,
	CELL_EXPLOSION = CELL_BOMB | BOMB_EXPLOSION,

};

// Create a new empty map
struct map* map_new(int width, int height);
void map_free(struct map* map);


// Return the height and width of a map
int map_get_width(struct map* map);
int map_get_height(struct map* map);

// Return the type of a cell
enum cell_type map_get_cell_type(struct map* map, int x, int y);

// Set the type of a cell
void  map_set_cell_type(struct map* map, int x, int y, enum cell_type type);

// Test if (x,y) is within the map
int map_is_inside(struct map* map, int x, int y);

// Return a default static map
struct map* map_get_static();
struct map* map_get_static_2();
struct map* map_get_static_3();

// Display the map on the screen
void map_display(struct map* map);

void bomb_display(struct map *map, int x, int y, unsigned char type);

struct bomb *map_get_tab_bomb(struct map *map);

struct explosion *map_get_tab_explosion(struct map *map);

#endif /* MAP_H_ */
