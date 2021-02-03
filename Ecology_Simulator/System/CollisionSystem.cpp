#include "CollisionSystem.h"

#include <Tracy.hpp>

bool checkCollision(const PhysicalComponent* entityPhys, const PhysicalComponent* targetPhys) {

	// Ensure correct components are present
	if (entityPhys != nullptr && targetPhys != nullptr) {

		// Get mouth of entity as vec2
		glm::vec2 mouth = glm::vec2(0.0f, -entityPhys->height / 2.0f);
		mouth = glm::rotate(mouth, glm::radians(entityPhys->rotation));
		mouth = mouth + entityPhys->pos;

		int intersections = 0;

		// Calculate vertices of target entity
		glm::vec2 v1(-targetPhys->width / -targetPhys->height / 2.0f);
		v1 = glm::rotate(v1, glm::radians(targetPhys->rotation));
		v1 = v1 + targetPhys->pos;

		glm::vec2 v2(targetPhys->width / 2.0f, -targetPhys->height / 2.0f);
		v2 = glm::rotate(v2, glm::radians(targetPhys->rotation));
		v2 = v2 + targetPhys->pos;

		glm::vec2 v3(targetPhys->width / 2.0f, targetPhys->height / 2.0f);
		v3 = glm::rotate(v3, glm::radians(targetPhys->rotation));
		v3 = v3 + targetPhys->pos;

		glm::vec2 v4(-targetPhys->width / 2.0f, targetPhys->height / 2.0f);
		v4 = glm::rotate(v4, glm::radians(targetPhys->rotation));
		v4 = v4 + targetPhys->pos;

		// Construct polygon
		std::vector<glm::vec2> polygon;
		polygon.push_back(v1);
		polygon.push_back(v2);
		polygon.push_back(v3);
		polygon.push_back(v4);

		// Calculate point outside of target polygon to act as second vertex of ray
		glm::vec2 rayBegin(mouth.x, mouth.y - targetPhys->pos.y - targetPhys->height);

		// Cast ray, returning true if mouth is within the polygon (thus collision)
		return raycastPointWithPolygon(rayBegin, mouth, polygon);

	}

	return false;

}

/**
 * Check if a point is within a polygon by raycasting from outside the polygon to the point.
 *
 * @returns true if point is outside of the polygon
 */
bool raycastPointWithPolygon(const glm::vec2 rayBegin, const glm::vec2 rayEnd, const std::vector<glm::vec2> polygon) {

	int intersections = 0;

	// Iterate vertices of polygon
	for (int i = 0; i < polygon.size(); i++) {

		// Index if next vertex, wrapping to beginning if needed
		int j = (i + 1) % (polygon.size());

		// If ray intersects polygin side, increment intersections
		if (segmentIntersectsSegment(rayBegin, rayEnd, polygon[i], polygon[j])) intersections++;

	}

	// If odd number of intersections, ray ends within polygon
	return (intersections % 2 == 1);
}

/**
 * Check if a segment intersects a segment.
 *
 * @returns true if segments intersect
 */
bool segmentIntersectsSegment(const glm::vec2 s1v1, const glm::vec2 s1v2, const glm::vec2 s2v1, const glm::vec2 s2v2) {

	// Return true if both segments intersect the trajectory of the other, thus intersecting themselves
	return (segmentIntersectsLine(s1v1, s1v2, s2v1, s2v2) 
		&& segmentIntersectsLine(s2v1, s2v2, s1v1, s1v2));

}

/**
 * Check if a segment intersects an infinite line.
 *
 * @returns true if segment intersects infinite line
 */
bool segmentIntersectsLine(const glm::vec2 s1v1, const glm::vec2 s1v2, const glm::vec2 s2v1, const glm::vec2 s2v2) {

	// Construct line from segment one
	float a, b, c;
	a = s1v2.y - s1v1.y;
	b = s1v1.x - s1v2.x;
	c = (s1v2.x * s1v1.y) - (s1v1.x * s1v2.y);

	// Calculate which side of the line segments two's endpoints fall on
	float d1, d2;
	d1 = (a * s2v1.x) + (b * s2v1.y) + c;
	d2 = (a * s2v2.x) + (b * s2v2.y) + c;

	// If endpoints on opposide sides, segment intersects line, return true
	return  ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0));

}

/**
 * Test harness for raycasting.
 */
void testRaycast() {

	glm::vec2 v1(6.0f, 6.0f);
	glm::vec2 v2(11.0f, 4.0f);
	glm::vec2 v3(14.0f, 8.0f);
	glm::vec2 v4(7.0f, 10.0f);
	std::vector<glm::vec2> polygon;
	polygon.push_back(v1);
	polygon.push_back(v2);
	polygon.push_back(v3);
	polygon.push_back(v4);

	glm::vec2 a(10.0f, 7.0f);
	glm::vec2 b(11.0f, 5.0f);
	glm::vec2 c(16.0f, 5.0f);
	glm::vec2 d(10.0f, 11.0f);

	glm::vec2 rayBegin(-1.0f, -1.0f);

	std::cout << "Test raycastPointWithPolygon():" << std::endl;
	std::cout << "vertex (expected): result" << std::endl;
	std::cout << "a (1): " << raycastPointWithPolygon(rayBegin, a, polygon) << std::endl;
	std::cout << "b (1): " << raycastPointWithPolygon(rayBegin, b, polygon) << std::endl;
	std::cout << "c (0): " << raycastPointWithPolygon(rayBegin, c, polygon) << std::endl;
	std::cout << "d (0): " << raycastPointWithPolygon(rayBegin, d, polygon) << std::endl;

	std::cout << "Finished tests." << std::endl;

}

/**
 * Test harness for checking entity collisions.
 */
void testEntityCollision(Simulation* sim) {

	Entity grass = sim->getEntityManager()->createLivingEntity(200.0f, 200.0f, 0.0f, 0.0f, 40.0f, 40.0f, Texture::GRASS, LivingComponent::GRASS, 10.0f);
	Entity lemmingA = sim->getEntityManager()->createBehaviouralEntity(230.0f, 200.0f, 270.0f, 0.0f, 25.0f, 50.0f, Texture::LEMMING, LivingComponent::LEMMING, 20.0f, 40.0f, 250.0f, 170.0f);
	Entity lemmingB = sim->getEntityManager()->createBehaviouralEntity(170.0f, 200.0f, 0.0f, 0.0f, 25.0f, 50.0f, Texture::LEMMING, LivingComponent::LEMMING, 40.0f, 40.0f, 250.0f, 170.0f);

	std::cout << "Test checkCollision():" << std::endl;
	std::cout << "entity (expected): result" << std::endl;
	std::cout << "LemmingA (1): " <<
		checkCollision(sim->getComponentManager()->getComponent<PhysicalComponent>(lemmingA),
			sim->getComponentManager()->getComponent<PhysicalComponent>(grass))
		<< std::endl;

	std::cout << "LemmingB (0): " <<
		checkCollision(sim->getComponentManager()->getComponent<PhysicalComponent>(lemmingB),
			sim->getComponentManager()->getComponent<PhysicalComponent>(grass))
		<< std::endl;

}