#pragma once

#include <execution>

#include <glm/gtx/rotate_vector.hpp>

#include "../Simulation/Simulation.h"

bool moveEntity(PhysicalComponent* entityPhys, LivingComponent* entityLiv, unsigned int wWidth, unsigned int wHeight);

glm::vec2 calculateNewPos(glm::vec2 pos, float velocity, float rotation);