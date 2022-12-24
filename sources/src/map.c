/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
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

struct map {
	int width;
	int height;
	unsigned char* grid;
	int lives_of_monster;
	int speed_monster;
	int timer_monster;
	//struct monster *monster_tab;
	struct bomb *tab_bomb;
	struct explosion *tab_explosion;
};

#define CELL(i,j) ( (i) + (j) * map->width)

struct map* map_new(int width, int height)
{
	assert(width > 0 && height > 0);

	struct map* map = malloc(sizeof *map);
	if (map == NULL )
		error("map_new : malloc map failed");

	map->width = width;
	map->height = height;

	map->grid = malloc(height * width);
	if (map->grid == NULL) {
		error("map_new : malloc grid failed");
	}

	// Grid cleaning
	int i, j;
	for (i = 0; i < width; i++)
	  for (j = 0; j < height; j++)
	    map->grid[CELL(i,j)] = CELL_EMPTY;

	// initialisation

	map->tab_bomb = malloc(9*sizeof(struct bomb*));
	map->tab_explosion = malloc(9*sizeof(struct explosion*));

	bomb_init_tab(map->tab_bomb);
	explosion_init_tab(map->tab_explosion);

	return map;
}

int map_is_inside(struct map* map, int x, int y)
{
	assert(map);
	return 1;
}

void map_free(struct map *map)
{
	if (map == NULL )
		return;
	free(map->grid);
	free(map);
}

struct bomb *map_get_tab_bomb(struct map *map){
	assert(map);
	return map->tab_bomb;
}

struct explosion *map_get_tab_explosion(struct map *map){
	assert(map);
	return map->tab_explosion;	
}

int map_get_width(struct map* map)
{
	assert(map != NULL);
	return map->width;
}

int map_get_height(struct map* map)
{
	assert(map);
	return map->height;
}

enum cell_type map_get_cell_type(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)] & 0xf0;
}

void map_set_cell_type(struct map* map, int x, int y, enum cell_type type)
{
	assert(map && map_is_inside(map, x, y));
	map->grid[CELL(x,y)] = type;
}

void display_bonus(struct map* map, int x, int y, unsigned char type)
{
	// bonus is encoded with the 4 most significant bits
	switch (type & 0x0f) {
	case BONUS_BOMB_RANGE_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_INC), x, y);
		break;

	case BONUS_BOMB_RANGE_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_DEC), x, y);
		break;

	case BONUS_BOMB_NB_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_DEC), x, y);
		break;

	case BONUS_BOMB_NB_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_NB_INC), x, y);
		break;
	}
}

void display_scenery(struct map* map, int x, int  y, unsigned char type)
{
	switch (type & 0x0f) { // sub-types are encoded with the 4 less significant bits
	case SCENERY_STONE:
		window_display_image(sprite_get_stone(), x, y);
		break;

	case SCENERY_TREE:
		window_display_image(sprite_get_tree(), x, y);
		break;
	}
}

void map_display(struct map* map)
{
	assert(map != NULL);
	assert(map->height > 0 && map->width > 0);

	int x, y;
	for (int i = 0; i < map->width; i++) {
	  for (int j = 0; j < map->height; j++) {
	    x = i * SIZE_BLOC;
	    y = j * SIZE_BLOC;

	    unsigned char type = map->grid[CELL(i,j)];
	    
	    switch (type & 0xf0) {
		case CELL_BOMB:
		  bomb_display(map, x, y, type);
		  break;
		case CELL_SCENERY:
		  display_scenery(map, x, y, type);
		  break;
	    case CELL_BOX:
	      window_display_image(sprite_get_box(), x, y);
	      break;
	    //case CELL_BONUS:
	      //display_bonus(map, x, y, type);
	      //break;
	    case CELL_KEY:
	      window_display_image(sprite_get_key(), x, y);
	      break;
	    case CELL_DOOR:
	      // pas de gestion du type de porte
	      window_display_image(sprite_get_door_opened(), x, y);
	      break;
	    }
	  }
	}
}

void bomb_display(struct map *map, int x, int y, unsigned char type){

        assert(map != NULL);
		assert(map->height > 0 && map->width > 0);

		switch (type & 0x0f) {

		case BOMB_1:
			window_display_image(sprite_get_bombs(0), x, y); 
			break;
		case BOMB_2:
			window_display_image(sprite_get_bombs(1), x, y); 
			break;
		case BOMB_3:
			window_display_image(sprite_get_bombs(2), x, y); 
			break;
		case BOMB_4:
			window_display_image(sprite_get_bombs(3), x, y); 
			break;
		case BOMB_EXPLOSION:
			bomb_explosion(map, x, y);
			window_display_image(sprite_get_bombs(3), x * SIZE_BLOC, y * SIZE_BLOC); 
			break;

		}
	}

struct map* map_get_static(void)
{
	struct map* map = map_new(STATIC_MAP_WIDTH, STATIC_MAP_HEIGHT);

	unsigned char themap[STATIC_MAP_WIDTH * STATIC_MAP_HEIGHT] = {
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,
	  CELL_STONE, CELL_STONE, CELL_STONE, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_BOX, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_BOX, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_BOX, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_BOX, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_STONE, CELL_STONE, CELL_EMPTY, CELL_EMPTY, CELL_STONE, CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY , CELL_EMPTY, CELL_EMPTY, CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_TREE, CELL_BOX, CELL_TREE, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,  CELL_EMPTY, CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_TREE, CELL_TREE, CELL_TREE, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,  CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
	  CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_STONE,  CELL_EMPTY, CELL_EMPTY,
	  CELL_BOX, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE, CELL_STONE,  CELL_BOX_LIFE, CELL_EMPTY,
	  CELL_BOX,  CELL_EMPTY, CELL_DOOR, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,
		};

	for (int i = 0; i < STATIC_MAP_WIDTH * STATIC_MAP_HEIGHT; i++)
		map->grid[i] = themap[i];

	return map;
}


struct map* map_get_static_2(void)
{
	FILE *f;
  	int length;
  	int width;
  	int next_map[200];
  	int size;
  	int i;

  	f = fopen("map_2","r");

  	if(f==NULL){
    	printf("Unable to open the field\n");
  	}

  	fscanf(f, "%d:%d", &length, &width);
  	//printf("map size : %d x %d\n",width, length);
  	size = length*width;
	//printf("%d\n", size);
	
  	for(i=0; i<size; i++)
  	{	
		next_map[i] = 0;
  	}
	

	for(i=0; i<size; i++){
		fscanf(f, "%d", &next_map[i]);
	}

	struct map* map = map_new(width, length);

	for ( int i = 0; i < size; i++){
		switch(next_map[i]){

			case(0):
				map->grid[i] = CELL_EMPTY;
			break;

			case(17):
				map->grid[i] = CELL_STONE;
			break;

            case(18):
				map->grid[i] = CELL_TREE;
			break;

			case(48): // 110000
				map->grid[i] = CELL_DOOR;
			break;


		}
	}
		
	for (int i = 0; i < size; i++)
		map->grid[i] = next_map[i];

	return map;



  	fclose(f);
}


struct map* map_get_static_3(void)
{
	FILE *f;
  	int length;
  	int width;
  	int next_map[200];
  	int size;
  	int i;

  	f = fopen("map_3","r");

  	if(f==NULL){
    	printf("Unable to open the field\n");
  	}

  	fscanf(f, "%d:%d", &length, &width);
  	size = length*width;
	
  	for(i=0; i<size; i++)
  	{	
		next_map[i] = 0;
  	}
	

	for(i=0; i<size; i++){
		fscanf(f, "%d", &next_map[i]);
	}
	

  	fclose(f);

	struct map* map = map_new(width, length);

	for ( int i = 0; i < size; i++){
		switch(next_map[i]){

			case(0):
				map->grid[i] = CELL_EMPTY;
			break;

			case(17):
				map->grid[i] = CELL_STONE;
			break;

            case(18):
				map->grid[i] = CELL_TREE;
			break;
		}
	}
		
		

	for (int i = 0; i < size; i++)
		map->grid[i] = next_map[i];

	return map;
}



