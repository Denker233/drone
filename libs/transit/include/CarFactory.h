#ifndef CAR_FACTORY_H_
#define CAR_FACTORY_H_

#include <vector>

#include "Car.h"
#include "IEntity.h"
#include "IEntityFactory.h"

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

#endif  // CAR_FACTORY_H_
