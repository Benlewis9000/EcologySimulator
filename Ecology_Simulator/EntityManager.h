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
	void generateQuad(unsigned int& VBO, unsigned int& VAO, unsigned int& size);
public:
	EntityManager(ComponentManager* componentMgr);

	const std::set<Entity>* getEntities() const;
	void deleteEntity(Entity entity);	// TODO define delete Entity - will need to remove from compMgr and from this list

	Entity createGrassEntity(float xPos, float yPos, float rotation, float velocity, float width, float height, float energy);
	Entity createLemmingEntity(float xPos, float yPos, float rotation, float velocity, float width, float height, float energy, float saturated, float radius, float fov);
	Entity createFoxEntity(float xPos, float yPos, float rotation, float velocity, float width, float height, float energy, float saturated, float radius, float fov);

	Entity generateTestSprite(float xPos, float yPos, float rotation, float velocity);

};

