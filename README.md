# Ecology Simulator
Ecology Simulator is a graphical simulation of a finite set of species competing and interacting for a mate or food. Startup parameters are fully configurable via the config.json. Balanced configs can accurately portray booms and collapses in populations as the size of their respective prey or predator's also changes.

The simulation is implemented in C++ and shader based OpenGL 3.3. The model is based on an entity-component-system architecture, allowing for great flexibility when designing, adding or modifying entities. This is assisted by the highly dynamic component manager. Independent to entities and components, the entity manager does not know what has been defined until they are created at runtime. Whilst this advantageous to rapid and agile development, the typecasts performed do act as a barrier to performance. Regardless,  the ECS engine is highly effective as a proof of concept.

This was a graded piece, awarded a First at 78%.
