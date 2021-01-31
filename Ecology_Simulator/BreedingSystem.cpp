#include "BreedingSystem.h"

/**
 * Attempt to breed two entities based on their components.
 * 
 * @return Entity ID, or 0 if breeding failed
 */
Entity breedEntities(PhysicalComponent* entityPhys, LivingComponent* entityLiv, BehaviourComponent* entityBhv, SpriteComponent* entitySprite, PhysicalComponent* targetPhys, LivingComponent* targetLiv, BehaviourComponent* targetBhv, EntityManager* entityMgr, std::default_random_engine& rand) {

	ZoneScoped

	// Ensure required components are present
	if (entityPhys != nullptr && entityLiv != nullptr && entityBhv != nullptr && targetPhys != nullptr && targetLiv != nullptr && targetBhv != nullptr) {

		// Ensure entity and target want to breed (saturated and same species)
		if (entityLiv->energy >= entityBhv->saturated && targetLiv->energy >= targetBhv->saturated && entityLiv->species == targetLiv->species) {

				// Calculate child energy
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
				componentMgr->setComponent(child, std::make_unique<PhysicalComponent>(glm::vec2(entityPhys->pos.x + ((targetPhys->pos.x - entityPhys->pos.x)/2.0f), entityPhys->pos.y + ((targetPhys->pos.y - entityPhys->pos.y) / 2.0f)), std::fmod(entityPhys->rotation + 90, 360.0f), entityPhys->velocity, entityPhys->width, entityPhys->height));
				componentMgr->setComponent(child, std::make_unique<VertexComponent>(VBO, VAO, size));
				componentMgr->setComponent(child, std::make_unique<LivingComponent>(entityLiv->species, energy));
				componentMgr->setComponent(child, std::make_unique<BehaviourComponent>(entityBhv->saturated, entityBhv->range, entityBhv->fov));
				componentMgr->setComponent(child, std::make_unique<SpriteComponent>(entitySprite->texture));
				
				// Set new random directions
				entityPhys->rotation = std::fmod(rand(), 360.0f);
				targetPhys->rotation = std::fmod(rand(), 360.0f);

				return child;

		}

	}

	return 0;
}

void testBreeding(Simulation* sim) {

	Entity lemmingA = sim->getEntityManager()->createBehaviouralEntity(205.0f, 200.0f, 90.0f, 0.0f, 25.0f, 50.0f, Texture::LEMMING, LivingComponent::LEMMING, 50.0f, 40.0f, 250.0f, 170.0f);
	Entity lemmingB = sim->getEntityManager()->createBehaviouralEntity(225.0f, 200.0f, 270.0f, 0.0f, 25.0f, 50.0f, Texture::LEMMING, LivingComponent::LEMMING, 50.0f, 40.0f, 250.0f, 170.0f);
	Entity lemmingC = sim->getEntityManager()->createBehaviouralEntity(245.0f, 200.0f, 270.0f, 0.0f, 25.0f, 50.0f, Texture::LEMMING, LivingComponent::LEMMING, 50.0f, 40.0f, 250.0f, 170.0f);
	Entity lemmingD = sim->getEntityManager()->createBehaviouralEntity(225.0f, 200.0f, 270.0f, 0.0f, 25.0f, 50.0f, Texture::LEMMING, LivingComponent::LEMMING, 50.0f, 100.0f, 250.0f, 170.0f);
	Entity foxA = sim->getEntityManager()->createBehaviouralEntity(275.0f, 200.0f, 270.0f, 0.0f, 75.0f, 150.0f, Texture::FOX, LivingComponent::FOX, 50.0f, 40.0f, 400.0f, 170.0f);

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
			sim->getEntityManager(),
			sim->getRand()
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
			sim->getEntityManager(),
			sim->getRand()
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
			sim->getEntityManager(),
			sim->getRand()
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
			sim->getEntityManager(),
			sim->getRand()
		) << std::endl;

}