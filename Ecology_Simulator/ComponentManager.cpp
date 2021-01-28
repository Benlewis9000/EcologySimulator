#include "ComponentManager.h"



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