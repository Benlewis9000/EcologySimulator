#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "json.hpp"

#include <iostream>
#include <memory>

#include "ComponentManager.h"
#include "EntityManager.h"
#include "Shader.h"

class Simulation {
	// Member variables
	nlohmann::json config;
	unsigned int width;
	unsigned int height;
	GLFWwindow* window;
	glm::mat4 projection;
	std::random_device rd;
	std::default_random_engine rand;
	// Smart pointers - no calls to new/delete, thus no destructor
	std::unique_ptr<ComponentManager> componentMgr;
	std::unique_ptr<EntityManager> entityMgr;
	std::unique_ptr<TextureManager> textureMgr;
	std::unique_ptr<Shader> shader;

	void initOpenGL();
public:
	Simulation(std::string configPath = "config.json");
	const nlohmann::json getConfig();
	unsigned int getWidth();
	unsigned int getHeight();
	GLFWwindow* getWindow();
	const glm::mat4 getProjection();
	std::random_device& getRd();
	std::default_random_engine& getRand();
	EntityManager* getEntityManager();
	ComponentManager* getComponentManager();
	TextureManager* getTextureManager();
	Shader* getShader();

	void generateEntities();

};