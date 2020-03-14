#include "Bullet.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneGame.h"

#include <SDL_rect.h>

Bullet::Bullet(SDL_Texture* texture, SDL_Rect rect, fPoint position, int health, int damage, float speed) :
	Creature(texture, rect, position, health, damage, speed)
{
	type = Type::BULLET;
	SetActive(false);
}

Bullet::~Bullet()
{
}

UpdateStatus Bullet::Update(float delta_time)
{
	position.y -= speed * delta_time;

	Creature::UpdateBoxCollider();

	Entity::DrawBoxCollider();
	Entity::DrawEntity();

	// Collisions
	auto entities = App->sceneGame->GetEntities();//TODO hacer lista sin bullets para ahorrar calculos

	for (auto& entity : entities)
	{
		if (!entity->IsActive()) continue;

		if (entity->CompareTag(Type::ASTEROID))
		{
			if (SDL_HasIntersection(&box_collider, &entity->GetBoxCollider()))
			{
				SetActive(false);
				entity->ReceiveDamage(1);

				//entity->health--;

				//if (entity->health < 1)
				//	App->sceneGame->RemoveEntity(entity);

				break;
			}
		}
	}

	if (position.y < rect.w)
		SetActive(false);

	return UpdateStatus::CONTINUE;
}
