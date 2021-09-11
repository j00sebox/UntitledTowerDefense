#include "Tower.h"

void Tower::draw()
{
	for (Projectile& p : projectiles)
	{
		p.sprite->Draw();
	}

	grid->draw_cell( location.x, location.y, r, g, b);
	App::Print( location.x  + grid->get_cell_width()  / 3.0f, location.y + grid->get_cell_height() / 3.0f, c, 0.0, 0.0, 0.0);
}

// shoot projectile at certain enemey
void Tower::shoot(EnemyPtr& e, float delta)
{
	if (attack_timer >= time_to_attack)
	{
		// creates projectile frame based off the frame
		Projectile projectile;
		projectile.sprite = std::shared_ptr<CSimpleSprite>(App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12));
		projectile.sprite->SetFrame(frame);
		projectile.sprite->SetScale(1.0f);
		projectile.e = e;

		// initial position of projectile is tower position
		projectile.x = location.x;
		projectile.y = location.y;

		// calculate initial direction of the projectile
		projectile.dirx = (e->get_x() - projectile.x) * speed;
		projectile.diry = (e->get_y() - projectile.y) * speed;

		// angle to rotate sprite offset by 90 degrees
		projectile.angle = atan2(projectile.diry, projectile.dirx) - PI/2;

		projectiles.push_back(projectile);

		attack_timer = 0.0f;
	}

	attack_timer += delta;
}

void Tower::update_projectiles()
{

	// remove projectiles that are offscreen or have collided with an enemy
	projectiles.erase(
		std::remove_if(
			projectiles.begin(),
			projectiles.end(),
			[](Projectile& p) { return ( p.out_of_bounds() || p.collided ); }
	), projectiles.end());

	// update positions
	for (Projectile& p : projectiles)
	{
		p.x += p.dirx;
		p.y += p.diry;

		p.sprite->SetPosition(p.x + xOff, p.y + yOff);
		p.sprite->SetAngle(p.angle);
	}
}

// calculates collision between projectile and given enemy
bool Tower::check_if_hit(EnemyPtr& e)
{
	bool hit = false;
	float rsq = (e->get_hit_radius() + proj_rad) * (e->get_hit_radius() + proj_rad);
	for (Projectile& p : projectiles)
	{
		if (CollisionManager::check_collison(e->get_x(), e->get_y(), p.x, p.y, rsq))
		{
			e->take_damage(damage);
			hit = true;
			p.collided = true;
		}
	}

	return hit;
}