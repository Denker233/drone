#ifndef LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_

#include <vector>

#include "IStrategy.h"

/**
 * @brief this class inhertis from the IStrategy class and is responsible for
 * decorate the istrategy to do celebration
 *
 */
class CelebrationDecorator : public IStrategy {
 public:
  /**
   * @brief Construct a new Celebration Decorator object
   *
   * @param strategy_ the strategy will be decorated
   */
  CelebrationDecorator(IStrategy *strategy_) {
    strategy = strategy_;
    time = 0;
  }
  /**
   * @brief move the entity in delta time
   *
   * @param entity entity to move
   * @param dt delta time (change time)
   */
  void Move(IEntity *entity, double dt);
  /**
   * @brief check if the strategy is completed
   *
   * @return true is completed
   * @return false is not completed
   */
  bool IsCompleted();

 protected:
  IStrategy *strategy;
  float time;
};  // close class

#endif  // LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_
