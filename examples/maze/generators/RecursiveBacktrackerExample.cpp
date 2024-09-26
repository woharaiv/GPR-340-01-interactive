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
      }
      //Mark the top cell as visited;
      w->SetNodeColor(p, Color::DarkRed);
      visited[p.y][p.x] = true;
      //List visitable neighbors;
      getVisitables(w, p);

      /*for (auto p2 : visitables) {
        //Remove the wall between the cell and the neighbor
        if((p2.y > 0 && p2.y > p.y) || (p2.y < 0 && p2.y < p.y)) {
          w->SetNorth(p,false);
          printf("\np2.y (%d) is farther north than p.y (%d)\n", p2.y, p.y);
        }
        if((p2.x > 0 && p2.x > p.x) || (p2.x < 0 && p2.x < p.x)) {
          w->SetEast(p,false);
          printf("\np2.x (%d) is farther east than p.x (%d)\n", p2.x, p.x);
        }
        if((p2.y > 0 && p2.y < p.y) || (p2.y < 0 && p2.y > p.y)) {
          w->SetSouth(p,false);
          printf("\np2.y (%d) is farther south than p.y (%d)\n", p2.y, p.y);
        }
        if((p2.x > 0 && p2.x < p.x) || (p2.x < 0 && p2.x > p.x)) {
          w->SetWest(p,false);
          printf("\np2.x (%d) is farther west than p.x (%d)\n", p2.x, p.x);
        }
      }*/
      switch(visitables.size()) {
        //If there are no visitables, backtrack
        case 0:
          return false;
        //If there's only one direction, add that one to the stack, otherwise choose a direction at random
        case 1:
          stack.push_back(visitables.back());
          break;
        default:
          stack.push_back(visitables.at(w->Random() % visitables.size()));
          break;
      }
      printf("\nVisiting (%d, %d) next.", stack.back().x, stack.back().y);
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
  printf("\np is (%d, %d)", p.x, p.y);
  //Up
  printf("\nAbove point is (%d, %d). ", p.x, p.y + (p.y >= 0 ? 1 : -1));
  if(!visited[p.y + (p.y >= 0 ? 1 : -1)][p.x] && p.y > w->GetSize()/-2) {
    visitables.push_back({p.x, p.y-1});
    w->SetNorth(p,false);
    printf("Adding above point (%d, %d) to visitables", p.x, p.y + (p.y >= 0 ? 1 : -1));
  }
  //Right
  printf("\nRight point is (%d, %d). ", p.x + (p.x >= 0 ? 1 : -1), p.y);
  if(!visited[p.y][p.x + (p.x >= 0 ? 1 : -1)] && p.x < w->GetSize()/2) {
    visitables.push_back({p.x + 1, p.y});
    w->SetEast(p,false);
    printf("Adding right point (%d, %d) to visitables", p.x + (p.x >= 0 ? 1 : -1), p.y);
  }
  //Down
  printf("\nBelow point is (%d, %d). ", p.x, p.y + (p.y >= 0 ? -1 : 1));
  if(!visited[p.y + (p.y >= 0 ? -1 : 1)][p.x] && p.y < w->GetSize()/2) {
    printf("\n%d < %d", p.y, w->GetSize()/2);
    visitables.push_back({p.x, p.y + 1});
    w->SetSouth(p,false);
    printf("Adding below point (%d, %d) to visitables", p.x, p.y + (p.y >= 0 ? -1 : 1));
  }
  //Left
  printf("\nLeft point is (%d, %d). ", p.x + (p.x >= 0 ? -1 : 1), p.y);
  if(!visited[p.y][p.x + (p.x >= 0 ? -1 : 1)] && p.y > w->GetSize()/-2) {
    visitables.push_back({p.x - 1, p.y});
    w->SetWest(p,false);
    printf("Adding left point (%d, %d) to visitables", p.x + (p.x >= 0 ? -1 : 1), p.y);
  }
  return visitables;
}
