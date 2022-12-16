#ifndef ROBOT_FACTORY_H_
#define ROBOT_FACTORY_H_

#include <vector>

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Robot.h"

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

#endif