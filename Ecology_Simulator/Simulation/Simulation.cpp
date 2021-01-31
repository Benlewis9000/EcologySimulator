#include "Simulation.h"

/**
 * Construct a Simulation.
 * 
 * @param configPath path to a JSON configuration file
 */
Simulation::Simulation(std::string configPath) : rand(std::random_device{}()) {

	using namespace nlohmann;

	// Try to load config
	std::ifstream file(configPath);
	if (file.is_open()) {

		file >> config;

	}
	else {

		// Exit if failure
		std::cerr << "Error: could not find JSON configuration \"" << configPath << "\"." << std::endl;
		exit(-1);

	}

	try {

		// Get window size from config..
		this->width = config.at("windowWidth");
		this->height = config.at("windowHeight");

	}
	catch (json::out_of_range e) {

		// ..or set defaults (720p)
		std::cerr << "Error: could not find \"windowWidth\" and \"windowHeight\" in the configuration." << std::endl;
		std::cerr << "Setting window size to 1280p * 720p." << std::endl;
		this->width = 1280;
		this->height = 720;

	}

	// Initialise OpenGL context
	Simulation::initOpenGL();

	// Initialise member variables
	this->projection = glm::ortho(0.0f, (float)this->width, (float)this->height, 0.0f);
	this->componentMgr = std::make_unique<ComponentManager>();
	this->entityMgr = std::make_unique<EntityManager>(this->componentMgr.get());
	this->textureMgr = std::make_unique<TextureManager>();
	this->shader = std::make_unique<Shader>("shaders/vertex.glsl", "shaders/fragment.glsl");

}

/**
 * Get the JSON configuration for the simulation.
 * 
 * @return the configuration 
 */
const nlohmann::json Simulation::getConfig() {

	return this->config;

}

/**
 * Get the width of the window.
 *
 * @return window width
 */
unsigned int Simulation::getWidth() {

	return this->width;

}

/**
 * Get the height of the window.
 *
 * @return window height
 */
unsigned int Simulation::getHeight() {

	return this->height;

}

/**
 * Get a pointer to the contexts window.
 *
 * @return GLFWindow* pointer to window
 */
GLFWwindow* Simulation::getWindow() {

	return this->window;

}

/**
 * Get the simulations projection matrix (map pixels to NDC).
 *
 * @return glm::mat4 the projection matrix
 */
const glm::mat4 Simulation::getProjection() {

	return this->projection;

}

std::random_device& Simulation::getRd() {

	return this->rd;

}

/**
 * Get the simulations random engine.
 * 
 * @return random engine
 */
std::default_random_engine& Simulation::getRand() {

	return this->rand;

}

/**
 * Get a pointer to the entity manager.
 *
 * @return EntityManager* pointer to the entity manager
 */
EntityManager* Simulation::getEntityManager() {

	return this->entityMgr.get();

}

/**
 * Get a pointer to the component manager.
 *
 * @return ComponentManager* ponter to component manager
 */
ComponentManager* Simulation::getComponentManager() {

	return this->componentMgr.get();

}

/**
 * Get a pointer to the texture manager.
 *
 * @return TextureManager* pointer to texture manager
 */
TextureManager* Simulation::getTextureManager() {

	return this->textureMgr.get();

}

/**
 * Get a pointer to the shader.
 *
 * @return Shader* pointer to the shader
 */
Shader* Simulation::getShader() {

	return this->shader.get();

}

/**
 * Initialise OpenGL context, dependencies and window, or exit application.
 */
void Simulation::initOpenGL() {

	// Initialise GLFW 3.3 and OpenGL core profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Prevent resize
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 16);

	// Create a window and bind to context (exit on failure)
	this->window = (glfwCreateWindow(this->width, this->height, "Ecology Simulation", NULL, NULL));
	if (this->window == NULL) {

		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		std::terminate();

	}
	glfwMakeContextCurrent(this->window);
	
	// Initiliase GLAD (exit on failure)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

		std::cout << "Failed to initialise GLAD!" << std::endl;
		glfwTerminate();
		std::terminate();

	}

	// Set viewport
	glViewport(0, 0, this->width, this->height);

	// Set random seed
	std::srand(glfwGetTime());

}

void Simulation::generateEntities() {

	using namespace nlohmann;

	json entities;

	// Load entity data from config
	try {
	
		entities = config.at("entities");
	
	}
	// Exit if entity data not defined
	catch (json::out_of_range e) {

		std::cerr << "Error: could not load \"entities\" from configuration." << std::endl
			<< "Exiting program..." << std::endl;
		exit(-1);

	}

	// Generate Grasss
	try {

		json grass = entities.at("grass");
		for (int i = 0; i < grass.at("quantity"); i++)
			getEntityManager()->registerEntity(
				getEntityManager()->createLivingEntity(
					std::fmod(rand(), getWidth()),
					std::fmod(rand(), getHeight()),
					std::fmod(rand(), 360.0f),
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

	// Generate Lemmings
	try {

		json lemming = entities.at("lemming");
		for (int i = 0; i < lemming.at("quantity"); i++)
			getEntityManager()->registerEntity(
				getEntityManager()->createBehaviouralEntity(
					std::fmod(rand(), getWidth()),
					std::fmod(rand(), getHeight()),
					std::fmod(rand(), 360.0f),
					lemming.at("velocity"),
					25.0f, 50.0f,
					Texture::LEMMING,
					LivingComponent::Species::LEMMING,
					lemming.at("energy"),
					lemming.at("saturated"),
					lemming.at("range"),
					lemming.at("fov")
				));

	}
	catch (json::out_of_range e) {

		std::cerr << "Error: could not load data for lemmings in the configuration." << std::endl
			<< "This entity will be ignored..." << std::endl;

	}

	try {

		// Generate Foxes
		json fox = entities.at("fox");
		for (int i = 0; i < fox.at("quantity"); i++)
			getEntityManager()->registerEntity(
				getEntityManager()->createBehaviouralEntity(
					std::fmod(rand(), getWidth()),
					std::fmod(rand(), getHeight()),
					std::fmod(rand(), 360.0f),
					fox.at("velocity"),
					75.0f, 150.0f,
					Texture::FOX,
					LivingComponent::Species::FOX,
					fox.at("energy"),
					fox.at("saturated"),
					fox.at("range"),
					fox.at("fov")
				));

	}
	catch (json::out_of_range e) {

		std::cerr << "Error: could not load data for foxes in the configuration." << std::endl
			<< "This entity will be ignored..." << std::endl;

	}

}