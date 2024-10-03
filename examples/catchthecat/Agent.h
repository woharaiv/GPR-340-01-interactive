#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  struct PointWithCost {
    Point2D point;
    int cost = 0;
    bool operator<(const PointWithCost& rhs) const {
      //Returns the opposite direction because the default order of the priority queue is the opposite of the order we want to
      return cost > rhs.cost;
    }
  };


  std::vector<Point2D> generatePath(World* w);

  std::vector<Point2D> bestPath;
};

#endif  // AGENT_H
