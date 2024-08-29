#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  int boidsInRadius = 0;
  for (int i = 0; i < neighborhood.size(); i++)
  {
    //Calculate the target boid's distance to this one
    Vector2f vecToBoid = boid->getPosition() - neighborhood[i]->getPosition();

    //If the distance is 0, it'll cause errors in the math later, so don't calculate this boid.
    if(vecToBoid.x == 0 && vecToBoid.y == 0)
      continue;

    float distToBoid = vecToBoid.getMagnitude();

    //only apply force if it's within the separation radius, which may be smaller than the neighborhood
    if(distToBoid < desiredMinimalDistance)
    {
      // Add the boid's position to the separation vector, scaled by how close that boid is to the target.
      separatingForce += vecToBoid.normalized()/distToBoid;
      boidsInRadius++;
    }
  }

  separatingForce = Vector2f::normalized(separatingForce) * weight;

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
