#include "Entity.h"

#include "Application.h"
#include "ModuleRender.h"

#include <SDL_render.h>

bool Entity::debug_draw = true;

Entity::Entity()
{
}

Entity::Entity(SDL_Rect rect, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	rect(rect), texture(texture), texture_death(texture_death), animation_death(animation_death), position(position), life_points(life_points), damage(damage), move_speed(move_speed)
{
	SetDefaultBoxCollider();
}

Entity::Entity(SDL_Rect rect, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	rect(rect), texture(texture), animation(animation), texture_death(texture_death), animation_death(animation_death), position(position), life_points(life_points), damage(damage), move_speed(move_speed)
{
	SetDefaultBoxCollider();
}

void Entity::Draw()
{
	if (debug_draw)
		DrawBoxCollider();

	App->renderer->Draw(texture, position, &rect);
}

void Entity::DrawAnimation()
{
	if (debug_draw)
		DrawBoxCollider();

	App->renderer->Draw(texture, position, &(animation.GetCurrentFrame()));
}

bool Entity::CompareType(Type type) const
{
	return this->type == type;
}

SDL_Rect Entity::GetBoxCollider() const
{
	return box_collider;
}

fPoint Entity::GetPosition() const
{
	return position;
}

void Entity::SetPosition(fPoint position)
{
	this->position = position;
}

void Entity::SetBoxCollider(SDL_Rect rect_collider)
{
	box_collider = rect_collider;
}

void Entity::UpdateBoxCollider()
{
	box_collider.x = position.x;
	box_collider.y = position.y;
}

void Entity::SetDefaultBoxCollider()
{
	box_collider.x = position.x;
	box_collider.y = position.y;
	box_collider.w = rect.w;
	box_collider.h = rect.h;
}

void Entity::DrawBoxCollider()
{
	SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(&App->renderer->GetRenderer(), &box_collider);
}
