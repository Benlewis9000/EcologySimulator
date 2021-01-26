#pragma once

#include "RenderSystem.h"

/**
 * Render all entities with the required components (PositionComponent, VertexComponent, SpriteComponent) in a given Simulation.
 * 
 * @param sim a pointer to the Simulator possessing the entities and components to render
 */
void renderEntities(Simulation* sim) {

	// Set background colour
	glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Access simulations members
	const EntityManager* const entityMgr = sim->getEntityManager();
	ComponentManager* const componentMgr = sim->getComponentManager();
	Shader* const shader = sim->getShader();
	const glm::mat4 projection = sim->getProjection();

	// Enable shader found
	shader->enable();

	// Send projection matrix to shader program
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// Iterate all entities
	for (Entity entity : *entityMgr->getEntities()) {

		// Acquire required components if possible
		PositionComponent* const pos = componentMgr->getComponent<PositionComponent>(entity);
		VertexComponent* const vert = componentMgr->getComponent<VertexComponent>(entity);
		SpriteComponent* const sprite = componentMgr->getComponent<SpriteComponent>(entity);

		// Make sure entity has required components
		if (pos != nullptr && vert != nullptr && sprite != nullptr) {

			// Bind entities buffers
			glBindBuffer(GL_ARRAY_BUFFER, vert->VBO);
			glBindVertexArray(vert->VAO);

			// Set transformation matrix model
			glm::mat4 model(1.0f);

			// Move to position
			model = glm::translate(model, glm::vec3(pos->pos, 0.0f));
			
			// Rotate 
			model = glm::rotate(model, glm::radians(pos->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
			//model = glm::rotate(model, glm::radians((float)glfwGetTime()*64 + pos->rotation), glm::vec3(0.0f, 0.0f, 1.0f));

			// Scale to size
			model = glm::scale(model, glm::vec3(sprite->width, sprite->height, 1.0f));

			// Send model matrix to shader
			glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
			
			// Set texture
			glUniform1i(glGetUniformLocation(shader->getID(), "image"), 0);
			glActiveTexture(GL_TEXTURE0);
			// Bind retrieved texture ID from manager
			glBindTexture(GL_TEXTURE_2D, sim->getTextureManager()->getTexture(sprite->texture));

			// Draw entity
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glDrawElements(GL_TRIANGLES, vert->numVertices, GL_UNSIGNED_INT, 0);

		}

	}

	// Swap buffers
	glfwSwapBuffers(sim->getWindow());

}