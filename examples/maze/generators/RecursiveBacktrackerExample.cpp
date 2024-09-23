#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  //If stack is empty, start at top left
  //While the stack is not empty:
    if(!stack.empty()) {
      Point2D p = stack.back();
      if(visited[p.y][p.x]) {
        w->SetNodeColor(p, Color::Black);
        stack.pop_back();
        return false;
      }
      //Mark the top cell as visited;
      w->SetNodeColor(p, Color::DarkRed);
      visited[p.y][p.x] = true;
      //List visitable neighbors;
      getVisitables(w, p);
      switch(visitables.size()) {
        //If there are no visitables, backtrack
        case 0:
          return false;
        //If the stack has visitable neighbors, choose one of them to add to the stack
        //If there's only one direction, choose that one, otherwise choose a direction at random
        case 1:
          stack.push_back(visitables.back());
          break;
        default:
          stack.push_back(visitables.at(w->Random() % visitables.size()));
          break;
      }
      //Remove the wall between the cell and the neighbor
      Point2D p2 = stack.back();
      if(p2.y < p.y)
        w->SetNorth(p,false);
      if(p2.x > p.x)
        w->SetEast(p,false);
      if(p2.y > p.y)
        w->SetSouth(p,false);
      if(p2.x < p.x)
        w->SetWest(p,false);
    }
  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  visitables.clear();
  stack.push_back({0,0});
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  visitables.clear();
  //Up
  if(!visited[p.y-1][p.x])
    visitables.push_back({p.y-1, p.x});
  //Right
  if(!visited[p.y][p.x+1])
    visitables.push_back({p.y, p.x+1});
  //Down
  if(!visited[p.y+1][p.x])
    visitables.push_back({p.y+1, p.x});
  //Left
  if(!visited[p.y][p.x-1])
    visitables.push_back({p.y, p.x-1});
  return visitables;
}
