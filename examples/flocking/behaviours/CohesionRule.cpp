#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid)
{
  if(neighborhood.size() <= 0)
    return Vector2f::zero();
  Vector2f cohesionForce = Vector2f::zero();
  Vector2f centerOfMass = Vector2f::zero();

  for (int i = 0; i < neighborhood.size(); i++)
  {
    centerOfMass += neighborhood[i]->getPosition();
  }
  // find center of mass
  centerOfMass /= neighborhood.size();
  //The strength of the cohesion vector is inversely proportional to the radius, and then scaled by k.
  cohesionForce = (centerOfMass - boid->getPosition()) * (weight/boid->getDetectionRadius());
  return cohesionForce;
}