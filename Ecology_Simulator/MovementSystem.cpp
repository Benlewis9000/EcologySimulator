#include "MovementSystem.h"

void moveEntities(Simulation* sim) {

	const EntityManager* const entityMgr = sim->getEntityManager();
	ComponentManager* const componentMgr = sim->getComponentManager();

	for (Entity entity : *entityMgr->getEntities()) {

		PositionComponent* posComp = componentMgr->getComponent<PositionComponent>(entity);

		if (posComp != nullptr) {

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

		}

	}

}