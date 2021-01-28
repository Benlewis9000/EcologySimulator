#pragma once

#include "Simulation.h"

void updateEntityTargets(Simulation* sim);
float calculateTargetRotation(const TargetComponent* targComp, const PositionComponent* posComp, const PositionComponent* targetPosComp);
