#include <cmath>
#include <limits>
#define _USE_MATH_DEFINES
#include "AstarStrategy.h"
#include "HighSpeedCar.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"

HighSpeedCar::HighSpeedCar(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
  std::string hcar_type=obj["type"];
  type = hcar_type;

  available = true;
}

HighSpeedCar::~HighSpeedCar() {
  // Delete dynamically allocated variables
}

void HighSpeedCar::Update(double dt, std::vector<IEntity*> scheduler) {
  if (toTargetPosStrategy) {
    toTargetPosStrategy->Move(this, dt);
  } else {
    int random_integer_x;
    int random_integer_y;
    int random_integer_z;
    random_integer_x = rand() % 2900 - 1400;
    random_integer_y = rand() % 50 + 300;
    random_integer_z = rand() % 1600 - 800;
    this->SetDestination(
        Vector3(random_integer_x, random_integer_y, random_integer_z));
    toTargetPosStrategy =
        new AstarStrategy(this->GetPosition(), this->GetDestination(), graph);
    toTargetPosStrategy->Move(this, dt);
  }
  if (toTargetPosStrategy->IsCompleted()) {
    delete toTargetPosStrategy;
    toTargetPosStrategy = NULL;
  }
}
