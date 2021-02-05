#include "MovementSystem.h"

/**
 * Update the position of all entities with the required components (PositionComponent, LivingComponent) in parallel and deduct energy used.
 * 
 * @returns true if the entity could move, false if it had no energy and is dead
 */
bool moveEntity(PhysicalComponent* entityPhys, LivingComponent* entityLiv, unsigned int wWidth, unsigned int wHeight) {

	if (entityPhys != nullptr && entityLiv != nullptr) {

		// Only apply movement if not dead (no energy)
		if (entityLiv->energy > 0) {

			// Get position
			glm::vec2 pos = entityPhys->pos;

			glm::vec2 newPos = calculateNewPos(pos, entityPhys->velocity, entityPhys->rotation);

			// Check if new pos would be outside of bounds, rotate and update pos if so
			if (newPos.x < 0 || newPos.x > wWidth) {
				entityPhys->rotation = 360 - entityPhys->rotation;
				newPos = calculateNewPos(pos, entityPhys->velocity, entityPhys->rotation);
			}
			if (newPos.y < 0 || newPos.y > wHeight) {
				entityPhys->rotation = std::fmod((180.0 - entityPhys->rotation) + 360.0, 360.0);
				newPos = calculateNewPos(pos, entityPhys->velocity, entityPhys->rotation);
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

glm::vec2 calculateNewPos(glm::vec2 pos, float velocity, float rotation) {

	// Translation vector, length of velocity
	glm::vec2 trans = glm::vec2(0.0f, -velocity);
	// Rotate to correct orientation
	trans = glm::rotate(trans, glm::radians(rotation));

	// Apply translation
	return pos + trans;

}