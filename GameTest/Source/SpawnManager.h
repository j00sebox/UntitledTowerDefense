#ifndef _SPAWN_MAN
#define _SPAWN_MAN

#include <stdlib.h>
#include <time.h> 

#include "Enemy.h"
#include "Reaver.h"
#include "Scout.h"
#include "Brute.h"
#include "Destroyer.h"

class SpawnManager
{
public:

	static void spawn(float delta, float& _x, float& _y, std::vector<EnemyPtr>& enemies, std::vector<Cell>& _path, Base& _base, Grid& _grid);

	static void difficulty_modifier(float& _x, float& _y, std::vector<EnemyPtr>& enemies, std::vector<Cell>& _path, Base& _base, Grid& _grid);

private:

	static void spawn_destroyer(float& _x, float& _y, std::vector<EnemyPtr>& enemies, std::vector<Cell>& _path, Base& _base, Grid& _grid);

	static float spawn_timer;
	static float time_to_spawn;
	static float speed_modifier;
	static int damage_modfier;
	static int healh_modifier;
	
	// basic enemy types
	enum class EnemyTypes
	{
		REAVER,
		SCOUT,
		BRUTE,
		LAST,
	};
};

#endif
