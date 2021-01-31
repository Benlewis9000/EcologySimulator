#pragma once

#include "../Entity/EntityManager.h"
#include "CollisionSystem.h"

Entity breedEntities(PhysicalComponent* entityPhys, LivingComponent* entityLiv, BehaviourComponent* entityBhv, SpriteComponent* entitySprite, PhysicalComponent* targetPhys, LivingComponent* targetLiv, BehaviourComponent* targetBhv, EntityManager* entityMgr, std::default_random_engine& rand);

void testBreeding(Simulation* sim);