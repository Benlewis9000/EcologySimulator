#include "EntityManager.h"

/**
 * Create a new Entity and register it with the calling manager.
 * 
 * @return Entity created
 */
Entity EntityManager::newEntity() {

	// Generate Entity (random ID)
	std::default_random_engine e((unsigned int)this->rd());
	Entity entity = e();
	// Register entity
	this->entities.get()->insert(entity);
	return entity;

}

/**
 * Generate an entity suitable only to test the render system.
 * 
 * @param xPos position along x axis
 * @param yPos position along y axis
 * @param rotation in degrees
 * @return Entity generated
 */
Entity EntityManager::generateTestSprite(float xPos, float yPos, float rotation, float velocity) {

	// Create new entity
	const Entity entity = this->newEntity();
	
	// Declare vertices
	float vertices[] = {
		// Coordinate	// Texture coordinate
		-0.5f, 0.5f,	0.0f, 1.0f,
		0.5f, 0.5f,		1.0f, 1.0f,
		0.5f, -0.5f,	1.0f, 0.0f,
		-0.5f, -0.5f,	0.0f, 0.0f
	};
	// Declare indicies to draw triangulated quad
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	// Generate arrays/buffers
	unsigned int VBO, EBO, VAO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	// Populate arrays/buffers
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

	// Set and enable vertex attribute pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Unbind buffers/arrays when done
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Build and attach relevant components to entity
	componentMgr->setComponent<PositionComponent>(entity, std::make_unique<PositionComponent>(glm::vec2(xPos, yPos), rotation, velocity));
	componentMgr->setComponent<VertexComponent>(entity, std::make_unique<VertexComponent>(sizeof(indices) / sizeof(float), VBO, VAO));
	componentMgr->setComponent<SpriteComponent>(entity, std::make_unique<SpriteComponent>(Texture::FOX, 100.0f, 200.0f));

	return entity;

}