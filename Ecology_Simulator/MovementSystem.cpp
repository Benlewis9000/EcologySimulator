#include "MovementSystem.h"

/**
 * Update the position of all entities with the required components (PositionComponent, LivingComponent) in parallel and deduct energy used.
 * 
 * @param sim a pointer to the Simulator possessing the entities and components to move
 */
void moveEntities(Simulation* sim) {

	// TODO also check if entity has TargetComponent. If it does, pursue target.

	const EntityManager* const entityMgr = sim->getEntityManager();
	ComponentManager* const componentMgr = sim->getComponentManager();

	// Calculate movements in parallel
	std::for_each(std::execution::par, entityMgr->getEntities()->begin(), entityMgr->getEntities()->end(), [&sim, &entityMgr, &componentMgr](auto&& entity) {
		
		PositionComponent* posComp = componentMgr->getComponent<PositionComponent>(entity);
		LivingComponent* livingComp = componentMgr->getComponent<LivingComponent>(entity);

		if (posComp != nullptr && livingComp != nullptr) {

			// Only apply movement if not dead (no energy)
			if (livingComp->energy > 0) {

				// Translation vector, length of velocity
				glm::vec2 trans = glm::vec2(0.0f, -posComp->velocity);
				// Rotate to correct orientation
				trans = glm::rotate(trans, glm::radians(posComp->rotation));

				// Get current pos
				glm::vec2 newPos = posComp->pos;
				// Apply translation
				newPos = newPos + trans;

				// TODO should be abstracted outside of movement system: what if an entity needs to be able to leave?
				// Make sure entity stays within window
				// |<- OR ->|
				if (newPos.x < 0 || newPos.x > sim->getWidth()) {
					posComp->rotation = 360 - posComp->rotation;
				}
				// -^- OR -v-
				if (newPos.y < 0 || newPos.y > sim->getHeight()) {
					posComp->rotation = 180 - posComp->rotation;
				}

				// Update components position vector
				posComp->pos = newPos;

				// Deplete energy (proportionate to velocity)
				livingComp->energy = livingComp->energy - posComp->velocity / 500.0f;

			}

		}

	});

	/*
	for (Entity entity : *entityMgr->getEntities()) {

		PositionComponent* posComp = componentMgr->getComponent<PositionComponent>(entity);
		LivingComponent* livingComp = componentMgr->getComponent<LivingComponent>(entity);

		if (posComp != nullptr && livingComp != nullptr) {

			// Only apply movement if not dead (no energy)
			if (livingComp->energy > 0) {

				// Translation vector, length of velocity
				glm::vec2 trans = glm::vec2(0.0f, -posComp->velocity);
				// Rotate to correct orientation
				trans = glm::rotate(trans, glm::radians(posComp->rotation));

				// Get current pos
				glm::vec2 newPos = posComp->pos;
				// Apply translation
				newPos = newPos + trans;

				// Make sure entity stays within window @TODO should be abstracted outside of movement system: what if an entity needs to be able to leave?
				// |<- OR ->|
				if (newPos.x < 0 || newPos.x > sim->getWidth()) {
					posComp->rotation = 360 - posComp->rotation;
				}
				// -^- OR -v-
				if (newPos.y < 0 || newPos.y > sim->getHeight()) {
					posComp->rotation = 180 - posComp->rotation;
				}

				// Update components position vector
				posComp->pos = newPos;

				// Deplete energy (proportionate to velocity)
				livingComp->energy = livingComp->energy - posComp->velocity / 500.0f;

			}

		}
		
	}
	*/

}