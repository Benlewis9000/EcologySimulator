#pragma once

#include <set>
#include <random>
#include <cstdlib>
#include <ctime>

#include <glad/glad.h>

#include "Entity.h"
#include "ComponentManager.h"
#include "TextureManager.h"

class EntityManager {
	// No destructor, EntityManager does not own this resource
	ComponentManager* componentMgr;
	std::unique_ptr<std::set<Entity>> entities;
	std::random_device rd;

	Entity createEntity();
public:
	EntityManager(ComponentManager* componentMgr);

	const std::set<Entity>* getEntities() const;
	void deleteEntity(Entity entity);	// TODO define delete Entity - will need to remove from compMgr and from this list

	Entity generateTestSprite(float xPos, float yPos, float rotation, float velocity);

};

