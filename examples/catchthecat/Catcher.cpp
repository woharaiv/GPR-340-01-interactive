#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  generatePath(world);
  if(bestPath.size() > 0) {
    std::cout << "Best path (catcher turn):" << std::endl;
    for(Point2D point : bestPath) {
      std::cout << " (" << point.x << ", " << point.y << ")" << std::endl;
    }

    std::cout << "Placing block at (" << bestPath.front().x << ", " << bestPath.front().y << ")" << std::endl;
    return bestPath.front();
  }

  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}
