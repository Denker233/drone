#ifndef HighSpeedCar_FACTORY_H_
#define HighSpeedCar_FACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "HighSpeedCar.h"

#include <vector>

class HighSpeedCarFactory : public IEntityFactory {
  public:
    virtual ~HighSpeedCarFactory() {}
    IEntity* CreateEntity(JsonObject& entity);
};

#endif