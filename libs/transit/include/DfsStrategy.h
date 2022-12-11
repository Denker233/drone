#ifndef DFS_STRATEGY_H_
#define DFS_STRATEGY_H_

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
class DfsStrategy : public IStrategy {
public:
    DfsStrategy(Vector3 position, Vector3 destination, const IGraph* graph);
    DfsStrategy(Vector3 position, Vector3 mid, Vector3 destination, const IGraph* graph);
    ~DfsStrategy();
    void Move(IEntity* entity, double dt);
    bool IsCompleted();
    DfsStrategy decision(IEntity* entity, std::vector< IStrategy*> s2);
    float Distance(IEntity* entity);
    float TimeDirect(IEntity* entity);
    float TimeSwap(IEntity* entity,Vector3* SwapStation);

private:
    std::vector<std::vector<float>> path;
    int currentIndex;
    int maxIndex;
    Vector3 midV3 = {0,0,0};
}; //end class
#endif // DFS_STRATEGY_H_