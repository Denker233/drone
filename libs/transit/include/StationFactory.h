#ifndef LIBS_TRANSIT_INCLUDE_STATIONFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_STATIONFACTORY_H_

#include <vector>

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Station.h"

/**
 * @brief represent the station factory to create the stations
 *
 */
class StationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destroy the Station Factory object
   *
   */
  virtual ~StationFactory() {}
  /**
   * @brief Create a Entity object
   *
   * @param entity the input entity to created
   * @return IEntity* the create one
   */
  IEntity* CreateEntity(JsonObject& entity);
};

#endif  // LIBS_TRANSIT_INCLUDE_STATIONFACTORY_H_
