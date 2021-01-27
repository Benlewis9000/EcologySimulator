#include "ComponentManager.h"

/**
 * Assign a component of type V to an Entity (overrides existing component if one already exists).
 *
 * @tparam V the type of the Components derived class
 * @param entity to assign component to
 * @param component to assign to entity
 */
template <typename V>
void ComponentManager::setComponent(const Entity entity, std::unique_ptr<V> component) {

	components[typeid(V)][entity] = std::move(component);

}

/**
 * Remove a component of type V from an entity (if the entity exists with that component).
 *
 * @tparam V the type of the Components derived class
 * @param entity to remove component from
 */
template <typename V>
void ComponentManager::removeComponent(const Entity entity) {

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
bool ComponentManager::hasComponent(const Entity entity) {

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
auto ComponentManager::getComponent(const Entity entity) {

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

/**
 * Test harness for the ComponentManager.
 */
void testSetComponent() {

	Entity entity1 = 1;
	std::unique_ptr<A> a1 = std::make_unique<A>();
	std::unique_ptr<B> b1 = std::make_unique<B>();
	std::unique_ptr<C> c1 = std::make_unique<C>('c');

	Entity entity42 = 42;
	std::unique_ptr<C> c42 = std::make_unique<C>();

	ComponentManager compMan;

	compMan.setComponent<A>(entity1, std::move(a1));
	compMan.setComponent<B>(entity1, std::move(b1));
	compMan.setComponent<C>(entity1, std::move(c1));


	std::cout << "Test setComponent(), hasComponent(): Expect 0, 1, 0" << std::endl;
	std::cout << compMan.hasComponent<C>(entity42) << std::endl;

	compMan.setComponent<C>(entity42, std::move(c42));
	std::cout << compMan.hasComponent<C>(entity42) << std::endl;

	compMan.removeComponent<C>(entity42);
	std::cout << compMan.hasComponent<C>(entity42) << std::endl;


	std::cout << "Test getComponent(): Expect \"Hello, c\"" << std::endl;
	C* c = compMan.getComponent<C>(entity1);
	c->hello();


	std::cout << "Finished ComponentManager tests." << std::endl;

}