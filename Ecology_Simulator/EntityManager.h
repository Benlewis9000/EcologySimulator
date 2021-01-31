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
	std::default_random_engine rand;

public:
	EntityManager(ComponentManager* componentMgr);

	ComponentManager* const getComponentManager();
	const std::set<Entity>* getEntities() const;

	Entity createEntity();
	void registerEntity(Entity entity);
	void deleteEntity(Entity entity);

	Entity createLivingEntity(float xPos, float yPos, float rotation, float velocity, float width, float height, Texture texture, LivingComponent::Species species, float energy);
	Entity createBehaviouralEntity(float xPos, float yPos, float rotation, float velocity, float width, float height, Texture texture, LivingComponent::Species species, float energy, float saturated, float radius, float fov);

	Entity generateTestSprite(float xPos, float yPos, float rotation, float velocity);

};

// TODO abstract to Util?
void generateQuad(unsigned int& VBO, unsigned int& VAO, unsigned int& size);