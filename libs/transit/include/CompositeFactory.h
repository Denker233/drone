#ifndef LIBS_TRANSIT_INCLUDE_COMPOSITEFACTORY_H_
#define LIBS_TRANSIT_INCLUDE_COMPOSITEFACTORY_H_

#include "IEntityFactory.h"

/**
 * @brief this class inherits from the IEntityFactory class and is responsible for
 * create entity and add factories.
 */
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

#endif  // LIBS_TRANSIT_INCLUDE_COMPOSITEFACTORY_H_
