#include "Simulation.h"

/**
 * Construct a Simulation.
 * 
 * @param width of window in pixels
 * @param height of window in pixels
 */
Simulation::Simulation(int width, int height) : width(width), height(height) {

	Simulation::init();

	this->projection = glm::ortho(0.0f, (float)this->width, (float)this->height, 0.0f);
	this->componentMgr = std::make_unique<ComponentManager>();
	this->entityMgr = std::make_unique<EntityManager>(this->componentMgr.get());
	this->textureMgr = std::make_unique<TextureManager>();
	this->shader = std::make_unique<Shader>("vertex.glsl", "fragment.glsl");

}

/**
 * Initialise OpenGL context, dependencies and window, or exit application.
 */
void Simulation::init() {

	// Initialise GLFW 3.3 and OpenGL core profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Prevent resize
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);

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