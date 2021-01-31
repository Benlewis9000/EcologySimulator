#pragma once

#include "../libs/json.hpp"

#include "../Entity/EntityManager.h"

void spawnGrass(nlohmann::json config, EntityManager* entityMgr, std::random_device& rd, std::default_random_engine& iRand, int windowWidth, int windowHeight);