#ifndef LIBS_TRANSIT_INCLUDE_IENTITYFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_IENTITYFACTORY_H_

#include "Drone.h"
#include "IEntity.h"
#include "IEntityFactory.h"
#include "util/json.h"

/**
 * @brief this class is a factory to create IEntity
 */
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

#endif // LIBS_TRANSIT_INCLUDE_IENTITYFACTORY_H_
