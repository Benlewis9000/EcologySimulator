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
	
	/**
 * Assign a component of type V to an Entity (overrides existing component if one already exists).
 *
 * @tparam V the type of the Components derived class
 * @param entity to assign component to
 * @param component to assign to entity
 */
	template <typename V>
	inline void setComponent(const Entity entity, std::unique_ptr<V> component) {

		components[typeid(V)][entity] = std::move(component);

	}

	/**
	 * Remove a component of type V from an entity (if the entity exists with that component).
	 *
	 * @tparam V the type of the Components derived class
	 * @param entity to remove component from
	 */
	template <typename V>
	inline void removeComponent(const Entity entity) {

		// Check Component type exists in manager
		auto itType = components.find(typeid(V));
		if (itType != components.end()) {

			// Check entity has a type of given component
			auto itEntity = components[typeid(V)].find(entity);
			if (itEntity != components[typeid(V)].end()) {

				components[typeid(V)].erase(itEntity);

			}

		}

	}

	/**
	 * Check whether an Entity has a Component of type stated V.
	 *
	 * @tparam V the type of the Components derived class to check for
	 * @param entity to check has component
	 */
	template<typename V>
	inline bool hasComponent(const Entity entity) {

		// Check Component type exists in manager
		auto itType = components.find(typeid(V));
		if (itType != components.end()) {

			// Return true if entity has that type of component
			auto itEntity = components[typeid(V)].find(entity);
			if (itEntity != components[typeid(V)].end()) return true;

		}

		return false;
	}

	/**
	 * Get a pointer of type V to the component specified for the given Entity.
	 *
	 * @tparam V the type of the Components derived class to get
	 * @param entity to get component of
	 */
	template <typename V>
	inline auto getComponent(const Entity entity) {

		V* component = nullptr;

		// Check Component type exists in manager
		auto itType = components.find(typeid(V));
		if (itType != components.end()) {

			// Check the entity has a component of stated type
			auto itEntity = components[typeid(V)].find(entity);
			if (itEntity != components[typeid(V)].end()) {

				// Get raw pointer
				Component* ptrCom = components[typeid(V)][entity].get();

				// Cast to original type
				component = static_cast<V*>(ptrCom);

			}

		}

		return component;
	}
};

void testSetComponent();