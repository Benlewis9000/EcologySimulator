#include "MovementSystem.h"

/**
 * Update the position of all entities with the required components (PositionComponent, LivingComponent) in parallel and deduct energy used.
 * 
 * @param sim a pointer to the Simulator possessing the entities and components to move
 * @returns true if the entity could move, false if it had no energy and is dead
 */
bool moveEntity(PhysicalComponent* entityPhys, LivingComponent* entityLiv, unsigned int wWidth, unsigned int wHeight) {

	// TODO execute in parallel still? How?

	if (entityPhys != nullptr && entityLiv != nullptr) {

		// Only apply movement if not dead (no energy)
		if (entityLiv->energy > 0) {

			// Translation vector, length of velocity
			glm::vec2 trans = glm::vec2(0.0f, -entityPhys->velocity);
			// Rotate to correct orientation
			trans = glm::rotate(trans, glm::radians(entityPhys->rotation));

			// Get current pos
			glm::vec2 newPos = entityPhys->pos;
			// Apply translation
			newPos = newPos + trans;

			// TODO should be abstracted outside of movement system: what if an entity needs to be able to leave?
			// ^ Give its own system (and maybe a comp has a new var (physics?))
			// Make sure entity stays within window
			// |<- OR ->|
			if (newPos.x < 0 || newPos.x > wWidth) {
				entityPhys->rotation = 360 - entityPhys->rotation;
			}
			// -^- OR -v-
			if (newPos.y < 0 || newPos.y > wHeight) {
				entityPhys->rotation = 180 - entityPhys->rotation;
			}

			// Update components position vector
			entityPhys->pos = newPos;

			// Deplete energy (proportionate to velocity)
			entityLiv->energy = entityLiv->energy - entityPhys->velocity / 500.0f;

			return true;

		}

	}

	return false;
}