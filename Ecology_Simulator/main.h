#pragma once

#include <iostream>
#include <map>
#include <typeindex>
#include <memory>
#include <thread>

#include <Tracy.hpp>
#include "libs/json.hpp"

#include "main.h"
#include "Component/ComponentManager.h"
#include "Simulation/Simulation.h"
#include "System/MovementSystem.h"
#include "System/RenderSystem.h"
#include "System/TargettingSystem.h"
#include "System/CollisionSystem.h"
#include "System/SystemManager.h"