//
// Created by willow.ohara on 10/21/2024.
//

#include "WillowsGenerator.h"

#include <iostream>
#include <ostream>

unsigned int WillowsGenerator::Random() {
  //std::cout << "Random fnuction" << std::endl;
  //simple xorshift for faster random generation
  rngState ^= rngState << 13;
  rngState ^= rngState >> 17;
  rngState ^= rngState << 5;
  if(rngState == 0) rngState++; //xorshift gets stuck in a loop at 0
  return rngState;
}


std::vector<Color32> WillowsGenerator::Generate(int sideSize, float displacement) {
  //std::cout << "init randomArray" << std::endl;
  InitRandomArray();
  std::vector<Color32> colors;

  for (int y = 0; y < sideSize; y++) {
    for (int x = 0; x < sideSize; x++) {
      //std::cout << "get perlin" << std::endl;
      colors.emplace_back(Color::Black + PerlinNoise((float)x/resolution, (float)y/resolution) * 255);
    }
  }
  return colors;
}
std::string WillowsGenerator::GetName() { return "Willow's Generator"; }

float WillowsGenerator::PerlinNoise(float x, float y) {
  int X = (int)x;
  int Y = (int)y;
  float xDec = x - floor(x);
  float yDec = y - floor(y);

  //std::cout << "corners to point" << std::endl;
  //Vectors from the nearest corners of the integer grid to the actual point
  Vector2d topRight = Vector2d(xDec - 1, yDec - 1);
  Vector2d topLeft = Vector2d(xDec, yDec - 1);
  Vector2d bottomRight = Vector2d(xDec - 1, yDec);
  Vector2d bottomLeft = Vector2d(xDec, yDec);

  //std::cout << "values" << std::endl;
  //randomArray is pre-generated, so these will be the same every time PerlinNoise is run.
  //valueBottomLeft for a grid cell is the same as valueTopRight for the cell down and to the right, ensuring the vectors stay the same across the grid.
  int valueTopRight = randomArray[(randomArray[(X+1)%255]+Y+1)%255];
  int valueTopLeft = randomArray[(randomArray[X%255]+Y+1)%255];
  int valueBottomRight = randomArray[(randomArray[(X+1)%255]+Y)%255];
  int valueBottomLeft = randomArray[(randomArray[X%255]+Y)%255];

  //std::cout << "dots" << std::endl;
  float dotTopRight = Dot(topRight, GetVec(valueTopRight));
  float dotTopLeft = Dot(topLeft, GetVec(valueTopLeft));
  float dotBottomRight = Dot(bottomRight, GetVec(valueBottomRight));
  float dotBottomLeft = Dot(bottomLeft, GetVec(valueBottomLeft));

  //std::cout << "fadecurve" << std::endl;
  float u = FadeCurve(xDec);
  float v = FadeCurve(yDec);
  float result = Lerp(u,
                      Lerp(v, dotBottomLeft, dotTopLeft),
                      Lerp(v, dotBottomRight, dotTopRight));
  return result;
}

Vector2d WillowsGenerator::GetVec(int v) {
  switch(v % 4) {
    case 0:
      return Vector2d(1, 1);
    case 1:
      return Vector2d(-1, 1);
    case 2:
      return Vector2d(-1, -1);
    default:
      return Vector2d(1, -1);
  }
}



