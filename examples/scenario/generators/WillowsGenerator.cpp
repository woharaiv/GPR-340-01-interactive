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
  float minHeight = 999;
  float maxHeight = 0;
  for (int y = 0; y < sideSize; y++) {
    for (int x = 0; x < sideSize; x++) {
      //Remap from roughly (-1.5, 1.5) to (0, 255)
      float height = ((FractalBrownianMotion((float)x, (float)y, octaves) + 1.5f) / 3.0f) * 255.0f;
      if (height<minHeight) minHeight = height;
      if (height>maxHeight) maxHeight = height;
      uint8_t pixelColor = (uint8_t)height;
      //colors.emplace_back(Color32(height, height, height));
      if(height < 128) //Ocean
        colors.emplace_back(Color32(0, 0, pixelColor + 32));
      else if (height < 130) //Shore
        colors.emplace_back(Color32(pixelColor + 16, pixelColor + 16, 0));
      else if (height < 160) //Land
        colors.emplace_back(Color32(0, pixelColor + 32, 0));
      else //Mountain
        colors.emplace_back(Color32(pixelColor/2, pixelColor/2, pixelColor/2));

    }
  }
  std::cout << "Minimum Height: " << minHeight << std::endl;
  std::cout << "Maximum Height: " << maxHeight << std::endl;
  return colors;
}
std::string WillowsGenerator::GetName() { return "Willow's Generator"; }

float WillowsGenerator::FractalBrownianMotion(float x, float y, int octaves) {
  float result = 0;
  float amplitude = 1;
  float frequency = 0.005f;
  for(int oct = 0; oct < octaves; oct++) {
    float octaveOutput = PerlinNoise(x*frequency, y*frequency) * amplitude;
    result += octaveOutput;

    amplitude *= 0.5;
    frequency *= 2;
  }
  return result;
}

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



