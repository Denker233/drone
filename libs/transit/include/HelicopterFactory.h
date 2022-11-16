#ifndef HELICOPTER_FACTORY_H_
#define HELICOPTER_FACTORY_H_

#include <vector>

#include "Helicopter.h"
#include "IEntity.h"
#include "IEntityFactory.h"

class HelicopterFactory : public IEntityFactory {
 public:
  /**
   * @brief Create the entity(helicopter) in this factory.
   * @param entity New json object to create entity(helicopter)
   * right at the start of the scene with the information
   */
  IEntity* CreateEntity(JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_HELICOPTERFACTORY_H_
