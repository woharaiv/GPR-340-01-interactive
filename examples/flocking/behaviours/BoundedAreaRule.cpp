#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Return a force proportional to the proximity of the boids with the bounds, and opposed to it
  Vector2f force = Vector2f::zero();  // zero

  // todo: add here your code code here do make the boid follow the bounded box rule
  // hint: use this->world->engine->window->size() and desiredDistance
  Vector2f walls(this->world->engine->window->size().x, this->world->engine->window->size().y);
  //Assuming top left is 0,0
  Vector2f distToTopLeft = boid->getPosition();
  Vector2f distToBottomRight = walls - boid->getPosition();
  Vector2f centerPoint = walls/2;

  //Calculate for each wall
  //North wall
  if(distToTopLeft.y < desiredDistance)
  {
    force.y += desiredDistance / distToTopLeft.y;
  }
  //East wall
  if(distToBottomRight.x < desiredDistance)
  {
    force.x -= desiredDistance / distToBottomRight.x;
  }
  //South wall
  if(distToBottomRight.y < desiredDistance)
  {
    force.y -= desiredDistance / distToBottomRight.y;
  }
  //West wall
  if(distToTopLeft.x < desiredDistance)
  {
    force.x += desiredDistance / distToTopLeft.x;
  }

  //Weight was originally re-multiplied in FlockingRule::computeWeightedForce()
  //Since now it's possible to have influence when weight is 0, that step was moved here.
  force *= weight * weight;

  return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}