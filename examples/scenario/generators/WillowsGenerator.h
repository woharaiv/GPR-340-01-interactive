//
// Created by willow.ohara on 10/21/2024.
//

#ifndef WILLOWSGENERATOR_H
#define WILLOWSGENERATOR_H

#include "../GeneratorBase.h"
#include "math/Vector2.h"

class WillowsGenerator : public ScenarioGeneratorBase {
public:

  int resolution = 255;

  unsigned int rngState = 42;
  unsigned int Random();

  int randomArray[256];
  void InitRandomArray(){
    for(int i = 0; i < 256; i++) {randomArray[i] = Random() % 4;}
  }

  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;

  float PerlinNoise(float x, float y);
  float PerlinNoise(Vector2d point){return PerlinNoise(point.x, point.y);}

  Vector2d GetVec(int v);
  float Lerp(float t, float a1, float a2) {
    return a1 + t*(a2-a1);
  }
  float FadeCurve(float t) {
    return ((6*t - 15)*t + 10)*t*t*t; //Equivalent to 6t^5 - 15t^4 + 10t^3 but with 9 less multiplications
  }
  float Dot(Vector2d v1, Vector2d v2) {
    return (v1.x*v2.x + v1.y*v2.y);
  }
};

#endif //WILLOWSGENERATOR_H
