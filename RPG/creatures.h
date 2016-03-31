#pragma once

#ifndef __CREATURES_H__
#define __CREATURES_H__

#include<stdlib.h>

class Creature
{
public:
	int hp;
	int attack_min;
	int attack_max;
	int armor;
	int coins;
	int xp;
public:
	Creature(int _hp, int _attack_min, int _attack_max, int _armor, int _coins, int _xp);
	~Creature();
	Creature(){};
};

class Hero : public Creature
{
public:
	char* name;
	int Attack(Creature& target);
	int level;
	Hero(int _hp, int _attack_min, int _attack_max, int _armor, int _coins, int _xp, int _level);
	~Hero();
};

class Goblin : public Creature
{
public:
	int Attack(Creature& target, Creature& hero);
	Goblin(){};
	~Goblin();
};

class Globals
{
public:
	bool end; // end game
	int round; // current round
	int num_goblins; // number of goblins on the current round
	int goblins_killed; // goblins killed on the current round
	bool all_goblins_dead;
	bool goblin_dead;
	int all_goblins_killed = 0; // all goblins killed
	int average_damage; //average damage 
	Globals(bool _end, int _round, int _num_goblins);
};
#endif // __CREATURES_H__
