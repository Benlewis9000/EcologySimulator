#pragma once

#include "Simulation.h"

void updateTarget(PhysicalComponent* entityPhys, LivingComponent* entityLiv, TargetComponent* entityTarg, PhysicalComponent* targPhys, LivingComponent* targLiv);
float calculateTargetRotation(const PhysicalComponent* entityPhys, const PhysicalComponent* targetPhys);
