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

	Entity newEntity();
public:
	inline EntityManager(ComponentManager* componentMgr);

	inline const std::set<Entity>* getEntities() const;

	Entity generateTestSprite(float xPos, float yPos, float rotation, float velocity);

};

/**
 * Construct an EntityManager.
 * 
 * @param componentMgr pointer to a ComponentManager to register an entities components with
 */
inline EntityManager::EntityManager(ComponentManager* componentMgr) : componentMgr(componentMgr) {

	this->entities = std::make_unique<std::set<Entity>>();

} 

/**
 * Get an immutable pointer to the managers entities.
 * 
 * @return std::set<Entity>* a pointer to the managers entities
 */
inline const std::set<Entity>* EntityManager::getEntities() const {

	return this->entities.get();

}