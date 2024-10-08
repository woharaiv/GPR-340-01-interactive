#ifndef WORLD_H
#define WORLD_H

#include "../behaviours/FlockingRule.h"
#include "Boid.h"
#include "scene/GameObject.h"

class Particle;

// todo: make world a game engine scene manager
class World : public GameObject {
private:
  /// MEMBERS
  /// Configuration
  // Boids
  int nbBoids = 300;

  bool hasConstantSpeed = false;
  float desiredSpeed = 120.0f;

  bool hasMaxAcceleration = false;
  float maxAcceleration = 10.0f;

  float detectionRadius = 35;

  Boid* userBoid = nullptr;
  float userSpeed = 1.0f;

  // Display
  bool showRadius = false;
  bool showRules = false;
  bool showAcceleration = false;

  // rules
  std::vector<std::unique_ptr<FlockingRule>> boidsRules;
  // todo: make this a vector
  std::vector<float> defaultWeights;  // array of default rules weight

  std::vector<float> defaultBonusWeights;  // defaultWeights, but for the user boid bonus weights

  /// METHODS
  void initializeRules();

  // Boids

  void applyFlockingRulesToAllBoids();
  void setNumberOfBoids(int number);
  void randomizeBoidPositionAndVelocity(Boid* boid);
  void warpParticleIfOutOfBounds(Particle* particle);

  Boid* createBoid();
  Boid* createUserBoid();
  void destroyUserBoid();

public:
  // cached list to manipulate objects
  std::vector<Boid*> boids;

  bool userBoidActive = false;

  /// METHODS
  explicit World(Engine* pEngine);

  // Getters
  std::vector<Boid*>* getAllBoids();

  int getNbBoids() const;

  /// Setters

  // ImGui
  void drawGeneralUI();
  void drawRulesUI();

  // Update
  void Update(float deltaTime) override;

  void showConfigurationWindow(float deltaTime);
  void drawPerformanceUI(float deltaTime);

  void OnGui(ImGuiContext* context) override;
  void Start() override;
};

#endif
