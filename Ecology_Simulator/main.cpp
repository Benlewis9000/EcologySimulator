#include <iostream>
#include <map>
#include <typeindex>
#include <memory>

#include "main.h"
#include "ComponentManager.h"
#include "Simulation.h"
#include "MovementSystem.h"
#include "RenderSystem.h"

int main() {

    //testSetComponent();

    std::unique_ptr<Simulation> sim = std::make_unique<Simulation>(1280, 720);

    // Test sprites
    for (int i = 0; i < 500; i++) sim.get()->getEntityManager()->generateTestSprite(100.0f, 300.0f, 60.0f, 4.0f);
    sim.get()->getEntityManager()->generateTestSprite(100.0f, 300.0f, 60.0f, 4.0f);
    sim.get()->getEntityManager()->generateTestSprite(400.0f, 200.0f, 250.0f, 8.0f);
    sim.get()->getEntityManager()->generateTestSprite(800.0f, 200.0f, 250.0f, 2.0f);
    sim.get()->getEntityManager()->generateTestSprite(1000.0f, 600.0f, 290.0f, 4.0f);
    sim.get()->getEntityManager()->generateTestSprite(700.0f, 400.0f, 80.0f, 4.0f);
    sim.get()->getEntityManager()->generateTestSprite(900.0f, 370.0f, 45.0f, 4.0f);

    // Main loop
    while (!glfwWindowShouldClose(sim.get()->getWindow())) {

        moveEntities(sim.get());
        renderEntities(sim.get());

        glfwPollEvents();
    }

}