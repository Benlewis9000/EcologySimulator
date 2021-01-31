#pragma once

#include "Simulation.h"

void updateTarget(PhysicalComponent* entityPhys, LivingComponent* entityLiv, BehaviourComponent* entityBvr, PhysicalComponent* targPhys, LivingComponent* targLiv, int& closestTarget);
float calculateTargetRotation(const PhysicalComponent* entityPhys, const PhysicalComponent* targetPhys);
