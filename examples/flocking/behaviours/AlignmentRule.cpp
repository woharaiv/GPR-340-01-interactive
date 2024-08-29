#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  if(neighborhood.size() <= 0)
    return Vector2f::zero();

  Vector2f averageVelocity = Vector2f::zero();

  for (int i = 0; i < neighborhood.size(); i++)
  {
    averageVelocity += neighborhood[i]->getVelocity();
  }

  averageVelocity /= neighborhood.size();
  return Vector2f::normalized(averageVelocity) * weight;
}