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
    int accumulatedDist = 0;
    int heuristicDist = 0;
    bool operator<(const PointWithCost& rhs) const {
      //Returns the opposite direction because the default order of the priority queue puts the highest value first, but we want the lowest value first
      return accumulatedDist + heuristicDist > rhs.accumulatedDist + rhs.heuristicDist;
    }
  };


  std::vector<Point2D> generatePath(World* w);

  std::vector<Point2D> bestPath;
};

#endif  // AGENT_H
