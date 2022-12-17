#ifndef LIBS_TRANSIT_INCLUDE_CARFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_CARFACTORY_H_

#include <vector>

#include "Car.h"
#include "IEntity.h"
#include "IEntityFactory.h"

/**
 * @brief this class inherits from the IEntityFactory class and is responsible
 * for CarFactory create cars.
 */
class CarFactory : public IEntityFactory {
 public:
  /**
   * @brief Destroy the Car factory object
   */
  virtual ~CarFactory() {}
  /**
   * @brief Create the entity(car) in this factory.
   * @param entity New json object to create entity(car)
   * right at the start of the scene with the information
   */
  IEntity* CreateEntity(JsonObject& entity);
};  // end class

#endif  // LIBS_TRANSIT_INCLUDE_CARFACTORY_H_
