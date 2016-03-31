#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "creatures.h"
#include <Windows.h>

int main()
{
	// Input
	char tmp[80];
	printf("\nEnter the name of our hero: ");
	scanf_s("%s", tmp, 80);

	printf("\nEnter combat stats for %s: (hp min max armor)", tmp);
	int hp, atk_max, atk_min, armor;
	scanf_s("%d %d %d %d", &hp, &atk_min, &atk_max, &armor);

	Hero *hero = new Hero(hp+1, atk_min+1, atk_max+1, armor+1, 0, 0, 1);
	hero->name = tmp;

	// Game Objects 
	Globals *g = new Globals(false, 0, 0); 

	g->average_damage = 0;

	// Main Loop
	srand(time(NULL));
	while (g->end == false)
	{
		int tmp_goblins;

		// Seting Round values----------
		tmp_goblins = rand() % 6 + 1;
		g->round++;
		g->all_goblins_dead = false;
		g->goblins_killed = 0;

		printf("\n%s, in the round %d you will fight against %d goblin/s.\n\n", hero->name, g->round, tmp_goblins);
		
		// Create the enemy wave--------
		Goblin *goblins = new Goblin[tmp_goblins];

		for (int i = 0; i < tmp_goblins; i++)
		{
			goblins[i].hp = rand() % (hero->hp/2) + 1;
			goblins[i].attack_max = rand() % ((hero->attack_max / 4) * g->round) + 1;
			goblins[i].attack_min = rand() % ((hero->attack_min / 4) * g->round) + 1;
			goblins[i].armor = rand() % (hero->armor / 2) + 1;
			goblins[i].coins = 30 + g->round * 2;
			goblins[i].xp = 5 * g->round;
			//printf("The goblin %d: hp: %d, maxAt: %d, minAt: %d, armor: %d, coins: %d, xp: %d\n", i+1, goblins[i].hp, goblins[i].attack_max, goblins[i].attack_min, goblins[i].armor, goblins[i].coins, goblins[i].xp);
		}

		// Fight the Wave---------------
		while (g->all_goblins_dead == false)
		{
			// Don't atack a dead goblin----
			g->goblin_dead = true;
			int tmp_atack;

			while (g->goblin_dead == true)
			{
				tmp_atack = rand() % tmp_goblins;
				if (tmp_atack == tmp_goblins)
					tmp_atack -= 1;
				if (goblins[tmp_atack].hp <= 0)
					g->goblin_dead = true;
				else
					g->goblin_dead = false; 
			}

			// Hero attack to random enemy---
			system("pause");

			int tmp_hero_atack = hero->Attack(goblins[tmp_atack]) + hero->level * 2;
			g->average_damage += tmp_hero_atack;

			printf("\n-> You atack the goblin number %d and deal %d of damage.\n", tmp_atack+1, tmp_hero_atack);

			// Loot--------------------------
			if (goblins[tmp_atack].hp <= 0)
			{ 
				printf("\nYou killed the goblin %d, gained %d exp and %d coins.\n", tmp_atack+1, goblins[tmp_atack].xp, goblins[tmp_atack].coins); 
				hero->xp += goblins[tmp_atack].xp; //take xp
				hero->coins += goblins[tmp_atack].coins; //take coins
				
				g->goblins_killed++; 
				g->all_goblins_killed++;	
			}

			// Level up?---------------------
			if (hero->xp >= (hero->level * 15 * 2))
			{
				printf("\n%s you level up! Now you are level %d\nYou restored %d hp", hero->name, ++hero->level, (hero->hp/10 * hero->level));
				hero->hp += (hero->hp / 10 * hero->level);
			}
				
			
			// Finish round?-----------------
			if (g->goblins_killed == tmp_goblins)
			{
				printf("\nYou killed all the goblins from the round %d.\n\n", g->round);
				
				delete[] goblins; //free to realloc
				g->all_goblins_dead = true;
				system("pause");
				break;
			}

			// Monsters Attack---------------
			printf("---------------------\n");
			for (int i = 0; i < tmp_goblins; i++)
			{
				if (goblins[i].hp > 0)
				{
					printf("The goblin %d hit you and deal %d of damage. HP: %d\n", i + 1, goblins[i].Attack(goblins[i], *hero), goblins[i].hp);
				}
			}
			printf("---------------------\n");

			if (hero->hp < 0)
				hero->hp = 0;
			printf("\nYou have %d hp and %d xp.\n\n", hero->hp, hero->xp);

			// You are dead?-----------------
			if (hero->hp == 0)
			{
				printf("You are dead.\n\nIn this game you have killed %d goblins.\nYou won %d coins.\nYou won %d exp.\nTou dealt %d of average damage/round.", g->all_goblins_killed, hero->coins, hero->xp, (g->average_damage/g->round));
				delete[] goblins; //free to end
				g->end = true;
				break;
			}
		}
	}

	// Free and End
	delete hero;
	delete g;
	
	printf("\nBye :)\n");
	system("pause");

	return 0;
}
