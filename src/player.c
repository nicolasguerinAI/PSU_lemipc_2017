/*
** EPITECH PROJECT, 2018
** LemiPC
** File description:
** Player
*/

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include "lemipc.h"

player_t *create_player_sem(player_t *player)
{
	player->semid = semget(player->key, 1, SHM_R | SHM_W);
	if (player->semid == -1) {
		player->semid = semget(player->key, 1,
			IPC_CREAT | SHM_R | SHM_W);
		semctl(player->semid, 0, SETVAL, 1);
	} else {
		semctl(player->semid, 0, IPC_RMID);
		player->semid = semget(player->key, 1,
			IPC_CREAT | SHM_R | SHM_W);
	}
	return (player);
}

player_t *init_player(player_t *player, int team)
{
	player = malloc(sizeof(player_t));
	if (player == NULL)
		return (NULL);
	player->team = team;
	player->is_alive = true;
	player->is_host = false;
	srand(time(0));
	player->posx = rand() % MAP_WIDTH;
	player->posy = rand() % MAP_HEIGHT;
	return (player);
}

int     find_occurence(const int map[8], int value)
{
        int nb_occurence = 0;

        for (int i = 0; i < 8; ++i) {
                if (value == map[i])
                        ++nb_occurence;
        }
        return nb_occurence;
}

bool	check_killed(player_t *player, int **map)
{
        int occurence = 0;
        int next_to[8] = {check_up(map, player),
                          check_right(map, player),
                          check_down(map, player),
                          check_left(map, player),
                          check_diag_up_right(map, player),
                          check_diag_down_right(map, player),
                          check_diag_down_left(map, player),
                          check_diag_up_left(map, player)};

        for (int i = 0; i < 8; ++i) {
                occurence = find_occurence(next_to, next_to[i]);
                if (occurence > 1) {
                        return (true);
                }
        }

	return (false);
}

int	**suicide(player_t *player, int **map)
{
	semctl(player->semid, 0, IPC_RMID);
	map[player->posx][player->posy] = 0;
        return (map);
}

