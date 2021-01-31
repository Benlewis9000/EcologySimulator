#pragma once

#include <execution>

#include <glm/gtx/rotate_vector.hpp>

#include "../Simulation/Simulation.h"

bool moveEntity(PhysicalComponent* entityPhys, LivingComponent* entityLiv, unsigned int wWidth, unsigned int wHeight);