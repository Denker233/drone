#ifndef HIGHSPEEDCAR_FACTORY_H_
#define HIGHSPEEDCAR_FACTORY_H_

#include <vector>

#include "HighSpeedCar.h"
#include "IEntity.h"
#include "IEntityFactory.h"

class HighSpeedCarFactory : public IEntityFactory {
 public:
  /**
   * @brief Destroy the High speed Car factory object
   */
  virtual ~HighSpeedCarFactory() {}
  /**
   * @brief Create the entity(high speed car) in this factory.
   * @param entity New json object to create entity
   * (high speed car) right at the start of the scene
   * with the information
   */
  IEntity* CreateEntity(JsonObject& entity);
};

#endif  // HIGHSPEEDCAR_FACTORY_H_
