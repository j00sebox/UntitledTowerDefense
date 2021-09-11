#include "GameOverManager.h"

bool GameOverManager::game_over = false;

void GameOverManager::end_game()
{
	App::Print(450.0, 384.0, "GAME OVER", 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24);
}