#include "SpawningSystem.h"

/**
 * Spawn grass entities randomly where the spawn rate defined in the config is the probability of a succesful spawn.
 */
void spawnGrass(nlohmann::json config, EntityManager* entityMgr, std::random_device& rd, std::default_random_engine& iRand, int windowWidth, int windowHeight) {

	using namespace nlohmann;

	float spawnrate = 0.0;

	try {
	
		spawnrate = config.at("grassSpawnrate");
	
	}
	catch (json::out_of_range e) {

		std::cerr << "Error: could not load \"grassSpawnrate\" from configuration." << std::endl
			<< "Ignoring grass spawning..." << std::endl;

	}
	
	// Generate random between 0 and 1
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> fRand(0.0, 1.0);

	if (fRand(gen) < spawnrate) {

		// TODO basically a copy of sims grass spawner - abstract elsewhere?
		try {

			// TODO iRand is not random coz passed by value, not ref
			json grass = config.at("entities").at("grass");
			entityMgr->registerEntity(
				entityMgr->createLivingEntity(
					std::fmod(iRand(), windowWidth),
					std::fmod(iRand(), windowHeight),
					std::fmod(iRand(), 360.0f),
					0.0f,
					40.0f, 40.0f,
					Texture::GRASS,
					LivingComponent::Species::GRASS,
					grass.at("energy")
				));
		
		}
		catch (json::out_of_range e) {

			std::cerr << "Error: could not load data for grass in the configuration." << std::endl
				<< "This entity will be ignored..." << std::endl;

		}

	}

}