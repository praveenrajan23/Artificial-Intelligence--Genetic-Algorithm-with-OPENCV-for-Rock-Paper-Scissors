#ifndef GA_Player_H
#define GA_Player_H 1

#include "stdafx.h"

#define ROCK 2
#define PAPER 1
#define SCISSORS 0
#define population_size 10
#define chromosome_size 34
#define Game_Course 3
#define elite_pop 5

class Player
{
public:
	int chromosome[chromosome_size];
	int lamda;
	int fitness_value;
	Player();
	void Randomize();
};

#endif