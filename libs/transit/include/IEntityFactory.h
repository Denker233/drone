#ifndef I_ENTITY_FACTORY_H_
#define I_ENTITY_FACTORY_H_

#include "Drone.h"
#include "IEntity.h"
#include "IEntityFactory.h"
#include "util/json.h"

class IEntityFactory {
 public:
 /**
  * @brief Destroy the IEntityFactory object
  * 
  */
  virtual ~IEntityFactory() {}
  /**
   * @brief Create a Entity object
   * 
   * @param entity the input entity
   * @return IEntity* the created entity
   */
  virtual IEntity* CreateEntity(JsonObject& entity) = 0;
};

#endif