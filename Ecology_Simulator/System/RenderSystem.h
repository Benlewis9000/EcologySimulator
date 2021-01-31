#pragma once

#include "../Simulation/Simulation.h"

void renderEntity(PhysicalComponent* entityPhys, VertexComponent* entityVert, SpriteComponent* entitySprite, Shader* const shader, TextureManager* textureManager, GLFWwindow* window);