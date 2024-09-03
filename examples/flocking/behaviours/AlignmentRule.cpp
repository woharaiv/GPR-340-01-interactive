#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  if(neighborhood.size() <= 0)
    return Vector2f::zero();

  Vector2f userBoidVelocity = Vector2f::zero();
  Vector2f averageVelocity = Vector2f::zero();

  for (auto boid_i : neighborhood)
  {
    averageVelocity += boid_i->getVelocity();
    if (boid_i->controledByUser)
      userBoidVelocity += boid_i->getVelocity();
  }

  userBoidVelocity /= neighborhood.size();
  averageVelocity /= neighborhood.size();
  //Weight was originally re-multiplied in FlockingRule::computeWeightedForce()
  //Since now it's possible to have influence when weight is 0, that step was moved here.
  return Vector2f::normalized(averageVelocity) * weight * weight + Vector2f::normalized(userBoidVelocity) * userBoidBonusWeight * userBoidBonusWeight;
}