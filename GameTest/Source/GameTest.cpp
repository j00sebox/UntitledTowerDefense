//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  

//------------------------------------------------------------------------
#include "Tower.h"
#include "MachineGun.h"
#include "Sniper.h"
#include "Blaster.h"
#include "Launcher.h"
#include "Enemy.h"
#include "Reaver.h"
#include "Scout.h"
#include "SpawnManager.h"
#include "Search.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------

/**************************GLOBALS**************************/

Grid g(50, 50);
float click_timer = 0.0f;
float spawn_timer = 0.0f;
float game_time = 0.0f;
float modify_timer = 0.0f;
float time_to_spawn = 3000.0f;
Cell start = g.cells[0][8];
Base base(g.cells[18][8]);
std::vector<TowerPtr> towers;
std::vector<EnemyPtr> enemies;
std::vector<Cell> path;
bool collision_flag = false;
SelectedTower selection = SelectedTower::MACHINE_GUN;
bool paused = false;
bool menu = false;
float mouseX, mouseY;
int path_price = 50;


/**********************************************************/

void show_menu()
{
	App::Print(100, 700, "CONTROLS:", 1.0, 1.0, 1.0);
	App::Print(100, 675, "LMB - Place new path or get rid of existing path. Path must always connect to the base in some way.", 1.0, 1.0, 1.0);
	App::Print(100, 650, "RMB - Place or remove tower. The type of tower placed depends on the current selection.", 1.0, 1.0, 1.0);
	App::Print(100, 625, "1 - Select machine gun tower.", 1.0, 1.0, 1.0);
	App::Print(100, 600, "2 - Select sniper tower.", 1.0, 1.0, 1.0);
	App::Print(100, 575, "3 - Select blaster tower.", 1.0, 1.0, 1.0);
	App::Print(100, 550, "4 - Select launcher tower.", 1.0, 1.0, 1.0);
	App::Print(100, 525, "P - Pause game. In this mode the path and towers can be updated.", 1.0, 1.0, 1.0);
	App::Print(100, 500, "M - Enters this menu. Press again to exit.", 1.0, 1.0, 1.0);

	App::Print(100, 400, "PRICES:", 1.0, 1.0, 1.0);
	App::Print(100, 375, "MACHINE GUN: 15", 1.0, 1.0, 1.0);
	App::Print(100, 350, "SNIPER: 30", 1.0, 1.0, 1.0);
	App::Print(100, 325, "BLASTER: 50", 1.0, 1.0, 1.0);
	App::Print(100, 300, "LAUNCHER: 100", 1.0, 1.0, 1.0);
	App::Print(100, 275, "ADD PATH: 50", 1.0, 1.0, 1.0);
}

void show_tower_selection()
{

	App::Print(0, 650, "Current Tower: ", 0.0, 0.0, 0.0);

	switch (selection)
	{
		case SelectedTower::MACHINE_GUN:
		{
			App::Print(150, 650, "MACHINE GUN", 0.5f, 0.0f, 0.7f);
			break;
		}
		case SelectedTower::SNIPER:
		{
			App::Print(150, 650, "SNIPER", 0.0f, 0.5f, 0.7f);
			break;
		}
		case SelectedTower::BLASTER:
		{
			App::Print(150, 650, "BLASTER", 0.7f, 0.3f, 0.0f);
			break;
		}
		case SelectedTower::LAUNCHER:
		{
			App::Print(150, 650, "LAUNCHER", 0.7f, 0.7f, 0.7f);
			break;
		}
	}
}


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	srand(time(NULL));

	// default starting path
	g.path.insert({ start, g.cells[1][8], g.cells[2][8], g.cells[3][8],
		g.cells[4][8], g.cells[5][8], g.cells[6][8], g.cells[7][8], g.cells[8][8],
		g.cells[9][8], g.cells[10][8], g.cells[11][8], g.cells[12][8], g.cells[13][8],
		g.cells[14][8], g.cells[15][8], g.cells[16][8], g.cells[17][8] });

	g.base = *base.get_cell(); 

	std::unordered_map<Cell, Cell> connections;

	Search::a_star(g, start, g.base, connections);

	path = Search::get_path(connections, start, g.base);
	
	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	/**START**/
	if (!GameOverManager::game_over)
	{
		// total elapsed time playing
		game_time += deltaTime;

		// timer prevents unintended multiple clicks
		click_timer += deltaTime;

		// if key 'M' is pressed
		if (App::IsKeyPressed(0x4D) && click_timer >= 300)
		{
			menu = !menu;
			click_timer = 0.0f;
		}

		// if the menu isn't up
		if (!menu)
		{
			// if key 'P' is pressed
			if (App::IsKeyPressed(0x50) && click_timer >= 300)
			{
				paused = !paused;

				click_timer = 0.0f;
			}

			// if key '1' is pressed
			if (App::IsKeyPressed(0x31) && click_timer >= 300)
			{
				selection = SelectedTower::MACHINE_GUN;
				click_timer = 0.0f;
			}

			// if key '2' is pressed
			if (App::IsKeyPressed(0x32) && click_timer >= 300)
			{
				selection = SelectedTower::SNIPER;
				click_timer = 0.0f;
			}

			// if key '3' is pressed
			if (App::IsKeyPressed(0x33) && click_timer >= 300)
			{
				selection = SelectedTower::BLASTER;
				click_timer = 0.0f;
			}

			// if key '4' is pressed
			if (App::IsKeyPressed(0x34) && click_timer >= 300)
			{
				selection = SelectedTower::LAUNCHER;
				g.path.find(g.cells[8][0]);
				click_timer = 0.0f;
			}

			// left mouse button
			if (App::IsKeyPressed(VK_LBUTTON) && click_timer >= 300)
			{
				App::GetMousePos(mouseX, mouseY);

				Cell* c = g.get_cell(mouseX, mouseY);

				if (c != nullptr && !c->occupied)
				{
					std::unordered_map<Cell, Cell> connections;

					// if the cell clicked on is already in path and not being traversed it is removed
					if (g.in_path(*c))
					{
						if (!c->traversing)
						{
							g.remove_from_path(*c);

							// the cell cannot be removed unless there exists some way to get to the goal
							bool gf = Search::a_star(g, start, g.base, connections);

							// if there was a goal found with the additional path node we can sell it
							if (gf)
							{
								path = Search::get_path(connections, start, g.base);

								for (EnemyPtr& e : enemies)
								{
									e->update_path(path);
								}

								base.sell(path_price);
							}
							else // otherwise the cell needs to be added back to the path
							{
								g.add_to_path(*c);
							}
						}
					}
					else
					{
						// if it can be afforded add to path
						if (base.buy(path_price))
						{
							g.add_to_path(*c);

							Search::a_star(g, start, g.base, connections);

							path = Search::get_path(connections, start, g.base);

							for (EnemyPtr& e : enemies)
							{
								e->update_path(path);
							}
						}
					}
				}

				click_timer = 0.0f;
			}

			// right mouse button
			if (App::IsKeyPressed(VK_RBUTTON) && click_timer >= 300)
			{
				App::GetMousePos(mouseX, mouseY);

				Cell* c = g.get_cell(mouseX, mouseY);

				if (c != nullptr && !g.in_path(*c) && !g.is_base(*c))
				{
					// if no tower there buy one
					if (!c->occupied)
					{
						// if purchase was successful
						if (base.buy((int)selection))
						{
							switch (selection)
							{
								case SelectedTower::MACHINE_GUN:
								{

									towers.emplace_back(std::make_unique<MachineGun>(MachineGun(g, *c)));
									break;
								}
								case SelectedTower::SNIPER:
								{
									towers.emplace_back(std::make_unique<Sniper>(Sniper(g, *c)));
									break;
								}
								case SelectedTower::BLASTER:
								{
									towers.emplace_back(std::make_unique<Blaster>(Blaster(g, *c)));
									break;
								}
								case SelectedTower::LAUNCHER:
								{
									towers.emplace_back(std::make_unique<Launcher>(Launcher(g, *c)));
									break;
								}
							}

							c->occupied = true;
							c->st = selection;
						}
					}
					// already tower there so sell it
					else
					{
						base.sell((int)c->st);

						towers.erase(
							std::remove_if(
								towers.begin(),
								towers.end(),
								[&](TowerPtr& t) { return (t->get_cell() == *c); }
						), towers.end());

						// set back to default cell
						c->occupied = false;
						c->st = SelectedTower::NONE;
					}

				}

				click_timer = 0.0f;
			}

			// if not paused update enemies, towers, etc.
			if (!paused)
			{
				//------------------------------------------------------------------------
				modify_timer += deltaTime;
				
				// difficulty modifier
				if (modify_timer >= 30000.0)
				{
					SpawnManager::difficulty_modifier(start.x, start.y, enemies, path, base, g);

					modify_timer = 0.0;
				}

				// spawn enemies at specified interval
				SpawnManager::spawn(deltaTime, start.x, start.y, enemies, path, base, g);

				for (TowerPtr& t : towers)
				{
					float r = t->get_range();
					float p_rad = t->get_projectile_radius();
					for (EnemyPtr& e : enemies)
					{
						float er = e->get_hit_radius();
						float rsq = (r + er) * (r + er);

						// if an enemy is in range of the tower
						if (CollisionManager::check_collison(t->get_x(), t->get_y(), e->get_x(), e->get_y(), rsq))
						{
							t->shoot(e, deltaTime);
						}

						// this checks if the projectile hit the enemy
						t->check_if_hit(e);
					}

					// remove dead enemies from list before continuing 
					enemies.erase(
						std::remove_if(
							enemies.begin(),
							enemies.end(),
							[](EnemyPtr& e) { return e->is_dead(); }
					), enemies.end());


					// update position
					t->update_projectiles();
				}

				// move enemies along path
				for (EnemyPtr& e : enemies)
				{
					e->move(deltaTime);
				}
			}
		}
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	if (!GameOverManager::game_over)
	{

		if (menu)
		{
			show_menu();
		}
		else
		{
			g.draw_grid();

			for (TowerPtr& t : towers)
			{
				t->draw();
			}

			for (EnemyPtr& e : enemies)
			{
				e->display();
			}

			// update HUD
			base.update_healthbar();
			base.display_money();
			base.display_kills();
			App::Print(450, 700, "MENU [M]", 0.0, 0.0, 0.5);
			show_tower_selection();

			if (paused)
			{
				App::Print(450, 600, "PAUSED", 0.0, 0.0, 0.0);
			}
		}
		
	}
	else
	{
		// shows the game over screen
		GameOverManager::end_game();
	}

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
}