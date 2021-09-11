#include "Base.h"

void Base::update_healthbar()
{
	float _x = hb->healthx;
	float _y = hb->healthy;
	float _xOff = hb->healthx + (hb->xOff * health / 100);
	float _yOff = hb->healthy + hb->yOff;

#if APP_USE_VIRTUAL_RES		
	APP_VIRTUAL_TO_NATIVE_COORDS(_xOff, _yOff);
	APP_VIRTUAL_TO_NATIVE_COORDS(_x, _y);
#endif

	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.0f, 0.0f);
	glVertex2f(_x, _y);
	glVertex2f(_xOff, _y);
	glVertex2f(_xOff, _yOff);
	glVertex2f(_x, _yOff);
	glEnd();

	App::Print(hb->healthx - 100, hb->healthy, "HEALTH: ", 0.3f, 0.0f, 0.0f);
}

void Base::take_damage(int _dam)
{
	if ( (health - _dam) > 0)
	{
		health -= _dam;
	}
	else
	{
		health = 0;
		GameOverManager::game_over = true;
	}
}

void Base::display_money()
{
	sprintf(money_buff, "MONEY: %i", money);

	App::Print(800, 700, money_buff, 0.3f, 0.7f, 0.0f);
}

void Base::display_kills()
{
	sprintf(kills_buff, "KILLS: %i", kills);

	App::Print(800, 650, kills_buff, 0.7f, 0.0f, 0.0f);
}