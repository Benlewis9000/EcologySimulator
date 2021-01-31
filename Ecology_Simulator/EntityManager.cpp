#include "EntityManager.h"

/**
 * Construct an EntityManager.
 *
 * @param componentMgr pointer to a ComponentManager to register an entities components with
 */
EntityManager::EntityManager(ComponentManager* componentMgr) : componentMgr(componentMgr), rand(std::random_device{}()) {

	this->entities = std::make_unique<std::set<Entity>>();

}

ComponentManager* const EntityManager::getComponentManager() {

	return this->componentMgr;

}

/**
 * Get an immutable pointer to the managers entities.
 *
 * @return std::set<Entity>* a pointer to the managers entities
 */
const std::set<Entity>* EntityManager::getEntities() const {

	return this->entities.get();

}

/**
 * Create a new Entity and register it with the calling manager.
 * 
 * @return Entity created
 */
Entity EntityManager::createEntity() {

	// Generate Entity (random ID)
	Entity entity = rand();
	return entity;

}

void EntityManager::registerEntity(Entity entity) {

	this->entities.get()->insert(entity);

}

void EntityManager::deleteEntity(Entity entity) {

	this->entities.get()->erase(entity);
	componentMgr->deleteEntity(entity);

}

Entity EntityManager::createLivingEntity(float xPos, float yPos, float rotation, float velocity, float width, float height, Texture texture, LivingComponent::Species species, float energy) {

	const Entity entity = this->createEntity();

	// Build and attach relevant components to entity
	unsigned int VBO, VAO, size;
	generateQuad(VBO, VAO, size);
	componentMgr->setComponent<VertexComponent>(entity, std::make_unique<VertexComponent>(size, VBO, VAO));
	componentMgr->setComponent<PhysicalComponent>(entity, std::make_unique<PhysicalComponent>(glm::vec2(xPos, yPos), rotation, velocity, width, height));
	componentMgr->setComponent<SpriteComponent>(entity, std::make_unique<SpriteComponent>(texture));
	componentMgr->setComponent<LivingComponent>(entity, std::make_unique<LivingComponent>(species, energy));

	return entity;

}
Entity EntityManager::createBehaviouralEntity(float xPos, float yPos, float rotation, float velocity, float width, float height, Texture texture, LivingComponent::Species species, float energy, float saturated, float radius, float fov) {

	// Create living entity
	Entity entity = createLivingEntity(xPos, yPos, rotation, velocity, width, height, texture, species, energy);
	
	// Add behavioural component
	componentMgr->setComponent<BehaviourComponent>(entity, std::make_unique<BehaviourComponent>(saturated, radius, fov));

	return entity;

}

/**
 * Generate an entity suitable only for testing.
 * 
 * @param xPos position along x axis
 * @param yPos position along y axis
 * @param rotation in degrees
 * @return Entity generated
 */
Entity EntityManager::generateTestSprite(float xPos, float yPos, float rotation, float velocity) {

	// Create new entity
	const Entity entity = this->createEntity();
	
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
	componentMgr->setComponent<PhysicalComponent>(entity, std::make_unique<PhysicalComponent>(glm::vec2(xPos, yPos), rotation, velocity, 100.0f, 200.0f));
	componentMgr->setComponent<VertexComponent>(entity, std::make_unique<VertexComponent>(sizeof(indices) / sizeof(float), VBO, VAO));
	componentMgr->setComponent<SpriteComponent>(entity, std::make_unique<SpriteComponent>(Texture::FOX));
	componentMgr->setComponent<LivingComponent>(entity, std::make_unique<LivingComponent>(LivingComponent::Species::FOX, 20000.0f));
	componentMgr->setComponent<BehaviourComponent>(entity, std::make_unique<BehaviourComponent>(0.0f, 800.0f, 170.0f));

	return entity;

}

void generateQuad(unsigned int& VBO, unsigned int& VAO, unsigned int& size) {

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
	size = sizeof(indices) / sizeof(float);

	// Generate arrays/buffers
	unsigned int EBO;
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

}