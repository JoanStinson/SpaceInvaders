#include "Entity.h"

#include "Application.h"
#include "ModuleRender.h"

#include <SDL_render.h>

std::list<Entity*> Entity::entities;
bool Entity::debug_draw = true;

Entity::Entity(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health) :
	texture(texture), rect(rect), position(position), health(health)
{
	CreateBoxCollider();
}

void Entity::DrawEntity()
{
	if (debug_draw)
		DrawBoxCollider();

	App->renderer->Draw(texture, position, &rect);
}

void Entity::DrawBoxCollider()
{
	SDL_SetRenderDrawColor(&App->renderer->GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(&App->renderer->GetRenderer(), &box_collider);
}

void Entity::CreateBoxCollider()
{
	box_collider.x = position.x;
	box_collider.y = position.y;
	box_collider.w = rect.w;
	box_collider.h = rect.h;
}

void Entity::ReceiveDamage(int damage, callback on_death)
{
	health -= damage;

	if (health < 1 && on_death != nullptr)
	{
		on_death();
		//Remove entity
	}	
}

void Entity::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

void Entity::RemoveEntity(Entity* entity)
{
	entities.remove(entity);
	delete entity;
}

void Entity::SetActive(bool active)
{
	this->active = active;
}

void Entity::SetPosition(fPoint position)
{
	this->position = position;
}

void Entity::SetTexture(SDL_Texture* texture)
{
	this->texture = texture;
}

bool Entity::IsActive() const
{
	return active;
}

bool Entity::CompareType(Type type) const
{
	return this->type == type;
}

SDL_Rect Entity::GetBoxCollider() const
{
	return box_collider;
}
