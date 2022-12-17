#ifndef LIBS_TRANSIT_INCLUDE_DRONEFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_DRONEFACTORY_H_

#include <vector>

#include "Drone.h"
#include "IEntity.h"
#include "IEntityFactory.h"

/**
 * @brief this class inherits from IEntityFactory class and represents
 * the factory of the drone
 */
class DroneFactory : public IEntityFactory {
 public:
  /**
   * @brief Destroy the Drone Factory object
   *
   */
  virtual ~DroneFactory() {}
  /**
   * @brief Create a Entity object
   *
   * @param entity the input entity
   * @return IEntity* the drone
   */
  IEntity* CreateEntity(JsonObject& entity);
};  // end class

#endif  // LIBS_TRANSIT_INCLUDE_DRONEFACTORY_H_
