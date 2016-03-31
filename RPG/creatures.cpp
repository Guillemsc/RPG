#include "creatures.h"
#include <time.h>
#include <stdio.h>

// --------------------------------------------------------
Creature::Creature(int _hp, int _attack_min, int _attack_max, int _armor, int _coins, int _xp) : 
hp(_hp), attack_min(_attack_min), attack_max(_attack_max), armor(_armor), coins(_coins), xp(_xp) {};

// --------------------------------------------------------
Hero::Hero(int _hp, int _attack_min, int _attack_max, int _armor, int _coins, int _xp, int _level) :
Creature(_hp, _attack_min, _attack_max, _armor, _coins, _xp), level(_level){};

// --------------------------------------------------------
int Hero::Attack(Creature& target)
{
	srand(time(NULL));
	int damage = rand() % Hero::attack_max + Hero::attack_min;
	damage -= target.armor/4;
	if (damage < 0)
		damage = 0;
	target.hp -= damage;
	return damage;
}

// --------------------------------------------------------
int Goblin::Attack(Creature& target, Creature& hero)
{
	srand(time(NULL));
	int damage = rand() % target.attack_max + target.attack_min;
	damage -= hero.armor/4;
	if (damage < 0)
		damage = 0;
	hero.hp -= damage;
	return damage;
}
// --------------------------------------------------------
Globals::Globals(bool _end, int _round, int _num_goblins) : 
end(_end), round(_round), num_goblins(_num_goblins){};

// --------------------------------------------------------
Creature::~Creature()
{}

// --------------------------------------------------------
Hero::~Hero()
{}

// --------------------------------------------------------
Goblin::~Goblin()
{}

// --------------------------------------------------------
