#include "BreedingSystem.h"

/**
 * Attempt to breed two entities based on their components.
 * 
 * @return Entity ID, or 0 if breeding failed
 */
Entity breedEntities(PhysicalComponent* entityPhys, LivingComponent* entityLiv, BehaviourComponent* entityBhv, SpriteComponent* entitySprite, PhysicalComponent* targetPhys, LivingComponent* targetLiv, BehaviourComponent* targetBhv, EntityManager* entityMgr) {

	// Ensure required components are present
	if (entityPhys != nullptr && entityLiv != nullptr && entityBhv != nullptr && targetPhys != nullptr && targetLiv != nullptr && targetBhv != nullptr) {

		// Ensure entity and target want to breed (saturated and same species)
		if (entityLiv->energy >= entityBhv->saturated && targetLiv->energy >= targetBhv->saturated && entityLiv->species == targetLiv->species) {

			// Check target is colliding with entity)
			if (checkCollision(targetPhys, entityPhys)) {

				// Calculate child energy-
				float energy = 0;
				energy = energy + entityLiv->energy * 0.25;
				energy = energy + targetLiv->energy * 0.25;
				// Deduct parents energy
				entityLiv->energy = entityLiv->energy * 0.75;
				targetLiv->energy = targetLiv->energy * 0.75;

				ComponentManager* const componentMgr = entityMgr->getComponentManager();

				// Create child
				Entity child = entityMgr->createEntity();
				unsigned int VBO, VAO, size;
				generateQuad(VBO, VAO, size);
				// TODO make pos midpoint of two entities, and rotation average? or perpendicular out?
				componentMgr->setComponent(child, std::make_unique<PhysicalComponent>(glm::vec2(entityPhys->pos.x + ((targetPhys->pos.x - entityPhys->pos.x)/2.0f), entityPhys->pos.y + ((targetPhys->pos.y - entityPhys->pos.y) / 2.0f)), std::fmod(entityPhys->rotation + 90, 360.0f), entityPhys->velocity, entityPhys->width, entityPhys->height));
				componentMgr->setComponent(child, std::make_unique<VertexComponent>(VBO, VAO, size));
				componentMgr->setComponent(child, std::make_unique<LivingComponent>(entityLiv->species, energy));
				componentMgr->setComponent(child, std::make_unique<BehaviourComponent>(entityBhv->saturated, entityBhv->radius, entityBhv->fov));
				componentMgr->setComponent(child, std::make_unique<SpriteComponent>(entitySprite->texture));
				
				return child;

			}

		}

	}

	return 0;
}

void testBreeding(Simulation* sim) {

	Entity lemmingA = sim->getEntityManager()->createLemmingEntity(205.0f, 200.0f, 90.0f, 0.0f, 25.0f, 50.0f, 50.0f, 40.0f, 250.0f, 170.0f);
	Entity lemmingB = sim->getEntityManager()->createLemmingEntity(225.0f, 200.0f, 270.0f, 0.0f, 25.0f, 50.0f, 50.0f, 40.0f, 250.0f, 170.0f);
	Entity lemmingC = sim->getEntityManager()->createLemmingEntity(245.0f, 200.0f, 270.0f, 0.0f, 25.0f, 50.0f, 50.0f, 40.0f, 250.0f, 170.0f);
	Entity lemmingD = sim->getEntityManager()->createLemmingEntity(225.0f, 200.0f, 270.0f, 0.0f, 25.0f, 50.0f, 50.0f, 100.0f, 250.0f, 170.0f);
	Entity foxA = sim->getEntityManager()->createFoxEntity(275.0f, 200.0f, 270.0f, 0.0f, 75.0f, 150.0f, 50.0f, 40.0f, 400.0f, 170.0f);

	std::cout << "Test breedEntities():" << std::endl;
	std::cout << "objective (entityA, entityB) expected: result" << std::endl;
	std::cout << "succesful (lemmingA, lemmingB) != 0: " <<
		breedEntities(
			sim->getComponentManager()->getComponent<PhysicalComponent>(lemmingA),
			sim->getComponentManager()->getComponent<LivingComponent>(lemmingA),
			sim->getComponentManager()->getComponent<BehaviourComponent>(lemmingA),
			sim->getComponentManager()->getComponent<SpriteComponent>(lemmingA),
			sim->getComponentManager()->getComponent<PhysicalComponent>(lemmingB),
			sim->getComponentManager()->getComponent<LivingComponent>(lemmingB),
			sim->getComponentManager()->getComponent<BehaviourComponent>(lemmingB),
			sim->getEntityManager()
		) << std::endl;
	std::cout << "no collision (lemmingA, lemmingC) == 0: " <<
		breedEntities(
			sim->getComponentManager()->getComponent<PhysicalComponent>(lemmingA),
			sim->getComponentManager()->getComponent<LivingComponent>(lemmingA),
			sim->getComponentManager()->getComponent<BehaviourComponent>(lemmingA),
			sim->getComponentManager()->getComponent<SpriteComponent>(lemmingA),
			sim->getComponentManager()->getComponent<PhysicalComponent>(lemmingC),
			sim->getComponentManager()->getComponent<LivingComponent>(lemmingC),
			sim->getComponentManager()->getComponent<BehaviourComponent>(lemmingC),
			sim->getEntityManager()
		) << std::endl;
	std::cout << "not saturated (lemmingA, lemmingD) == 0: " <<
		breedEntities(
			sim->getComponentManager()->getComponent<PhysicalComponent>(lemmingA),
			sim->getComponentManager()->getComponent<LivingComponent>(lemmingA),
			sim->getComponentManager()->getComponent<BehaviourComponent>(lemmingA),
			sim->getComponentManager()->getComponent<SpriteComponent>(lemmingA),
			sim->getComponentManager()->getComponent<PhysicalComponent>(lemmingD),
			sim->getComponentManager()->getComponent<LivingComponent>(lemmingD),
			sim->getComponentManager()->getComponent<BehaviourComponent>(lemmingD),
			sim->getEntityManager()
		) << std::endl;
	std::cout << "wrong species (lemmingA, FoxA) == 0: " <<
		breedEntities(
			sim->getComponentManager()->getComponent<PhysicalComponent>(lemmingA),
			sim->getComponentManager()->getComponent<LivingComponent>(lemmingA),
			sim->getComponentManager()->getComponent<BehaviourComponent>(lemmingA),
			sim->getComponentManager()->getComponent<SpriteComponent>(lemmingA),
			sim->getComponentManager()->getComponent<PhysicalComponent>(foxA),
			sim->getComponentManager()->getComponent<LivingComponent>(foxA),
			sim->getComponentManager()->getComponent<BehaviourComponent>(foxA),
			sim->getEntityManager()
		) << std::endl;

}