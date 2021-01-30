#pragma once

#include "EntityManager.h"
#include "CollisionSystem.h"

Entity breedEntities(PhysicalComponent* entityPhys, LivingComponent* entityLiv, BehaviourComponent* entityBhv, SpriteComponent* entitySprite, PhysicalComponent* targetPhys, LivingComponent* targetLiv, BehaviourComponent* targetBhv, EntityManager* entityMgr);

void testBreeding(Simulation* sim);