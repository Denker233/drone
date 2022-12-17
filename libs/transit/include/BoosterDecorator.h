#ifndef LIBS_TRANSIT_INCLUDE_BOOSTERDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_BOOSTERDECORATOR_H_

#include <vector>

#include "IStrategy.h"

/**
 * @brief this class inherits from the IStrategy class and is responsible for
 * generating decorate some IStrategy make them can work for drone with booster
 */
class BoosterDecorator : public IStrategy {
 public:
  /**
   * @brief Construct a new Booster Decorator object
   *
   * @param strategy_ the strategy will be decorated
   */
  BoosterDecorator(IStrategy* strategy_) { strategy = strategy_; }
  /**
   * @brief move the entity in delta time
   *
   * @param entity entity to move
   * @param dt delta time (change time)
   */
  void Move(IEntity* entity, double dt);
  /**
   * @brief check if the strategy is completed
   *
   * @return true is completed
   * @return false is not completed
   */
  bool IsCompleted();
  /**
   * @brief calculate the time if entity go to destination after it go to the
   * charge station
   *
   * @param entity the entity to calculate the time
   * @param SwapStation the station the entity will go to
   * @return float the time it go to station then go to the destination
   */
  float TimeSwap(IEntity* entity, Vector3* SwapStation) {}

 protected:
  IStrategy* strategy;
};  // end class

#endif  // LIBS_TRANSIT_INCLUDE_BOOSTERDECORATOR_H_
