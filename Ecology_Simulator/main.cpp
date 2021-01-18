#include <iostream>
#include <map>
#include <typeindex>
#include <memory>

#include "main.h"
#include "ComponentManager.h"
#include "Simulation.h"
#include "RenderSystem.h"

int main() {

    //testSetComponent();

    std::unique_ptr<Simulation> sim = std::make_unique<Simulation>(1280, 720);

    sim.get()->getEntityManager()->generateTestSprite(100.0f, 300.0f, 25.0f);
    sim.get()->getEntityManager()->generateTestSprite(400.0f, 200.0f, 250.0f);
    sim.get()->getEntityManager()->generateTestSprite(1000.0f, 600.0f, 290.0f);
    sim.get()->getEntityManager()->generateTestSprite(700.0f, 400.0f, 90.0f);
    sim.get()->getEntityManager()->generateTestSprite(900.0f, 370.0f, 45.0f);

    // Main render loop
    // Todo: MOVE TO SYSTEM
    while (!glfwWindowShouldClose(sim.get()->getWindow())) {

        renderEntities(sim.get());

        glfwPollEvents();
    }

}