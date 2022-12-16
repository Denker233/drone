#ifndef COMPOSITE_FACTORY_H_
#define COMPOSITE_FACTORY_H_

#include "IEntityFactory.h"

class CompositeFactory : public IEntityFactory {
 public:
  /**
   * @brief Create a Entity object
   * 
   * @param entity entity to created
   * @return IEntity* the created one
   */
  IEntity* CreateEntity(JsonObject& entity);
  /**
   * @brief add the factory
   * 
   * @param factoryEntity factory that will be added
   */
  void AddFactory(IEntityFactory* factoryEntity);
  /**
   * @brief Destroy the Composite Factory object
   * 
   */
  virtual ~CompositeFactory();

 private:
  std::vector<IEntityFactory*> componentFactories;
};

#endif