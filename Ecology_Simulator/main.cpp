#include "main.h"

int main() {

    std::random_device rd;
    std::default_random_engine e(rd());

    std::unique_ptr<Simulation> sim = std::make_unique<Simulation>("config.json");

    sim.get()->generateEntities();

    // Main loop
    while (!glfwWindowShouldClose(sim.get()->getWindow())) {

        runSystems(sim.get());

        glfwPollEvents();
    }

}