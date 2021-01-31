#pragma once

#include "Simulation.h"
#include "Entity.h"
#include "Component.h"

void renderEntity(PhysicalComponent* entityPhys, VertexComponent* entityVert, SpriteComponent* entitySprite, Shader* const shader, TextureManager* textureManager, GLFWwindow* window);