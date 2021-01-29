#pragma once

#include <glm/gtx/rotate_vector.hpp>
#include < glm/gtx/intersect.hpp>

#include "Simulation.h"

/**
 * Check if the head of one entity intersects the polygon of another entity.
 * 
 * @param entityPhys physical component of entity to detect head collision with
 * @param targetPhys physical component of entity to detect polygon collision with
 * @returns true if collision
 */
bool checkCollision(const PhysicalComponent* entityPhys, const PhysicalComponent* targetPhys);

/**
 * Check if a point is within a polygon by raycasting from outside the polygon to the point.
 * 
 * @param rayBegin beginning of ray
 * @param rayEnd end of ray
 * @param polygon vector of ordered vertices making up a polygon
 * @returns true if point is outside of the polygon
 */
bool raycastPointWithPolygon(const glm::vec2 rayBegin, const glm::vec2 rayEnd, const std::vector<glm::vec2> polygon);

/**
 * Check if a segment intersects a segment.
 * 
 * @param s1v1 start point of segment one
 * @param s1v2 end point of segment one
 * @param s2v1 start point of segment two
 * @param s2v2 end point of segment two
 * @returns true if segments intersect
 */
bool segmentIntersectsSegment(const glm::vec2 s1v1, const glm::vec2 s1v2, const glm::vec2 s2v1, const glm::vec2 s2v2);

/**
 * Check if a segment intersects the trajectory of another.
 * 
 * @param s1v1 start point of segment to be treated as line
 * @param s1v2 end point of segment to be treated as line
 * @param s2v1 start point of segment to test for intersection
 * @param s2v2 end point of segment to test for intersection
 * @returns true if segment intersects infinite line
 */
bool segmentIntersectsLine(const glm::vec2 s1v1, const glm::vec2 s1v2, const glm::vec2 s2v1, const glm::vec2 s2v2);

void testRaycast();

void testEntityCollision(Simulation* sim);