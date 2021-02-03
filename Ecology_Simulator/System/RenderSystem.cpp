#pragma once

#include <Tracy.hpp>

#include "RenderSystem.h"

/**
 * Render all entities with the required components (PositionComponent, VertexComponent, SpriteComponent) in a given Simulation.
 */
void renderEntity(PhysicalComponent* entityPhys, VertexComponent* entityVert, SpriteComponent* entitySprite, Shader* const shader, TextureManager* textureManager, GLFWwindow* window) {

	// Make sure entity has required components
	if (entityPhys != nullptr && entityVert != nullptr && entitySprite != nullptr) {

		// Bind entities buffers
		glBindBuffer(GL_ARRAY_BUFFER, entityVert->VBO);
		glBindVertexArray(entityVert->VAO);

		// Set transformation matrix model
		glm::mat4 model(1.0f);

		// Move to position
		model = glm::translate(model, glm::vec3(entityPhys->pos, 0.0f));
			
		// Rotate 
		model = glm::rotate(model, glm::radians(entityPhys->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, glm::radians((float)glfwGetTime()*64 + pos->rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		// Scale to size
		model = glm::scale(model, glm::vec3(entityPhys->width, entityPhys->height, 1.0f));

		// Send model matrix to shader
		glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
			
		// Set texture
		glUniform1i(glGetUniformLocation(shader->getID(), "image"), 0);
		glActiveTexture(GL_TEXTURE0);
		// Bind retrieved texture ID from manager
		glBindTexture(GL_TEXTURE_2D, textureManager->getTexture(entitySprite->texture));

		// Draw entity
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, entityVert->numVertices, GL_UNSIGNED_INT, 0);

	}

}