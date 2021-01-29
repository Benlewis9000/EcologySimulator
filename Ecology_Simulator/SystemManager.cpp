#include "SystemManager.h"

void runSystems(Simulation* sim) {

	// Access simulations members
	EntityManager* const entityMgr = sim->getEntityManager();
	ComponentManager* const componentMgr = sim->getComponentManager();
	TextureManager* textureMgr = sim->getTextureManager();
	Shader* const shader = sim->getShader();
	const glm::mat4 projection = sim->getProjection();

	// Prepare OpenGL
	glClearColor(111.0f / 255.0f, 156 / 255.0f, 79 / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// Enable shader found
	shader->enable();
	// Send projection matrix to shader program
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	for (Entity entity : *entityMgr->getEntities()) {

		PhysicalComponent* entityPhys = componentMgr->getComponent<PhysicalComponent>(entity);
		VertexComponent* entityVert = componentMgr->getComponent<VertexComponent>(entity);
		SpriteComponent* entitySprite = componentMgr->getComponent<SpriteComponent>(entity);
		LivingComponent* entityLiv = componentMgr->getComponent<LivingComponent>(entity);
		TargetComponent* entityTarg = componentMgr->getComponent<TargetComponent>(entity);

		for (Entity target : *entityMgr->getEntities()) {

			// Make sure both entities are unqiue
			if (entity != target) {

				PhysicalComponent* targetPhys = componentMgr->getComponent<PhysicalComponent>(target);
				LivingComponent* targetLiv = componentMgr->getComponent<LivingComponent>(target);

				//updateTarget(entityPhys, entityLiv, entityTarg, targetPhys, targetLiv);
				// Do targetted systems
				//checkCollision(entityPhys, targetPhys);

			}

		}

		moveEntity(entityPhys, entityLiv, sim->getWidth(), sim->getHeight());
		renderEntity(entityPhys, entityVert, entitySprite, shader, textureMgr, sim->getWindow());

	}

	// Swap buffers
	glfwSwapBuffers(sim->getWindow());

}