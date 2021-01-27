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
	unsigned int getWidth();
	unsigned int getHeight();
	GLFWwindow* getWindow();
	const glm::mat4 getProjection();
	EntityManager* getEntityManager();
	ComponentManager* getComponentManager();
	TextureManager* getTextureManager();
	Shader* getShader();

};