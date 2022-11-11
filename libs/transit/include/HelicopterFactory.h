#ifndef HelICOPTER_FACTORY_H_
#define HelICOPTER_FACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Helicopter.h"

#include <vector>

class HelicopterFactory : public IEntityFactory {
  public:
    IEntity* CreateEntity(JsonObject& entity);
};


#endif