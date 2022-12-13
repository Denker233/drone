#ifndef ASTAR_STRATEGY_H_
#define ASTAR_STRATEGY_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "IEntity.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for generating the beeline that the drone will take.
 */
class AstarStrategy : public IStrategy {
public:
    AstarStrategy(Vector3 position, Vector3 destination, const IGraph* graph);
    AstarStrategy(Vector3 position, Vector3 mid, Vector3 destination, const IGraph* graph);
    ~AstarStrategy();
    void Move(IEntity* entity, double dt);
    bool IsCompleted();
    AstarStrategy* decision(IEntity* entity, std::vector< IStrategy*> s2);
    float RealDistance(IEntity* entity);
    float TimeDirect(IEntity* entity);
    float TimeSwap(IEntity* entity);

private:
    std::vector<std::vector<float>> path;
    int currentIndex;
    int maxIndex;
    Vector3 midV3 = {0,0,0};
}; //end class
#endif // ASTAR_STRATEGY_H_