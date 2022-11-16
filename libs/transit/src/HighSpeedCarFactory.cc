#include "HighSpeedCarFactory.h"

IEntity* HighSpeedCarFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("highspeedcar") == 0) {
    std::cout << "HighSpeedCar Created" << std::endl;
    return new HighSpeedCar(entity);
  }
  return nullptr;
}
