#include "Creature.h"

#include "Application.h"
#include "ModuleRender.h"

#include <SDL_render.h>

Creature::Creature(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed) :
	Entity(texture, rect, position, health), damage(damage), speed(speed)
{
}

void Creature::UpdateBoxCollider()
{
	box_collider.x = position.x;
	box_collider.y = position.y;
}

int Creature::GetDamage() const
{
	return damage;
}
