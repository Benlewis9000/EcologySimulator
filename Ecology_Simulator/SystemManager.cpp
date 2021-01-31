#include "SystemManager.h"

void runSystems(Simulation* sim) {

	// Access simulations members
	EntityManager* const entityMgr = sim->getEntityManager();
	ComponentManager* const componentMgr = sim->getComponentManager();
	TextureManager* textureMgr = sim->getTextureManager();
	Shader* const shader = sim->getShader();
	const glm::mat4 projection = sim->getProjection();

	// Prepare OpenGL
	glClearColor(111.0f / 255.0f, 156 / 255.0f, 79 / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// Enable shader found
	shader->enable();
	// Send projection matrix to shader program
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	std::set<Entity> dead;
	std::set<Entity> children;

	spawnGrass(sim->getConfig(), entityMgr,sim->getRd(), sim->getRand(), sim->getWidth(), sim->getHeight());

	for (Entity entity : *entityMgr->getEntities()) {

		// Make sure entity is not dead
		if (dead.find(entity) == dead.end()) {

			PhysicalComponent* entityPhys = componentMgr->getComponent<PhysicalComponent>(entity);
			VertexComponent* entityVert = componentMgr->getComponent<VertexComponent>(entity);
			SpriteComponent* entitySprite = componentMgr->getComponent<SpriteComponent>(entity);
			LivingComponent* entityLiv = componentMgr->getComponent<LivingComponent>(entity);
			BehaviourComponent* entityBhv = componentMgr->getComponent<BehaviourComponent>(entity);

			int closestTarget = INT_MAX;

			for (Entity target : *entityMgr->getEntities()) {

				// Make sure both entities are unqiue and target is not dead
				if (entity != target && dead.find(target) == dead.end()) {

					// Acquire targets physical component to check range
					PhysicalComponent* targetPhys = componentMgr->getComponent<PhysicalComponent>(target);

					if (entityBhv != nullptr && targetPhys != nullptr) {

						// Ensure target is within range, otherwise ignore
						float dist = glm::distance(entityPhys->pos, targetPhys->pos);
						if (dist <= entityBhv->range) {

							// Acquire target components
							LivingComponent* targetLiv = componentMgr->getComponent<LivingComponent>(target);
							BehaviourComponent* targetBhv = componentMgr->getComponent<BehaviourComponent>(target);

							// Update rotation to aim at nearest target
							updateTarget(entityPhys, entityLiv, entityBhv, targetPhys, targetLiv, closestTarget);

							// If entities collide
							if (checkCollision(entityPhys, targetPhys)) {

								// Breeding system
								Entity child = breedEntities(entityPhys, entityLiv, entityBhv, entitySprite, targetPhys, targetLiv, targetBhv, entityMgr, sim->getRand());
								if (child != 0) children.insert(child);

								// Feeding system
								if (eatEntity(entityLiv, entityPhys, entityBhv, targetLiv, sim->getRand())) dead.insert(target);

							}

						}

					}

				}

			}

			// Move entity (update position)
			if (!moveEntity(entityPhys, entityLiv, sim->getWidth(), sim->getHeight())) dead.insert(entity);
			// Render entity
			renderEntity(entityPhys, entityVert, entitySprite, shader, textureMgr, sim->getWindow());

		}

	}

	// Remove dead entities
	for (Entity entity : dead) entityMgr->deleteEntity(entity);

	// Add children entities
	for (Entity entity : children) entityMgr->registerEntity(entity);

	// Swap buffers
	glfwSwapBuffers(sim->getWindow());

}