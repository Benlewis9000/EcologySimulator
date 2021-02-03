#include "main.h"

/**
 * Main method for the Ecology Simulation. Creates a simulation and executes it until closed.
 */
int main() {

    // Create simulation with path to config
    std::unique_ptr<Simulation> sim = std::make_unique<Simulation>("config.json");

    // Generate entities defined in config
    sim.get()->generateEntities();

    // Main loop
    while (!glfwWindowShouldClose(sim.get()->getWindow())) {

        // Run systems
        runSystems(sim.get());

        // Poll events (e.g. window close)
        glfwPollEvents();
    }

}