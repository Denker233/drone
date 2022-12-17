#ifndef LIBS_TRANSIT_INCLUDE_BEELINESTRATEGY_H_
#define LIBS_TRANSIT_INCLUDE_BEELINESTRATEGY_H_

/**
 * include
 */
#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"
/**
 * @brief this class inherits from the IStrategy class and is responsible for
 * generating the beeline that the drone will take.
 */
class BeelineStrategy : public IStrategy {
 public:
  /**
   * @brief Construct a new Beeline Strategy object
   *
   * @param position the start position of the strategy
   * @param destination the end position of the strategy
   */
  BeelineStrategy(Vector3 position, Vector3 destination);
  /**
   * @brief Destroy the Beeline Strategy object
   *
   */
  ~BeelineStrategy();
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

 private:
  Vector3 position;
  Vector3 destination;
};      // end class
#endif  // LIBS_TRANSIT_INCLUDE_BEELINESTRATEGY_H_
