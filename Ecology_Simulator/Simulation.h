#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>

#include "ComponentManager.h"
#include "EntityManager.h"
#include "Shader.h"

// Todo: enforce singleton pattern for Simulation (make constructor private and add factory that checks a var)
class Simulation {
	// Member variables
	unsigned int width;
	unsigned int height;
	GLFWwindow* window;
	glm::mat4 projection;
	// Smart pointers - no calls to new/delete, thus no destructor
	std::unique_ptr<ComponentManager> componentMgr;
	std::unique_ptr<EntityManager> entityMgr;
	std::unique_ptr<TextureManager> textureMgr;
	std::unique_ptr<Shader> shader;

	void init();
public:
	Simulation(int width = 1280, int height = 720);
	inline GLFWwindow* getWindow();
	inline const glm::mat4 getProjection();
	inline EntityManager* getEntityManager();
	inline ComponentManager* getComponentManager();
	inline TextureManager* getTextureManager();
	inline Shader* getShader();

};

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