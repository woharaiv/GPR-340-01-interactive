#ifndef MOBAGEN_WORLD_H
#define MOBAGEN_WORLD_H

#include "math/ColorT.h"
#include "scene/GameObject.h"
#include "MazeGeneratorBase.h"
#include "Node.h"
#include "math/Point2D.h"
#include <vector>

class World : GameObject {
private:
  int sideSize;

  std::vector<MazeGeneratorBase*> generators;
  int generatorId = 0;
  bool isSimulating = false;
  float timeBetweenAITicks = 0.0;
  float timeForNextTick = 0;
  int64_t moveDuration = 0;
  int64_t totalTime = 0;

  // ._
  // |
  // even indexes are top elements;
  // odd indexes are left elements;
  std::vector<bool> data;
  // the boxes colors
  std::vector<Color32> colors;
  // convert a point into the index of the left vertex of the node
  inline int Point2DtoIndex(const Point2D& point) {
    // todo: test. unstable interface
    auto sizeOver2 = sideSize / 2;
    return (point.y + sizeOver2) * (sideSize + 1) * 2 + (point.x + sizeOver2) * 2;
  }

public:
  ~World();
  explicit World(Engine* pEngine, int size);

  Node GetNode(const Point2D& point);
  bool GetNorth(const Point2D& point);
  bool GetEast(const Point2D& point);
  bool GetSouth(const Point2D& point);
  bool GetWest(const Point2D& point);

  void SetNode(const Point2D& point, const Node& node);
  void SetNorth(const Point2D& point, const bool& state);
  void SetEast(const Point2D& point, const bool& state);
  void SetSouth(const Point2D& point, const bool& state);
  void SetWest(const Point2D& point, const bool& state);

  void Start() override;
  void OnGui(ImGuiContext* context) override;
  void OnDraw(SDL_Renderer* renderer) override;
  void Update(float deltaTime) override;

  void Clear();

  void SetNodeColor(const Point2D& node, const Color32& color);
  Color32 GetNodeColor(const Point2D& node);

  int GetSize() const;

  int Random(){ return RNG_SEQUENCE[(++rngIndex %= 99)]; }

private:
  void step();
  const int RNG_SEQUENCE[100] = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};
  int rngIndex = -1; //Random() increments rngIndex by 1 before getting the value, so it's initialized to -1 so that the first call sets it to 0
};

#endif
