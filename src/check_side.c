/*
** EPITECH PROJECT, 2018
** LemiPC
** File description:
** Checks for collision
*/

#include "lemipc.h"

int check_left(int **map, player_t *player)
{
	int posx = player->posx;
	int posy = player->posy;

	if (posy > 0)
		return (map[posx][posy - 1]);
	return (0);
}

int check_right(int **map, player_t *player)
{
	int posx = player->posx;
	int posy = player->posy;

	if (posy < MAP_HEIGHT)
		return (map[posx][posy + 1]);
	return (0);
}

int check_down(int **map, player_t *player)
{
	int posx = player->posx;
	int posy = player->posy;

	if (posx < MAP_WIDTH)
		return (map[posx + 1][posy]);
	return (0);
}

int check_up(int **map, player_t *player)
{
	int posx = player->posx;
	int posy = player->posy;

	if (posx > 0)
		return (map[posx - 1][posy]);
	return (0);
}