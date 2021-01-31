#include "FeedingSystem.h"

/**
 * Given an entity, attempt to eat a target entity.
 * 
 * @param entityLiv living component of eating entity
 * @param entityPhys physical component of eating entity
 * @param entityTarg target component of eating entity
 */
bool eatEntity(LivingComponent* entityLiv, PhysicalComponent* entityPhys, BehaviourComponent* entityBvr, LivingComponent* targetLiv, std::default_random_engine e) {

	// Ensure required components are present
	if (entityLiv != nullptr && entityPhys != nullptr && entityBvr != nullptr && targetLiv != nullptr) {
		
		// If entity is hungry (not saturated) and target is one lower in food chain
		if (entityLiv->energy < entityBvr->saturated && entityLiv->species == targetLiv->species + 1) {

			// Transfer energy from target to entity
			entityLiv->energy = entityLiv->energy + targetLiv->energy;
			targetLiv->energy = 0.0f;

			return true;

		}

	}

	return false;

}