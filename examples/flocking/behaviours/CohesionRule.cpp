#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid)
{
  if(neighborhood.size() <= 0)
    return Vector2f::zero();
  Vector2f cohesionForce = Vector2f::zero();
  Vector2f centerOfMass = Vector2f::zero();

  Vector2f userBoidPosition = Vector2f::zero();
  bool userBoidInNeighborhood = false;

  for (auto boid_i : neighborhood)
  {
    centerOfMass += boid_i->getPosition();
    if(boid_i->controledByUser)
    {
      userBoidInNeighborhood = true;
      userBoidPosition += boid_i->getPosition();
    }
  }
  // find center of mass
  centerOfMass /= neighborhood.size();
  //The strength of the cohesion vector is inversely proportional to the radius, and then scaled by k.
  //Weight was originally re-multiplied in FlockingRule::computeWeightedForce()
  //Since now it's possible to have influence when weight is 0, that step was moved here.
  cohesionForce = (centerOfMass - boid->getPosition()) * (weight * weight/boid->getDetectionRadius());

  if(userBoidInNeighborhood)
    cohesionForce += (userBoidPosition - boid->getPosition()) * (userBoidBonusWeight * userBoidBonusWeight/boid->getDetectionRadius());

  return cohesionForce;
}