#ifndef LIBS_TRANSIT_INCLUDE_ROBOTFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_ROBOTFACTORY_H_

#include <vector>

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Robot.h"

/**
 * @brief this class inherits from IEntityFactory class and represents
 * the factory of the robot
 */
class RobotFactory : public IEntityFactory {
 public:
  /**
   * @brief Create a Entity object
   * 
   * @param entity entity to create
   * @return IEntity* the creat one
   */
  IEntity* CreateEntity(JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_ROBOTFACTORY_H_
