#ifndef BOMB_H_
#define BOMB_H_

#include <player.h>
#include <bomb.h>
#include <map.h>

struct bomb;
struct player;
struct map;

void drop_bomb(struct map *map, struct player *player);

void bomb_init_tab(struct bomb*bomb);

void set_bomb(struct bomb*bomb);

//int bomb_get_x(struct bomb *bomb);

//int bomb_get_y(struct bomb *bomb);

void bomb_display(struct map *map, int x, int y, unsigned char type);

int get_bomb_timer(struct bomb *bomb);

void bomb_update(struct map* map, struct player* player);

void bomb_update_aux(struct bomb *bomb, struct map* map, struct player* player);

#endif /* BOMB_H_ */
