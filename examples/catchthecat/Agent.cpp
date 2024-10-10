#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<PointWithCost> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  std::vector<Point2D> allNeighbors;
  std::vector<Point2D> visitable;
  int sideOver2 = w->getWorldSideSize()/2;
  int accumulatedCost = 0;

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(PointWithCost(catPos));
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    //std::cout << "get the current from frontier" << std::endl;
    PointWithCost current = frontier.top();
    frontier.pop();
    //std::cout << "(" << current.point.x << ", " << current.point.y << ")" << std::endl;
    accumulatedCost += current.accumulatedDist;

    //std::cout << "remove the current from frontierset" << std::endl;
    frontierSet.erase(current.point);

    //std::cout << "mark current as visited" << std::endl;
    visited[current.point] = true;

    //std::cout << "getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue" << std::endl;
    allNeighbors = w->neighbors(current.point);
    visitable.clear();
    for(Point2D neighbor : allNeighbors) {
      //std::cout << "  (" << neighbor.x << ", " << neighbor.y << ")" << std::endl;
      if(visited.contains(neighbor)) {
        //std::cout << "Not visitable; it's already visited" << std::endl;
        continue;
      }
      if(w->getCat().x == neighbor.x && w->getCat().y == neighbor.y) {
        //std::cout << "Not visitable; the cat is there" << std::endl;
        continue;
      }
      if(w->getContent(neighbor) == true) {
        //std::cout << "Not visitable; blocked" << std::endl;
        continue;
      }
      if(frontierSet.contains(neighbor)) {
        //std::cout << "Not visitable; in queue" << std::endl;
        continue;
      }
      visitable.push_back(neighbor);
    }
    //std::cout << "iterate over the neighs:" << std::endl;
    for(Point2D neighbor : visitable) {
      //std::cout << "  (" << neighbor.x << ", " << neighbor.y << ")" << std::endl;
      //std::cout << "for every neighbor set the cameFrom" << std::endl;
      cameFrom.insert({neighbor, current.point});
      //std::cout << "enqueue the neighbors to frontier and frontierset" << std::endl;
      //std::cout << "cost is " << accumulatedCost + w->distToBorder(neighbor) << std::endl;
      frontier.push(PointWithCost(neighbor, w->distToBorder(neighbor) + accumulatedCost));
      frontierSet.insert(neighbor);
      if(abs(neighbor.x) == sideOver2 || abs(neighbor.y) == sideOver2) {
        //std::cout << "do this up to find a visitable border and break the loop" << std::endl;
        borderExit = neighbor;
        break;
      }
    }
    if(abs(borderExit.x) <= sideOver2)
      break;
  }

  //std::cout << "if the border is not infinity, build the path from border to the cat using the camefrom map" << std::endl;
  if(abs(borderExit.x) <= sideOver2) {
    vector<Point2D> path;
    //std::cout << "if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move" << std::endl;
    path.push_back(borderExit);
    do {
      path.push_back(cameFrom.at(path.back()));
    }while(path.back() != catPos);
    bestPath = path;
  }
  else {
    //std::cout << "if there isnt a reachable border, just return empty vector" << std::endl;
    bestPath = vector<Point2D>();
  }

  return bestPath;
}
