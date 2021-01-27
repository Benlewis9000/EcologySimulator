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
 * Get the width of the window.
 *
 * @return window width
 */
inline unsigned int Simulation::getWidth() {

	return this->width;

}

/**
 * Get the height of the window.
 *
 * @return window height
 */
inline unsigned int Simulation::getHeight() {

	return this->height;

}

/**
 * Get a pointer to the contexts window.
 *
 * @return GLFWindow* pointer to window
 */
inline GLFWwindow* Simulation::getWindow() {

	return this->window;

}

/**
 * Get the simulations projection matrix (map pixels to NDC).
 *
 * @return glm::mat4 the projection matrix
 */
inline const glm::mat4 Simulation::getProjection() {

	return this->projection;

}

/**
 * Get a pointer to the entity manager.
 *
 * @return EntityManager* pointer to the entity manager
 */
inline EntityManager* Simulation::getEntityManager() {

	return this->entityMgr.get();

}

/**
 * Get a pointer to the component manager.
 *
 * @return ComponentManager* ponter to component manager
 */
inline ComponentManager* Simulation::getComponentManager() {

	return this->componentMgr.get();

}

/**
 * Get a pointer to the texture manager.
 *
 * @return TextureManager* pointer to texture manager
 */
inline TextureManager* Simulation::getTextureManager() {

	return this->textureMgr.get();

}

/**
 * Get a pointer to the shader.
 *
 * @return Shader* pointer to the shader
 */
inline Shader* Simulation::getShader() {

	return this->shader.get();

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