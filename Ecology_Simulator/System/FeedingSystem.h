#pragma once

#include "../Simulation/Simulation.h"

bool eatEntity(LivingComponent* entityLiv, PhysicalComponent* entityPhys, BehaviourComponent* entityBhv, LivingComponent* targetLiv, std::default_random_engine e);