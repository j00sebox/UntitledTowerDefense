#include "SpawnManager.h"

float SpawnManager::spawn_timer = 0.0f;
float SpawnManager::time_to_spawn = 3000.0f;

void SpawnManager::spawn(float delta, float& _x, float& _y, std::vector<EnemyPtr>& enemies, std::vector<Cell>& _path, Base& _base, Grid& _grid)
{
	// if enough time has elapsed pick an enemy to spawn
	if (spawn_timer >= time_to_spawn)
	{
		EnemyTypes choice = (EnemyTypes)( rand() % (int)EnemyTypes::LAST);
		switch (choice)
		{
			case EnemyTypes::REAVER:
			{
				enemies.emplace_back(new Reaver(_x, _y, _path, _base, _grid));
				break;
			}
			case EnemyTypes::SCOUT:
			{
				enemies.emplace_back(new Scout(_x, _y, _path, _base, _grid));
				break;
			}
			case EnemyTypes::BRUTE:
			{
				enemies.emplace_back(new Brute(_x, _y, _path, _base, _grid));
				break;
			}
		}
		
		spawn_timer = 0.0f;
	}
	else
	{
		spawn_timer += delta;
	}
}


void SpawnManager::spawn_destroyer(float& _x, float& _y, std::vector<EnemyPtr>& enemies, std::vector<Cell>& _path, Base& _base, Grid& _grid)
{
	enemies.emplace_back(new Destroyer(_x, _y, _path, _base, _grid));
}

void SpawnManager::difficulty_modifier(float& _x, float& _y, std::vector<EnemyPtr>& enemies, std::vector<Cell>& _path, Base& _base, Grid& _grid)
{
	spawn_destroyer(_x, _y, enemies, _path, _base, _grid);
	Enemy::healh_modifier += 10;
	Enemy::damage_modfier += 1;
	Enemy::speed_modifier += 0.2f;
}