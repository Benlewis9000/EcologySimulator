#pragma once

#include <execution>

#include <glm/gtx/rotate_vector.hpp>

#include "EntityManager.h"
#include "ComponentManager.h"
#include "Simulation.h"

bool moveEntity(PhysicalComponent* entityPhys, LivingComponent* entityLiv, unsigned int wWidth, unsigned int wHeight);