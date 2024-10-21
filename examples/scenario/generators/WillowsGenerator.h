//
// Created by willow.ohara on 10/21/2024.
//

#ifndef WILLOWSGENERATOR_H
#define WILLOWSGENERATOR_H

#include "../GeneratorBase.h"

class WillowsGenerator : public ScenarioGeneratorBase {
public:
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;
};

#endif //WILLOWSGENERATOR_H
