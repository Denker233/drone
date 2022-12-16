#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

#include <vector>

#include "Drone.h"
#include "IEntity.h"
#include "IEntityFactory.h"
/**
 * @brief the factory of the drone
 *
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

#endif  // DRONE_FACTORY_H_