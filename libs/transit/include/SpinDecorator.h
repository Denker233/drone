#ifndef SPIN_DECORATOR_H_
#define SPIN_DECORATOR_H_

#include <vector>

#include "CelebrationDecorator.h"
#include "IStrategy.h"

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

#endif  // SPIN_DECORATOR_H_