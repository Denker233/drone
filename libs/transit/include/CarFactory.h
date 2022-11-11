#ifndef CAR_FACTORY_H_
#define CAR_FACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Car.h"

#include <vector>

class CarFactory : public IEntityFactory {
  public:
    virtual ~CarFactory() {}
    IEntity* CreateEntity(JsonObject& entity);
};

#endif