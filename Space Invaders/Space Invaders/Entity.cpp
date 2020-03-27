#include "Entity.h"

#include "Application.h"
#include "ModuleRender.h"

#include <SDL_render.h>

bool Entity::debug_draw = false;

Entity::Entity()
{
}

Entity::Entity(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	rect(rect), rect_collider(rect_collider), init_rect_collider(rect_collider), texture(texture), texture_death(texture_death), animation_death(animation_death), position(position), init_position(position),
	life_points(life_points), init_life_points(life_points), damage(damage), move_speed(move_speed)
{
	UpdateRectCollider();
}

Entity::Entity(SDL_Rect rect, SDL_Rect rect_collider, SDL_Texture* texture, Animation animation, SDL_Texture* texture_death, Animation animation_death, fPoint position, int life_points, int damage, float move_speed) :
	rect(rect), rect_collider(rect_collider), init_rect_collider(rect_collider), texture(texture), animation(animation), texture_death(texture_death), animation_death(animation_death), position(position), 
	init_position(position), life_points(life_points), init_life_points(life_points), damage(damage), move_speed(move_speed)
{
	UpdateRectCollider();
}

void Entity::Draw()
{
	App->render->Draw(*texture, position, rect);

	if (debug_draw)
		DrawRectCollider();
}

void Entity::DrawAnimation()
{
	App->render->Draw(*texture, position, animation.GetCurrentFrame());

	if (debug_draw)
		DrawRectCollider();
}

bool Entity::DrawAnimationDeath(bool condition_death)
{
	return DrawAnimationDeath(condition_death, position);
}

bool Entity::DrawAnimationDeath(bool condition_death, fPoint position_death)
{
	if (condition_death)
	{
		if (!animation_death.HasAnimationEnded())
		{
			App->render->Draw(*texture_death, position_death, animation_death.GetCurrentFrameOnce());
		}
		else
		{
			OnDeath();
		}
	}

	if (debug_draw)
		DrawRectCollider();

	return condition_death ? true : false;
}

bool Entity::CompareType(Type type) const
{
	return this->type == type;
}

SDL_Rect Entity::GetRectCollider() const
{
	return rect_collider;
}

fPoint Entity::GetPosition() const
{
	return position;
}

void Entity::SetPosition(fPoint position)
{
	this->position = position;
}

void Entity::UpdateRectCollider()
{
	rect_collider.x = position.x + init_rect_collider.x;
	rect_collider.y = position.y + init_rect_collider.y;
}

void Entity::Reset()
{
	position = init_position;
	life_points = init_life_points;
	enabled = true;
	alive = true;
}

void Entity::DrawRectCollider()
{
	SDL_SetRenderDrawColor(&App->render->GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(&App->render->GetRenderer(), &rect_collider);
}
