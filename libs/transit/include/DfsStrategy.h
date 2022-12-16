#ifndef DFS_STRATEGY_H_
#define DFS_STRATEGY_H_

/**
 * include
 */
#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for
 * generating the Dfsstrategy that the drone will take.
 */
class DfsStrategy : public IStrategy {
 public:
  /**
   * @brief Construct a new Dfs Strategy object
   *
   * @param position the start position of the strategy
   * @param destination the end position of the strategy
   * @param graph the graph that hold the start and end points and the strategy
   */
  DfsStrategy(Vector3 position, Vector3 destination, const IGraph* graph);
  /**
   * @brief Construct a new Dfs Strategy object
   *
   * @param position the start position of the strategy
   * @param mid the station points
   * @param destination the end position of the strategy
   * @param graph the graph that hold the start and end points and the strategy
   */
  DfsStrategy(Vector3 position, Vector3 mid, Vector3 destination,
              const IGraph* graph);
  /**
   * @brief Destroy the Dfs Strategy object
   *
   */
  ~DfsStrategy();
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
   * @brief choose the fast strategy (consider if we should go to the charge
   * station)
   *
   * @param entity the entity do the decision
   * @param s2 the list of strategy to consider
   * @return DfsStrategy* the fast one!!
   */
  DfsStrategy* decision(IEntity* entity, std::vector<IStrategy*> s2);
  /**
   * @brief check the real distance of the path
   *
   * @param path the path will be check
   * @return float the path distance
   */
  float RealDistance();
  /**
   * @brief calculate the time if entity went to destination directly without go
   * to the charge station
   *
   * @param entity the entity to calculate the time
   * @return float the time it go to destination directly
   */
  float TimeDirect(IEntity* entity);
  /**
   * @brief calculate the time if entity go to destination after it go to the
   * charge station
   *
   * @param entity the entity to calculate the time
   * @return float the time it go to station then go to the destination
   */
  float TimeSwap(IEntity* entity);

 private:
  std::vector<std::vector<float>> path;
  std::vector<std::vector<float>> path_station;
  std::vector<std::vector<float>> path_2;
  int currentIndex;
  int maxIndex;
  Vector3 midV3 = {0, 0, 0};
};      // end class
#endif  // DFS_STRATEGY_H_