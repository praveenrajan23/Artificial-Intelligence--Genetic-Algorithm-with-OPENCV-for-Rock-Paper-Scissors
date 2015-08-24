#include "stdafx.h"
#include "GA_Player.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Player::Player()
{
	//Random population generation
	fitness_value = 0;
	lamda = 0;
	//	cout << "Chromosome : ";
	for (int j = 0; j < chromosome_size; j++)
	{
		chromosome[j] = rand() % 3;
		//cout << chromosome[j];

	}
	//cout << endl;

};
