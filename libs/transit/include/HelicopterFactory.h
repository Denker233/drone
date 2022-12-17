#ifndef LIBS_TRANSIT_INCLUDE_HELICOPTERFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_HELICOPTERFACTORY_H_

#include <vector>

#include "Helicopter.h"
#include "IEntity.h"
#include "IEntityFactory.h"

/**
 * @brief this class inherits from the IEntityFactory class and is responsible
 * for HelicopterFactory create helicopters.
 */
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
