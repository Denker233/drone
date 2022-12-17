#ifndef LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_

#include <vector>

#include "CelebrationDecorator.h"
#include "IStrategy.h"

/**
/**
 * @brief this class inherits from the CelebrationDecorator class and is
 * responsible for decorate the istrategy to do celebration(jump)
 */
class SpinDecorator : public CelebrationDecorator {
 public:
 /**
  * @brief Construct a new Spin Decorator of the strategy
  * 
  * @param strategy_ the strategy to decorate
  */
  SpinDecorator(IStrategy* strategy_) : CelebrationDecorator(strategy_) {}
  /**
   * @brief check if the strategy is completed
   *
   * @return true is completed
   * @return false is not completed
   */
  bool IsCompleted();
  /**
   * @brief move the entity in delta time
   *
   * @param entity entity to move
   * @param dt delta time (change time)
   */
  void Move(IEntity* entity, double dt);
};  // close class

#endif  // LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_
