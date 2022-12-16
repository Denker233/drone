#ifndef LIBS_TRANSIT_INCLUDE_ISTRATEGY_H_
#define LIBS_TRANSIT_INCLUDE_ISTRATEGY_H_

#include <vector>

#include "IEntity.h"
#include "graph.h"
#include "math/vector3.h"

using namespace routing;

class IStrategy {
 public:
  /**
   * @brief move the entity in delta time
   *
   * @param entity entity to move
   * @param dt delta time (change time)
   */
  virtual void Move(IEntity* entity, double dt) = 0;
  /**
   * @brief check if the strategy is completed
   *
   * @return true is completed
   * @return false is not completed
   */
  virtual bool IsCompleted() = 0;
  /**
   * @brief calculate the time if entity go to destination after it go to the
   * charge station
   *
   * @param entity the entity to calculate the time
   * @return float the time it go to station then go to the destination
   */
  virtual float TimeSwap(IEntity* entity){}
  /**
   * @brief choose the fast strategy (consider if we should go to the charge
   * station)
   *
   * @param entity the entity do the decision
   * @param s2 the list of strategy to consider
   * @return AstarStrategy* the fast one!!
   */
  IStrategy* decision(IEntity* entity, std::vector<IStrategy*> s2) {}

 protected:
  // IGraph object to be used in the simulation.
  const IGraph* graph;
};  // close class

#endif  // LIBS_TRANSIT_INCLUDE_ISTRATEGY_H_
