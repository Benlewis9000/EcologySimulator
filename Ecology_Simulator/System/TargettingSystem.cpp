#include "TargettingSystem.h"

/**
 * Update an entities rotation to look at a target, depending on whether in feeding or breeding state, and closer than current target.
 */
void updateTarget(PhysicalComponent* entityPhys, LivingComponent* entityLiv, BehaviourComponent* entityBvr, PhysicalComponent* targPhys, LivingComponent* targLiv, int& closestTarget) {

	if (entityPhys != nullptr && entityLiv != nullptr && entityBvr != nullptr && targPhys != nullptr && targLiv != nullptr) {

		// Check distance between entity and target is shortest so far
		float dist = glm::distance(entityPhys->pos, targPhys->pos);
		if (dist < closestTarget) {

			// Update shortest distance
			closestTarget = dist;

			// If unsaturated, and target is one lower on food chain, pursue food
			// OR if saturated, and target is equal species, pursue mate
			if ( (entityLiv->energy < entityBvr->saturated && targLiv->species == entityLiv->species - 1)
				|| (entityLiv->energy > entityBvr->saturated && targLiv->species == entityLiv->species) ){

				// Calculate rotation to point at target, and assign if within FOV
				float r = calculateTargetRotation(entityPhys, targPhys);
				if (std::abs(entityPhys->rotation - r) < entityBvr->fov / 2.0f) entityPhys->rotation = r;

			}

		}

	}

}

/**
 * Calculate the rotation value of an entity to point at a different target entity, if target is within FOV and nearest available.
 * 
 * @param entityPhys physical component of the entity
 * @param targetPhys physical component of the target entity
 */
float calculateTargetRotation(const PhysicalComponent* entityPhys, const PhysicalComponent* targetPhys) {

	// Calculate new rotation r to point at target
	float r;

	// Check entities are on same Y axis (thus preventing division by 0)
	if (entityPhys->pos.y == targetPhys->pos.y) {
		r = 90;
	}
	// Use arctan to calculate initial angle
	else {
		r = glm::degrees(glm::atan(std::abs(entityPhys->pos.x - targetPhys->pos.x),
			std::abs(entityPhys->pos.y - targetPhys->pos.y)));
	}

	// Adjust r to be relative to a rotation from 0 degrees
	if (entityPhys->pos.x < targetPhys->pos.x && entityPhys->pos.y < targetPhys->pos.y)
		r = 180 - r;
	else if (entityPhys->pos.x > targetPhys->pos.x && entityPhys->pos.y < targetPhys->pos.y)
		r = 180 + r;
	else if (entityPhys->pos.x > targetPhys->pos.x && entityPhys->pos.y > targetPhys->pos.y)
		r = 360 - r;

	return r;
}