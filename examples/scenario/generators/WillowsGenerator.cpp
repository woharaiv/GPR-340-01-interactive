//
// Created by willow.ohara on 10/21/2024.
//

#include "WillowsGenerator.h"

#include <iostream>
#include <ostream>

std::vector<Color32> WillowsGenerator::Generate(int sideSize, float displacement) {
  std::vector<Color32> colors;
  static unsigned int rngState = 56;
  for (int y = 0; y < sideSize; y++) {
    for (int x = 0; x < sideSize; x++) {
      //simple xorshift for faster random generation than adding a random color
      rngState ^= rngState << 13;
      rngState ^= rngState >> 17;
      rngState ^= rngState << 5;
      if(rngState == 0) rngState++; //xorshift gets stuck in a loop at 0
      colors.emplace_back(Color::Gold + rngState % 32);
    }
  }
  return colors;
}
std::string WillowsGenerator::GetName() { return "Willow's Generator"; }
