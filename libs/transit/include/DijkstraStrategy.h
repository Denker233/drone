#ifndef Dijkstra_STRATEGY_H_
#define Dijkstra_STRATEGY_H_

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
class DijkstraStrategy : public IStrategy {
public:
    DijkstraStrategy(Vector3 position, Vector3 destination, const IGraph* graph);
    DijkstraStrategy::DijkstraStrategy(Vector3 position, Vector3 mid, Vector3 destination, const IGraph* graph);
    ~DijkstraStrategy();
    void Move(IEntity* entity, double dt);
    bool IsCompleted();
    DijkstraStrategy::decision(IEntity* entity, std::vector< IStrategy*> s2);
    DijkstraStrategy::Distance(IEntity* entity);
    DijkstraStrategy::TimeDirect(IEntity* entity);
    DijkstraStrategy::TimeSwap(IEntity* entity,Vector3* SwapStation);

private:
    std::vector<std::vector<float>> path;
    int currentIndex;
    int maxIndex;
    Vector3 midV3 = {0,0,0};
}; //end class
#endif // Dijkstra_STRATEGY_H_