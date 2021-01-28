#include "TargettingSystem.h"

void updateEntityTargets(Simulation* sim) {

	// Get simulations managers
	const EntityManager* const entityMgr = sim->getEntityManager();
	ComponentManager* const componentMgr = sim->getComponentManager();

	// Iterate entities
	for (Entity entity : *entityMgr->getEntities()) {

		// Get required components
		PositionComponent* posComp = componentMgr->getComponent<PositionComponent>(entity);
		LivingComponent* livComp = componentMgr->getComponent<LivingComponent>(entity);
		TargetComponent* targComp = componentMgr->getComponent<TargetComponent>(entity);

		// TODO n^2 loops are very ineffecient
		// Could fix by having one n^2 loop that runs all collisions/targeting etc. with two given entities
		// H: would that need to access more components, which is expensive? I don't think so, just get all components
		// then try to run each system that the right components are available for
		// If so, would need target distance to be added to component. Targetting done by rotation, so doesn't
		// actually need to know who or what its target is, just how close it is for comparisons.
		// Would also stop an entity having the same component called by two diff systems.

		if (posComp != nullptr && livComp != nullptr && targComp != nullptr) {

			float shortest = INT_MAX;

			// Iterate other entities as potential target
			for (Entity target : *entityMgr->getEntities()) {

				// Ensure target is not itself
				if (target != entity) {

					// Get required target components
					PositionComponent* targetPosComp = componentMgr->getComponent<PositionComponent>(target);
					LivingComponent* targetLivComp = componentMgr->getComponent<LivingComponent>(target);

					if (targetPosComp != nullptr && targetLivComp != nullptr) {

						// Check distance between entity and target is shortest so far and within radius
						float dist = glm::distance(posComp->pos, targetPosComp->pos);
						if (dist < shortest && dist <= targComp->radius) {

							// Update shortest distance
							shortest = dist;

							// If unsaturated, and target is one lower on food chain, pursue food
							if (livComp->energy < targComp->saturation && targetLivComp->species == livComp->species - 1) {

								// Calculate rotation to point at target, and asign if within FOV
								float r = calculateTargetRotation(targComp, posComp, targetPosComp);
								if (std::abs(posComp->rotation - r) < targComp->fov / 2.0f) posComp->rotation = r;

							}
							// Else saturated, and target is equal species, pursue mate
							else if (livComp->energy > targComp->saturation && targetLivComp->species == livComp->species) {

								// Calculate rotation to point at target, and asign if within FOV
								float r = calculateTargetRotation(targComp, posComp, targetPosComp);
								if (std::abs(posComp->rotation - r) < targComp->fov / 2.0f) posComp->rotation = r;

							}

						}

					}

				}

			}

		}

	}

}

/**
 * Calculate the rotation value of an entity to point at a different target entity, if target is within FOV and nearest available.
 * 
 * @param targComp target component of the entity
 * @param posComp position component of the entity
 * @param targetPosComp position component of the target entity
 */
float calculateTargetRotation(const TargetComponent* targComp, const PositionComponent* posComp, const PositionComponent* targetPosComp) {

	// Calculate new rotation r to point at target
	float r;

	// Check entities are on same Y axis (thus preventing division by 0)
	if (posComp->pos.y == targetPosComp->pos.y) {
		r = 90;
	}
	// Use arctan to calculate initial angle
	else {
		r = glm::degrees(glm::atan(std::abs(posComp->pos.x - targetPosComp->pos.x),
			std::abs(posComp->pos.y - targetPosComp->pos.y)));
	}

	// Adjust r to be relative to a rotation from 0 degrees
	if (posComp->pos.x < targetPosComp->pos.x && posComp->pos.y < targetPosComp->pos.y)
		r = 180 - r;
	else if (posComp->pos.x > targetPosComp->pos.x && posComp->pos.y < targetPosComp->pos.y)
		r = 180 + r;
	else if (posComp->pos.x > targetPosComp->pos.x && posComp->pos.y > targetPosComp->pos.y)
		r = 360 - r;

	return r;
}