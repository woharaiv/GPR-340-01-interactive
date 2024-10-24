#include "RandomGenerator.h"
#include "../FastNoiseLite.h"

#include <iostream>
// do not use this one to your assignment. this is my sample generator
std::vector<Color32> RandomScenarioGenerator::Generate(int sideSize, float displacement) {
  std::vector<Color32> colors;
  //   create your own function for noise generation
  FastNoiseLite base;
  base.SetFractalOctaves(3);
  base.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
  base.SetFractalType(FastNoiseLite::FractalType_FBm);
  FastNoiseLite cellular;
  cellular.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
  cellular.SetFractalOctaves(3);
  for (int l = 0; l < sideSize; l++) {
    for (int c = 0; c < sideSize; c++) {
      // island generation
      float posY = (float)((l - sideSize / 2)) / ((float)sideSize / 2);
      float posX = (float)((c - sideSize / 2)) / ((float)sideSize / 2);

      float islandInfluence = (2 - (abs(posX) + abs(posY))) / 2;
      islandInfluence *= 255;

      float c1 = ((base.GetNoise((float)c, (float)l, displacement * 50) + 1) / 2) * 255;
      //      float c2 = ((cellular.GetNoise((float)c,(float)l, displacement*50) +1)/2) *255;

      auto avg = (c1 + islandInfluence) / 2;
      Color32 pixelColor = Color::Black;
      if (avg < 50)
        pixelColor += (Color::DarkBlue + avg);
      else if (avg < 100)
        pixelColor += (Color::Yellow + (avg - 50));
      else if (avg < 150)
        pixelColor += (Color::DarkRed + (avg - 100));
      else if (avg < 200)
        pixelColor += (Color::Brown + (avg - 150));
      else
        pixelColor += (Color::LightPink + (avg - 200));
      colors.emplace_back(pixelColor);
    }
  }
  std::cout << colors.size() << std::endl;
  return colors;
}
std::string RandomScenarioGenerator::GetName() { return "EXAMPLE"; }
