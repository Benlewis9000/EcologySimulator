#pragma once

#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <type_traits>
#include <memory>

#include "Component.h"
#include "Entity.h"

class ComponentManager {
	// Member variables
	// TODO Change to <Entity <CType, Component>> ? Means can iterate entities, and don't need a seperate list of entities. H: can't iterate components, have to iterate through all entities and look for component
	std::unordered_map<std::type_index, std::map<Entity, std::unique_ptr<Component>>> components;

public:
	
	template <typename V>
	void setComponent(const Entity entity, std::unique_ptr<V> component);

	template <typename V>
	void removeComponent(const Entity entity);

	template<typename V>
	bool hasComponent(const Entity entity);

	template <typename V>
	auto getComponent(const Entity entity);

};

void testSetComponent();