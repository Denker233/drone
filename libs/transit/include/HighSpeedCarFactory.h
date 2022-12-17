#ifndef LIBS_TRANSIT_INCLUDE_HIGHSPEEDCARFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_HIGHSPEEDCARFACTORY_H_

#include <vector>

#include "HighSpeedCar.h"
#include "IEntity.h"
#include "IEntityFactory.h"

/**
 * @brief this class inhertis from the IEntityFactory class and is responsible
 * for HighSpeedCarFactory create highSpeedCar.
 */
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

#endif  // LIBS_TRANSIT_INCLUDE_HIGHSPEEDCARFACTORY_H_
